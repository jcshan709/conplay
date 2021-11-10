#pragma once

#ifndef _WIN32
#ifdef INCLUDE_WINDOWS
#error You are not under Win32 environment!
#endif
#endif

#if defined(_WIN32) && defined(INCLUDE_WINDOWS)
#define _HAS_STD_BYTE 0 // std::byte and ::byte are incompatible
#define NOMINMAX
# ifdef WINSOCK2
#include <WinSock2.h>
#include <ws2bth.h>
#include <ws2def.h>
#include <ws2ipdef.h>
#include <WS2atm.h>
#include <WS2spi.h>
#include <WS2tcpip.h>
# endif
#include <Windows.h>
#include <tchar.h>
# ifdef LINKLIB
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "advapi32.lib")
# endif
#endif

// get version
#ifdef _MSC_VER
#define CPP_VERSION _MSVC_LANG
constexpr bool MSVC = true, clang = false, GNU = false;
#else
#define CPP_VERSION __cplusplus
# ifdef __GNUC__
constexpr bool MSVC = false, clang = false, GNU = true;
# elif defined(__clang__)
constexpr bool MSVC = false, clang = true, GNU = false;
# else
constexpr bool MSVC = false, clang = false, GNU = false;
# endif
#endif
constexpr long __cpp_version = CPP_VERSION;

#ifdef _WIN32
constexpr bool win32 = true;
# ifdef _WIN64
constexpr bool win64 = true;
# else
constexpr bool win64 = false;
# endif
#else
constexpr bool win32 = false, win64 = false;
#endif

#define CPP97 199711L
#define CPP11 201103L
#define CPP14 201402L
#define CPP17 201703L
#define CPP20 202002L
#define CPPLATEST 202004L

// C Runtime Library
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#if CPP_VERSION >= CPP11
# if CPP_VERSION < CPP17
#include <ccomplex>   // Deprecated in C++17
#include <cstdalign> // Deprecated in C++17
#include <cstdbool> // Deprecated in C++17
#include <ctgmath> // Deprecated in C++17
# endif
#include <cfenv>
#include <cinttypes>
#include <cstdint>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#endif

// C++ standard headers
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#if CPP_VERSION >= CPP11
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
#if CPP_VERSION >= CPP14
#include <shared_mutex>
#endif

#if CPP_VERSION >= CPP17
#include <any>
#include <charconv>
#include <optional>
#include <filesystem>
#endif

#if CPP_VERSION >= CPP20
#include <format>
#endif

// namespace
#ifndef NO_USING_STD
using namespace std;
using namespace std::chrono;
# if CPP_VERSION >= CPP17
using namespace std::filesystem;
# endif
#endif
