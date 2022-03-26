#ifndef LOGGING_H
#define LOGGING_H

/*
Este módulo define macros auxiliares para logging da execução do programa.
*/

#include <stdio.h>

#ifdef DEBUG
    #define LOG_INFO(fmt, ...) printf("INFO: " fmt, ##__VA_ARGS__)
    #define LOG_AVISO(fmt, ...) printf("AVISO: " fmt, ##__VA_ARGS__)
#else
    #define LOG_INFO(fmt, ...)
    #define LOG_AVISO(fmt, ...)
#endif

#define LOG_ERRO(fmt, ...) fprintf(stderr, "ERRO: " fmt, ##__VA_ARGS__)

#endif
