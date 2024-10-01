// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include <iostream>
#include <sstream>
#include "fctrading_api_client.h"

int main()
{

	try
	{

		fastconnect::fctrading::api_client client = fastconnect::fctrading::api_client::create("https://fc-tradeapi.ssi.com.vn/" /*https://fc-paperapi.ssi.com.vn*/, "", "", "");
		std::cout << "start get access token\n";
		
		std::cout <<"Get otp: " << client.get_otp() << "\n";

 		std::string otp;
        std::getline(std::cin, otp);

		std::string token = client.get_access_token(1, otp, true);
		std::cout << "token: " << token << std::endl;
		const char* order = "{\n"
			"\"instrumentID\":\"SSI\",\n"
			"\"market\":\"VN\",\n"
			"\"buySell\":\"B\",\n"
			"\"orderType\":\"LO\",\n"
			"\"channelID\":\"TA\",\n"
			"\"price\":25000,\n"
			"\"quantity\":100,\n"
			"\"account\":\"1234567\",\n"
			"\"requestID\":\"2\",\n"
			"\"stopOrder\":false,\n"
			"\"stopPrice\":0,\n"
			"\"stopType\":\"string\",\n"
			"\"stopStep\":0,\n"
			"\"lossStep\":0,\n"
			"\"profitStep\":0,\n"
			"\"code\":\"string\",\n"
			"\"modifiable\":true,\n"
			"\"deviceId\":\"00:00:00:00:00:00\",\n"
			"\"userAgent\":\"string\"\n"
			"}";
		std::cout << client.new_order(order) << std::endl;
		std::cout << "Orderbook: " << client.get_order_book_detail("1234567") << std::endl;
		std::cout << "Account balance: " << client.get_cash_account_balance("1234567") << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
