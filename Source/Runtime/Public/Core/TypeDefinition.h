#pragma once

using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

#ifdef UNICODE
using tchar = wchar_t;
#else
using tchar = char;
#endif

