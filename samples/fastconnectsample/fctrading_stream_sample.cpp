// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include <iostream>
#include <sstream>
#include "fctrading_stream_client.h"


int main()
{
	fastconnect::fctrading::api_client client = fastconnect::fctrading::api_client::create("https://fc-tradeapi.ssi.com.vn/", "", "");
    fastconnect::fctrading::stream_client stream_client = fastconnect::fctrading::stream_client::create("https://fc-tradehub.ssi.com.vn/", std::make_shared<fastconnect::fctrading::api_client>(client));
   
	try
	{
		stream_client.subscribe(300, [](const std::string &message){
			std::cout << message << std::endl;
		});
         stream_client.start();
         std::string message;
        std::getline(std::cin, message);
   
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
