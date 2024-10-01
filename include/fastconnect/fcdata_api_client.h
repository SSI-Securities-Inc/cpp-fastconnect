#include "_exports.h"
#include <string>
#include <functional>
namespace fastconnect
{
    namespace fcdata
    {
        class api_client
        {
        public:
            /// @brief Create FastConnect Data API client
            /// @param url we provied at https://guide.ssi.com.vn/ssi-products/fastconnect-data/connection-guide
            /// @param id https://guide.ssi.com.vn/ssi-products/service-registration
            /// @param secret https://guide.ssi.com.vn/ssi-products/service-registration
            /// @return API client
            FASTCONNECTCLIENT_API static api_client create(const std::string &url, const std::string &id, const std::string &secret);

            FASTCONNECTCLIENT_API ~api_client();
            /// @brief Get access token to authenticate with server
            /// @return access token
            FASTCONNECTCLIENT_API std::string get_access_token();

            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-securities
            /// @param market 
            /// @param page_index 
            /// @param page_size 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_securities(const std::string& market = "", int page_index = 1, int page_size = 100);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-securitiesdetails
            /// @param market 
            /// @param symbol 
            /// @param page_index 
            /// @param page_size 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_securities_details(const std::string& market = "", const std::string& symbol = "", int page_index = 1, int page_size = 100);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-indexcomponents
            /// @param index_code 
            /// @param page_index 
            /// @param page_size 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_index_components(const std::string& index_code = "", int page_index = 1, int page_size = 100);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-indexlist
            /// @param exchange 
            /// @param page_index 
            /// @param page_size 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_index_list(const std::string& exchange = "", int page_index = 1, int page_size = 100);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-dailyohlc
            /// @param symbol 
            /// @param from_date 
            /// @param to_date 
            /// @param page_index 
            /// @param page_size 
            /// @param ascending 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_daily_ohlc(const std::string& symbol = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, bool ascending = true);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-intradayohlc
            /// @param symbol 
            /// @param from_date 
            /// @param to_date 
            /// @param page_index 
            /// @param page_size 
            /// @param ascending 
            /// @param resolution 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_intraday_ohlc(const std::string& symbol = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, bool ascending = true, int resolution = 1);
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-dailyindex
            /// @param index_id 
            /// @param from_date 
            /// @param to_date 
            /// @param page_index 
            /// @param page_size 
            /// @param order_by 
            /// @param order 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_daily_index(const std::string& index_id = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, const std::string& order_by = "", const std::string& order = "");
            /// @brief https://guide.ssi.com.vn/ssi-products/fastconnect-data/api-specs#get-dailystockprice
            /// @param symbol 
            /// @param from_date 
            /// @param to_date 
            /// @param page_index 
            /// @param page_size 
            /// @param market 
            /// @return 
            FASTCONNECTCLIENT_API std::string get_daily_stock_price(const std::string& symbol = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, const std::string& market = "");

        private:
            std::string m_url;
            std::string m_id;
            std::string m_secret;
            std::string m_access_token; //TODO: need re-login after expired

            api_client(const std::string &url, const std::string &id, const std::string &secret);
            std::string get(const std::string& url, const std::string& path);
        };
    }
}