/* exercise 5-3.c  */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main (int argc, char *argv[])
{
  int fd, flags, i, numWritten, len, ap;
  _Bool apnd_flag = 0;

  printf ("Hello world\n");

  for (ap = 1; ap < argc; ap++) {
    if (argv[ap][0] == 'x') {
      apnd_flag = 1;
      break;
    }
  }

    if (apnd_flag)
      flags=O_RDWR | O_CREAT; //seek to end later
    else
      flags = O_RDWR | O_CREAT | O_APPEND;


    fd = open(argv[1], flags,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
      errExit("open");

  if (apnd_flag)
    lseek(fd, 0, SEEK_END);

  len = getLong(argv[2], GN_ANY_BASE, argv[2]);
  //printf ("%d", len);
  for(i = 0; i < len; i++) {
    numWritten = write (fd, "H", 1);
    if (numWritten == -1)
      errExit("write");
  }
    

  if (close(fd) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);


}
