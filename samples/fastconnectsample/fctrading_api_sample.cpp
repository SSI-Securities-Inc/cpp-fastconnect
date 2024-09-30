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
		fastconnect::fctrading::api_client client = fastconnect::fctrading::api_client::create("http://192.168.213.98:1150/", "31dbfaf1998148de8a09e5822a09f2d2", "aebc3631eda048ca881906827a557d05", "PFJTQUtleVZhbHVlPjxNb2R1bHVzPjZNc2NnWVZrTFh6TUNqTlVOM25PWCtYT0JabVlsUWNsWXFnSGRHdk1iL3JwT3pReUNZQ2RLNHlmUjlBcm5xbjRtS3FLWTNqMGVzK05FeE1UTmJWcGVGbjYzOC9iWU9UL3NzM08zUllyTWVLMExqSEhlVTBjZDZ5YWxIRGVYbE9yUm55dWgvTlNDUUN0cVNLdVZPZmhhc0ZDM0NKTzRTZm9yRHJSc3M0bzc2az08L01vZHVsdXM+PEV4cG9uZW50PkFRQUI8L0V4cG9uZW50PjxQPjlUWFlXQjI3NDdpTmpjc0NPSmVPbzE0V1RhQUhFTmQ4akxtdGNXNlVZdjhSQkVEdnpBOFpRcVd3RzI1dEtJYkkveEhYT1FBSkRRTHBFUFMxcUxlTHFRPT08L1A+PFE+OHdsbGlNdXg0dmNjUmRHcHVMUFYrWnAvN2hYWjlYNXQwWjl2L2plS1o1dHRPeDVDcldUUzduVjQ2WEIwV2xUampBaHQxMm9zZE80UUJ4R2IzT1RFQVE9PTwvUT48RFA+UUNrQ25xdkpDZUMwU1RHaE55V1EwUFpCWjdaRG93aC9NbU16R3NjUVZJYmc4UGY4eHF2OHRBK2VjTThJQ042Ym9RSU9Db0FUM2krd3hCc0RuVTNKWVE9PTwvRFA+PERRPnB6anU4TW5lOHVDK1JsZjFwSTJ3aTlhL2NXejlsRW5TZkNwczM0a05wUzR2WVQ3MzkrQm90Z1NFRm5MMnkvU2V3SXBJTWJEdk4rRlppOU9VMzg5VUFRPT08L0RRPjxJbnZlcnNlUT5vODZSV0tyaXdsUmZHd1hTNzcrRVYxK1M3YU1UNWFtRlJ4S0RaSVd1SnVZRk95YlFHUG1EYjlUYTNkRkMxRUxQVDNVOHVjem1iQlFkZ0QzRGE5SUxEdz09PC9JbnZlcnNlUT48RD5PZVZCeXFpTkdJOEFBODF1TlhuU3JLRHZrdzczRnFFM1dBam9DYmxCbDl2MEkyaEF4WUk2RkhtZHAzT0xWYU42RXlYZTB3eGk2U1F6TnJvNHZkUEhUZEROVkdHanhNNFdJNVZ0NURFQ2cvL0N2dkZRd09saE9nVnJYSmh1RDhjYjZHRHZHUmY4K0hkYlBRZXM3MHNCbWFQSWhvSEp1RExIbnNLWmlERk40QUU9PC9EPjwvUlNBS2V5VmFsdWU+");
		std::cout << "start get access token\n";
		std::string token = client.get_access_token(0, "12345678", true);
		std::cout << "token: " << token << std::endl;
		const char* order = "{\n"
			"\"instrumentID\":\"SSI\",\n"
			"\"market\":\"VN\",\n"
			"\"buySell\":\"B\",\n"
			"\"orderType\":\"LO\",\n"
			"\"channelID\":\"TA\",\n"
			"\"price\":25000,\n"
			"\"quantity\":100,\n"
			"\"account\":\"1000011\",\n"
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
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what();
		return 1;
	}

	return 0;
}
