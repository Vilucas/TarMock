#ifndef MAIN_H
#define MAIN_H

#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"


struct arguments_t {
    bool c;
    bool r;
    bool t;
    bool u;
    bool x;
    bool f;
}

typedef struct s_data {
    char                *archive_name;
    char   
    struct arguments_t  args;
}           data_t;

bool parsing(char **av, data_t Data);

#endif //MAIN_H