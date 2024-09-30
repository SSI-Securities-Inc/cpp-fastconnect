#include "fastconnect/fctrading_api_client.h"
#include <cpprest/http_client.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include "pugixml.hpp"
#include "fastconnect/base64.h"
#include "util.h"
namespace fastconnect
{
	namespace fctrading
	{
		api_client api_client::create(const std::string& url, const std::string& id, const std::string& secret, const std::string& private_key)
		{
			return api_client(url, id, secret, private_key);
		}
		api_client::api_client(const std::string& url, const std::string& id, const std::string& secret, const std::string& private_key)
			: m_url(url), m_id(id), m_secret(secret), m_private_key(private_key)
		{
			if(m_private_key.size() > 0)
				m_rsa = RSA_from_xmlb64(private_key);
		}

		api_client::~api_client()
		{
		}

		std::string api_client::get_access_token(int twoFAType, const std::string& code, bool save)
		{


			web::http::client::http_client client(utility::conversions::to_string_t(m_url));
			web::http::uri_builder builder(U("/api/v2/Trading/AccessToken"));
			web::json::value body;
			body[U("consumerID")] = web::json::value(utility::conversions::to_string_t(m_id));
			body[U("consumerSecret")] = web::json::value(utility::conversions::to_string_t(m_secret));
			body[U("twoFactorType")] = web::json::value(twoFAType);
			body[U("code")] = web::json::value(utility::conversions::to_string_t(code));
			body[U("isSave")] = web::json::value(save);
			web::http::http_request request(web::http::methods::POST);
			request.set_body(body.serialize(), U("application/json"));
			request.set_request_uri(builder.to_string());
			auto response = client.request(request).get();

			if (response.status_code() != web::http::status_codes::OK)
			{
				throw std::runtime_error("Failed to get access token");
			}
			auto json_response = response.extract_json().get();

			if (json_response.at(U("status")).as_integer() == 200)
			{
				m_access_token = utility::conversions::to_utf8string(json_response.at(U("data")).at(U("accessToken")).as_string());
				return m_access_token;
			}
			else
				throw std::runtime_error(utility::conversions::to_utf8string(json_response.at(U("message")).as_string()));
		}
		std::string api_client::sign(const std::string& data)
		{
			if(m_rsa == NULL)
				throw std::runtime_error("Private key is not set");
			// SHA256 digest
			unsigned char hash[SHA256_DIGEST_LENGTH];
			SHA256_CTX sha256;
			SHA256_Init(&sha256);
			SHA256_Update(&sha256, data.c_str(), data.size());
			SHA256_Final(hash, &sha256);

			const int size = RSA_size(m_rsa);
			unsigned char* sign = new unsigned char[size];
			unsigned int outlen = 0;
			RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, sign, &outlen, m_rsa);
			return to_hex(sign, outlen);
		}

		std::string api_client::new_order(const std::string& data) {
			return post(m_url, "/api/v2/Trading/NewOrder", data);
		}
		std::string api_client::post(const std::string& url, const std::string& path, const std::string& body)
		{
			web::http::client::http_client client(utility::conversions::to_string_t(url));
			web::http::uri_builder builder(utility::conversions::to_string_t(path));

			web::http::http_request request(web::http::methods::POST);
			request.set_body(utility::conversions::to_string_t(body), U("application/json"));
			request.set_request_uri(builder.to_string());
			web::http::http_headers headers;
			headers.add(U("Authorization"), utility::conversions::to_string_t("Bearer " + m_access_token));
			headers.add(U("X-Signature"),utility::conversions::to_string_t(sign(body)));
			headers.add(U("Content-Type"), U("application/json"));
			request.headers() = headers;
			auto response = client.request(request).get();

			if (response.status_code() != web::http::status_codes::OK)
			{
				throw std::runtime_error("Failed to post " + path);
			}
			return response.extract_utf8string().get();
		}
	}
}