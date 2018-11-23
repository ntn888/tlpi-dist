/* exercise 5-5.c */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"


int main (int argc, char **argv)
{
  int fd, fd2, ap, flags;
  ssize_t numWritten;
  _Bool apnd_flag = 0;
  printf ("Hello world\n");

  for (ap = 1; ap < argc; ap++) {
    if (argv[ap][0] == 'x') {
      apnd_flag = 1;
      break;
    }
  }


  if (apnd_flag)
    flags = O_RDWR | O_CREAT | O_APPEND;
  else
    flags=O_RDWR | O_CREAT;

  fd = open(argv[1], flags,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
        errExit("open");

  fd2 = dup(fd);    // All the magic right here
  numWritten = write(fd, argv[2], strlen(argv[2]));
  if (numWritten == -1)
    errExit("write");
  printf("wrote %ld bytes\n", (long) numWritten);
            
  numWritten = write(fd2, argv[2], strlen(argv[2]));
  if (numWritten == -1)
    errExit("write");
  printf("wrote %ld bytes\n", (long) numWritten);

  exit(EXIT_SUCCESS);
}
