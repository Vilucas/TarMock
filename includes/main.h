#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#define USAGE "usage ./mockTar <options> <archive_name> <arguments>\n\t-c Create a new archive containing the specified items.\n\t-r Like -c, but new entries are appended to the archive. The -f option is required.\n\t-t List archive contents to stdout.\n\t-u Like -r, but new entries are added only if they have a modification date newer than the corresponding entry in the archive. The -f option is required.\n\t-x Extract to disk from the archive. If a file with the same name appears more than once in the archive, each copy will be extracted, with later copies overwriting (replacing) earlier copies.\n "
#define MAX_OPTIONS 6

struct arguments_t {
    bool c;
    bool r;
    bool t;
    bool u;
    bool x;
    bool f;
};

enum fileType{
    FileType,
    FolderType,
};

typedef struct s_largs {
    char *arg_name;
    enum fileType type;
    struct s_larfs *next;
} largs_t;

typedef struct s_data {
    char                *archive_name;
    largs_t              *arguments;  
    struct arguments_t  options;
}           data_t;

bool parsing(char **av, data_t **Data);
void addNode(largs_t **head, char *val, enum fileType type);
void printInputData(data_t *Data);
#endif //MAIN_H