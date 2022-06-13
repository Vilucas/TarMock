#ifndef ARCHIVE_MANAGEMENT_H
#define ARCHIVE_MANAGEMENT_H

#include "main.h"

bool createArchive(data_t *Data);
bool extractArchive(data_t *Data);
bool appendItemToArchive(int fd, char *name, enum fileType type);
bool printArchive(data_t *Data);

#endif //ARCHIVE_MANAGEMENT_H