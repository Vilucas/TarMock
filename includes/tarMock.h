/* tar Header Block, from POSIX 1003.1-1990.  */

/* POSIX header.  */

#ifndef TarMOCK_H
#define TarMOCK_H


struct posix_header_mock
{                              /* byte offset */
  char *name;               /*   0 */
  int    size;                /* 124 */
};

#define MAX_NAME_LENGTH 100
#define MAX_SIZE_LENGTH 12

void   printfHeader(struct posix_header_mock *new);


#endif