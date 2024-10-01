# SSI FastConnect C++ Client



## Build this library

### Install vcpkg
```powershell
PS> git clone https://github.com/microsoft/vcpkg.git
PS> cd vcpkg; .\bootstrap-vcpkg.bat
PS> $env:VCPKG_ROOT="C:\path\to\vcpkg"
PS> $env:PATH="$env:VCPKG_ROOT;$env:PATH"
```

### Build on Windows ###
```powershell
PS> git submodule update --init
PS> vcpkg install cpprestsdk[websockets]:x64-windows
PS> mkdir build.release
PS> cd build.release
PS> cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE="$env{VCPKG_ROOT}\submodules\vcpkg\scripts\buildsystems\vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -DUSE_CPPRESTSDK=true
PS> cmake --build . --config Release
```
Output will be in `build.release\bin\Release\`


## Example usage

```cpp
#include <iostream>
#include <sstream>
#include "fcdata_api_client.h"

int main()
{

	try
	{
		fastconnect::fcdata::api_client client = fastconnect::fcdata::api_client::create("https://fc-dataapi.ssi.com.vn/", "", "");
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

```

