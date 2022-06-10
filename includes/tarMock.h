/* tar Header Block, from POSIX 1003.1-1990.  */

/* POSIX header.  */

#ifndef TarMOCK_H
#define TarMOCK_H


struct posix_header_mock
{                              /* byte offset */
  char *name;               /*   0 */
  int    size;                /* 124 */
};


void   printfHeader(struct posix_header_mock *new);


#endif