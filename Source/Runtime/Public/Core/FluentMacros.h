#pragma once

#define INDEX_NONE		(-1)

#define SIMD_CALL __vectorcall

#undef TEXT
#ifdef UNICODE
#define TXT(String) L##String
#elif
#define TXT(String) String
#endif

#define LOG_CONSOLE_STRING(String) printf("%s\n", String.c_str())
#define LOG_CONSOLE_FORMAT(Format, ...) printf(Format, __VA_ARGS__)

#define ARRAY_SIZE(array) sizeof((array)) / sizeof((array[0]))

