

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"


int main (void)
{
	
	int fd;
	
	fd = open("text.txt", O_RDWR | O_APPEND, 
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
		errExit("open");
    
    if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");
    printf("seek succeeded\n");
	
	if (write(fd, "test", 4) == -1)
        errExit("write");
    exit(EXIT_SUCCESS);
}
