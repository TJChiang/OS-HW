#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
    int srcFile, dstFile;    /* Input and output of file description */
    ssize_t inputBytes, outputBytes;        /* Bytes returned by read() and write() */
    char* buffer = (char*)calloc(BUF_SIZE,sizeof(char)) ;          /* Character buffer */

    /* Are src and dest file name arguments missing */
    if (argc != 3) {
        printf("Missing file\n");
        return -1;
    }

    /* Create input file descriptor */
    srcFile = open(argv [1], O_RDONLY);
    if (srcFile == -1) 
    {
        printf("Create source file Failed\n");
        return -1;
    }

    // open output file, with write only and create mode
    // 0(skip)6(User)4(Group)4(Other)means:
    // rwx oct    meaning
    // --- ---    -------
    // 001 01   = execute
    // 010 02   = write
    // 011 03   = write & execute
    // 100 04   = read
    // 101 05   = read & execute
    // 110 06   = read & write
    // 111 07   = read & write & execute
    // also can be written with "-rw-r--r--".
    
    /* Create output file descriptor */
    dstFile = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (dstFile == -1) 
    {
        printf("Create distination file Failed\n");
        return -1;
    }

    /* Copy process */
    while((inputBytes = read(srcFile, buffer, BUF_SIZE)) > 0) 
    {
        outputBytes = write(dstFile, buffer, inputBytes);
        if (inputBytes != outputBytes) {
            /* Write error */
            printf("I/O dose not match.\n");
            return -1;
        }
    }

    printf("Copy success.\n");

    /* Close file descriptions */
    close(srcFile);
    close(dstFile);

    free(buffer);

    return 0;
}
