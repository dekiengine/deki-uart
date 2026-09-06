#pragma once

#ifdef _WIN32
    #ifdef DEKI_UART_EXPORTS
        #define DEKI_UART_API __declspec(dllexport)
    #else
        #define DEKI_UART_API __declspec(dllimport)
    #endif
#else
    #define DEKI_UART_API __attribute__((visibility("default")))
#endif
