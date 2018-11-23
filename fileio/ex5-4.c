/* exercise 5-4.c */

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

int my_dup (int old_fd)
{
  return fcntl(old_fd, F_DUPFD, 0);
}

int my_dup2 (int old_fd, int new_fd)
{
  if(!fcntl(old_fd, F_GETFL)) {
    errno = EBADF;
    return -1;
  }

  else if(new_fd == old_fd)
  return old_fd;

  close(new_fd);
  return fcntl(old_fd, F_DUPFD, new_fd);
}

int main (void)
{
  int fd;

  //close(1);
  //i = my_dup(2);

  fd = my_dup2(600, 600);
  if(fd == -1)
    errExit("my_dup2");

  printf("%d\n", fd);

  close(fd);

  return 0;
}
