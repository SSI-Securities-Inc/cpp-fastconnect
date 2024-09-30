// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include <iostream>
#include <sstream>
#include "fcdata_stream_client.h"


int main()
{
	fastconnect::fcdata::api_client client = fastconnect::fcdata::api_client::create("http://192.168.213.98:1189/", "7412da607c354a72b996bc00bf5eb9de", "95bd2765dfb843a6b87be2bddd65b723");
    fastconnect::fcdata::stream_client stream_client = fastconnect::fcdata::stream_client::create("http://192.168.213.98:1188/", std::make_shared<fastconnect::fcdata::api_client>(client));
   
	try
	{
		stream_client.subscribe("X:ALL", [](const std::string &message){
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
