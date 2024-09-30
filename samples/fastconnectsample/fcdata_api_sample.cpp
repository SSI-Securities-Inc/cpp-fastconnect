// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include <iostream>
#include <sstream>
#include "fcdata_api_client.h"

int main()
{

	try
	{
		fastconnect::fcdata::api_client client = fastconnect::fcdata::api_client::create("http://192.168.213.98:1189/", "7412da607c354a72b996bc00bf5eb9de", "95bd2765dfb843a6b87be2bddd65b723");
		std::cout << "start get access token\n";
		std::string token = client.get_access_token();
		std::cout << "token: " << token << std::endl;
		
		std::cout << client.get_securities("HOSE", 1, 1000) << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
