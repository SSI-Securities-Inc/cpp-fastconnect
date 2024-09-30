#include "fastconnect/fcdata_api_client.h"
#include <cpprest/http_client.h>
#include "util.h"
namespace fastconnect
{
	namespace fcdata
	{
		api_client api_client::create(const std::string &url, const std::string &id, const std::string &secret)
		{
			return api_client(url, id, secret);
		}
		api_client::api_client(const std::string &url, const std::string &id, const std::string &secret)
			: m_url(url), m_id(id), m_secret(secret)
		{
		}

		api_client::~api_client()
		{
		}

		std::string api_client::get_access_token()
		{

			web::http::client::http_client client(utility::conversions::to_string_t(m_url));
			web::http::uri_builder builder(U("/api/v2/Market/AccessToken"));
			web::json::value body;
			body[U("consumerID")] = web::json::value(utility::conversions::to_string_t(m_id));
			body[U("consumerSecret")] = web::json::value(utility::conversions::to_string_t(m_secret));
			web::http::http_request request(web::http::methods::POST);
			request.set_body(body.serialize(), U("application/json"));
			request.set_request_uri(builder.to_string());
			web::http::http_headers headers;
			headers.add(U("Content-Type"), U("application/json"));
			headers.add(U("Accept"), U("application/json"));
			request.headers() = headers;
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

		std::string api_client::get_securities(const std::string &market, int page_index, int page_size)
		{
			web::http::uri_builder builder(U("/api/v2/Market/Securities"));
			if (market.size() > 0)
				builder.append_query(U("market"), utility::conversions::to_string_t(market), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}
		std::string api_client::get_securities_details(const std::string &market, const std::string &symbol, int page_index, int page_size)
		{
			web::http::uri_builder builder(U("/api/v2/Market/SecuritiesDetails"));
			if (market.size() > 0)
				builder.append_query(U("market"), utility::conversions::to_string_t(market), true);
			if (symbol.size() > 0)
				builder.append_query(U("symbol"), utility::conversions::to_string_t(market), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}
		std::string api_client::get_index_components(const std::string &index_code, int page_index, int page_size)
		{
			web::http::uri_builder builder(U("/api/v2/Market/IndexComponents"));
			if (index_code.size() > 0)
				builder.append_query(U("indexCode"), utility::conversions::to_string_t(index_code), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}
		std::string api_client::get_index_list(const std::string &exchange, int page_index, int page_size)
		{
			web::http::uri_builder builder(U("/api/v2/Market/IndexList"));
			if (exchange.size() > 0)
				builder.append_query(U("exchange"), utility::conversions::to_string_t(exchange), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}
		std::string api_client::get_daily_ohlc(const std::string &symbol, const std::string &from_date, const std::string &to_date, int page_index, int page_size, bool ascending)
		{
			web::http::uri_builder builder(U("/api/v2/Market/DailyOhlc"));
			if (symbol.size() > 0)
				builder.append_query(U("symbol"), utility::conversions::to_string_t(symbol), true);
			if (from_date.size() > 0)
				builder.append_query(U("fromDate"), utility::conversions::to_string_t(from_date), true);
			if (to_date.size() > 0)
				builder.append_query(U("toDate"), utility::conversions::to_string_t(to_date), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			builder.append_query(U("ascending"), utility::conversions::to_string_t(to_string(ascending)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}
		std::string api_client::get_intraday_ohlc(const std::string &symbol, const std::string &from_date, const std::string &to_date, int page_index, int page_size, bool ascending, int resolution)
		{
			web::http::uri_builder builder(U("/api/v2/Market/IntradayOhlc"));
			if (symbol.size() > 0)
				builder.append_query(U("symbol"), utility::conversions::to_string_t(symbol), true);
			if (from_date.size() > 0)
				builder.append_query(U("fromDate"), utility::conversions::to_string_t(from_date), true);
			if (to_date.size() > 0)
				builder.append_query(U("toDate"), utility::conversions::to_string_t(to_date), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			builder.append_query(U("ascending"), utility::conversions::to_string_t(to_string(ascending)));
			builder.append_query(U("resolution"), utility::conversions::to_string_t(std::to_string(resolution)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}

		std::string api_client::get_daily_index(const std::string &index_id, const std::string &from_date, const std::string &to_date, int page_index, int page_size, const std::string &order_by, const std::string &order)
		{
			web::http::uri_builder builder(U("/api/v2/Market/DailyIndex"));
			if (index_id.size() > 0)
				builder.append_query(U("indexId"), utility::conversions::to_string_t(index_id), true);
			if (from_date.size() > 0)
				builder.append_query(U("fromDate"), utility::conversions::to_string_t(from_date), true);
			if (to_date.size() > 0)
				builder.append_query(U("toDate"), utility::conversions::to_string_t(to_date), true);
			if (order_by.size() > 0)
				builder.append_query(U("orderBy"), utility::conversions::to_string_t(order_by), true);
			if (order.size() > 0)
				builder.append_query(U("order"), utility::conversions::to_string_t(order), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}

		std::string api_client::get_daily_stock_price(const std::string &symbol, const std::string &from_date, const std::string &to_date, int page_index, int page_size, const std::string &market)
		{
			web::http::uri_builder builder(U("/api/v2/Market/DailyStockPrice"));
			if (symbol.size() > 0)
				builder.append_query(U("symbol"), utility::conversions::to_string_t(symbol), true);
			if (from_date.size() > 0)
				builder.append_query(U("fromDate"), utility::conversions::to_string_t(from_date), true);
			if (to_date.size() > 0)
				builder.append_query(U("toDate"), utility::conversions::to_string_t(to_date), true);
			if (market.size() > 0)
				builder.append_query(U("market"), utility::conversions::to_string_t(market), true);
			builder.append_query(U("pageIndex"), utility::conversions::to_string_t(std::to_string(page_index)));
			builder.append_query(U("pageSize"), utility::conversions::to_string_t(std::to_string(page_size)));
			return get(m_url, utility::conversions::to_utf8string(builder.to_string()));
		}

		std::string api_client::get(const std::string &url, const std::string &path)
		{
			web::http::client::http_client client(utility::conversions::to_string_t(url));

			web::http::http_request request(web::http::methods::GET);
			request.set_request_uri(utility::conversions::to_string_t(path));

			web::http::http_headers headers;
			headers.add(U("Authorization"), utility::conversions::to_string_t("Bearer " + m_access_token));
			request.headers() = headers;
			auto response = client.request(request).get();

			if (response.status_code() != web::http::status_codes::OK)
			{
				throw std::runtime_error("Failed to get " + path + ": " + utility::conversions::to_utf8string(response.to_string()));
			}
			return response.extract_utf8string().get();
		}
	}
}