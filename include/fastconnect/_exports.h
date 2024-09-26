// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#pragma once

#ifdef NO_FASTCONNECTCLIENT_EXPORTS
#define FASTCONNECTCLIENT_API
#else
#ifdef FASTCONNECTCLIENT_EXPORTS
#define FASTCONNECTCLIENT_API __declspec(dllexport)
#else
#define FASTCONNECTCLIENT_API __declspec(dllimport)
#endif // FASTCONNECTCLIENT_EXPORTS
#endif // NO_FASTCONNECTCLIENT_EXPORTS

#ifndef _WIN32
#ifndef __cdecl
#ifdef cdecl
#define __cdecl __attribute__((cdecl))
#else
#define __cdecl
#endif // cdecl
#endif // !__cdecl
#endif // _WIN32