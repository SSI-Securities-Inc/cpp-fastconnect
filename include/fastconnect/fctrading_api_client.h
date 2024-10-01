#include "_exports.h"
#include <string>
#include <functional>
#include <openssl/rsa.h>
namespace fastconnect
{
    namespace fctrading
    {
        class api_client
        {
        public:
            /// @brief Create FastConnect Trading API client
            /// @param url FCTrading API url we proviced at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/connection-guide
            /// @param id Your consumer_id can get it from us https://iboard.ssi.com.vn
            /// @param secret Your consumer secret can get it from us https://iboard.ssi.com.vn
            /// @param private_key Your private can get it from us https://iboard.ssi.com.vn, this param can be empty if you don't want to place/modify/cancel order
            /// @return API client
            FASTCONNECTCLIENT_API static api_client create(const std::string &url, const std::string &id, const std::string &secret, const std::string &private_key = "");

            FASTCONNECTCLIENT_API ~api_client();

            /// @brief Get access token to authenticate with server
            /// @param twoFAType 0: PIN, 1: OTP. If you use 2FA, you need to get OTP from your 2FA device
            /// @param code PIN or OTP code
            /// @param save Save your PIN/OTP to server, you don't need to verify PIN/OTP next time to  place/modify/cancel order
            /// @return Response from server
            FASTCONNECTCLIENT_API std::string get_access_token(int twoFAType = 0, const std::string &code = "", bool save = false);
            FASTCONNECTCLIENT_API std::string sign(const std::string &data);

            /// @brief Request generate OTP to your 2FA device
            /// @return Your otp status
            FASTCONNECTCLIENT_API std::string get_otp();

            /// @brief place order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-neworder
            /// @return json string response from server
            FASTCONNECTCLIENT_API std::string new_order(const std::string& data);
            /// @brief cancel order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-cancelorder
            /// @return json string response from server
            FASTCONNECTCLIENT_API std::string cancel_order(const std::string& data);
            /// @brief modify order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-modifyorder
            /// @return  json string response from server
            FASTCONNECTCLIENT_API std::string modify_order(const std::string& data);
            /// @brief place derivative order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-derneworder
            /// @return  json string response from server
            FASTCONNECTCLIENT_API std::string derivative_new_order(const std::string& data);
            /// @brief cancel derivative order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-dercancelorder
            /// @return json string response from server
            FASTCONNECTCLIENT_API std::string derivative_cancel_order(const std::string& data);
            /// @brief modify derivative order
            /// @param data json string, specs at https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-dermodifyorder
            /// @return json string response from server
            FASTCONNECTCLIENT_API std::string derivative_modify_order(const std::string& data);

            /// @brief Get ratelimit https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#get-ratelimit
            /// @return 
            FASTCONNECTCLIENT_API std::string get_ratelimit();
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#post-orderbook
            /// @param account 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_order_book(const std::string& account);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#get-auditorderbook
            /// @param account 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_order_book_detail(const std::string& account);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#get-cashaccountbalance
            /// @param account 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_cash_account_balance(const std::string& account);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-trading/api-specs#get-derivativeaccountbalance
            /// @param account 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_derivative_account_balance(const std::string& account);


        private:
            std::string m_url;
            std::string m_id;
            std::string m_secret;
            std::string m_private_key;
            RSA *m_rsa;
            std::string m_access_token; //TODO: need re-login after expired

            api_client(const std::string &url, const std::string &id, const std::string &secret, const std::string &private_key);
            std::string post(const std::string& url, const std::string& path, const std::string& body);
            std::string get(const std::string& url, const std::string& path);
        };
    }
}