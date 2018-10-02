#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 2048
#define READ_END 0
#define WRITE_END 1

int main(int argc, char const *argv[])
{
    int srcFile, dstFile;
    int FileDescription[2];
    pid_t childPid;
    char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));

    char* SourceFile = argv [1];
    char* DestinationFile = argv [2];
    
    // Src and dst file name arguments missing
    if (argc != 3)
    {
        printf("File missing\n");
        return -1;
    }

    // Create the pipe
    if (pipe(FileDescription) == -1)
    {
        fprintf(stderr, "Pipe Failed.\n");
        return 1;
    }

    // Fork a child process
    childPid = fork();

    // Error occurred
    if (childPid < 0)   // -1
    {
        fprintf(stderr, "Fork Failed.\n");
        return 1;
    }

    // Parent process Write
    if (childPid > 0)
    {
        // Close the unused end of the pipe
        close(FileDescription[READ_END]);

        // Create the source file
        int srcFile = open(SourceFile, O_RDONLY);
        if (srcFile == -1)
        {
            printf("Create source file failed.\n");
            return -1;
        }

        // Read the content of source file
        ssize_t inputBytes = read(srcFile, buffer, BUF_SIZE);

        
        // Write the content of source file to Write end
        ssize_t outputBytes = write(FileDescription[WRITE_END], buffer, inputBytes);

        if (inputBytes != outputBytes)
        {
            printf("Write end I/O does not match.\n");
            return -1;
        }
        

        // Close the write end of the pipe
        close(FileDescription[WRITE_END]);
    }
    else    //  Child process Read
    {
        // Close the unused end of the pipe
        close(FileDescription[WRITE_END]);

        // Read the content from parent end
        ssize_t ParentOutput = read(FileDescription[READ_END], buffer, BUF_SIZE);

        // Close the read end of the pipe
        close(FileDescription[READ_END]);

        // Create the destination file
        int dstFile = open(DestinationFile, O_WRONLY | O_CREAT, 0644);
        if (dstFile == -1)
        {
            fprintf(stderr, "Create destination file failed.\n");
            return 1;
        }

        // Write the content to destination file from parent end
        ssize_t WriteBytes = write(dstFile, buffer, ParentOutput);
        if (WriteBytes != ParentOutput)
        {
            fprintf(stderr, "Read end I/O does not match\n");
            return 1;
        }
    }

    free(buffer);

    return 0;
}
