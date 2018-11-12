/*  
Usage: tee [OPTION]... [FILE]...
Copy standard input to each FILE, and also to standard output.


* read std_input
* write to file
* seek to 0, write to std_output
* 
* easy 

*/

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 1024

int main (int argc, char *argv[])
{
	
	int fd, openFlags;
	ssize_t numRead, totRead = 0;
	char buf[BUF_SIZE];
	
	//printf ("Hello World");
	
	if (getopt (argc, argv, "a") != -1)
		openFlags = O_RDWR | O_CREAT | O_APPEND;
	else
		openFlags = O_RDWR | O_CREAT | O_TRUNC;
	
	fd = open(argv[1], openFlags,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1) {
        errExit("open");
	}
	
	/*         */
	
	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
        if (write(fd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
        totRead += numRead;
	}
    if (numRead == -1)
        errExit("read");
    
    /*         */
    if (lseek(fd, -totRead, SEEK_END) == -1)
		errExit("lseek");
    printf("seek succeeded\n");
	
	/*         */
	while ((numRead = read(fd, buf, BUF_SIZE)) > 0)
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
	
	if (close(fd) == -1)
        errExit("close");
}
