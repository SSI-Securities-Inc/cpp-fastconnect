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
            FASTCONNECTCLIENT_API static api_client create(const std::string &url, const std::string &id, const std::string &secret);

            FASTCONNECTCLIENT_API ~api_client();

            FASTCONNECTCLIENT_API std::string get_access_token();

            FASTCONNECTCLIENT_API std::string get_securities(const std::string& market = "", int page_index = 1, int page_size = 100);
            FASTCONNECTCLIENT_API std::string get_securities_details(const std::string& market = "", const std::string& symbol = "", int page_index = 1, int page_size = 100);
            FASTCONNECTCLIENT_API std::string get_index_components(const std::string& index_code = "", int page_index = 1, int page_size = 100);
            FASTCONNECTCLIENT_API std::string get_index_list(const std::string& exchange = "", int page_index = 1, int page_size = 100);
            FASTCONNECTCLIENT_API std::string get_daily_ohlc(const std::string& symbol = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, bool ascending = true);
            FASTCONNECTCLIENT_API std::string get_intraday_ohlc(const std::string& symbol = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, bool ascending = true, int resolution = 1);
            FASTCONNECTCLIENT_API std::string get_daily_index(const std::string& index_id = "",const std::string& from_date = "",const std::string& to_date = "", int page_index = 1, int page_size = 100, const std::string& order_by = "", const std::string& order = "");
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