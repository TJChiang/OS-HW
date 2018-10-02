#include "PIDManager.h"

int main(int argc, char const *argv[])
{
    int allocateMap = allocate_map();
    if (allocateMap == 1)
    {
        printf("Data Structure initialized.\n");
        int i = 0;

        // Create 30 processes
        while (i < 30) 
        {
            int pid = allocate_pid();
            //printf("Process %2d: pid = %d\n", i+1, pid);
            i++;
        }

        // Release test
        release_pid(300);
        printf("pid 300 released.\n");

        release_pid(299);

        release_pid(315);
        printf("pid 315 released.\n");

        // Allocate a few more processes after this release
        // Should be 300
        int pidA = allocate_pid();
        printf("Process: %d; Pid: %d\n", ++i, pidA);    

        // Should be 315
        int pidB = allocate_pid();
        printf("Process: %d; Pid: %d\n", ++i, pidB);
        
        // Should be 330
        int pidC = allocate_pid();
        printf("Process: %d; Pid: %d\n", ++i, pidC);

    }
    else
    {
        printf("Failed to initialize data structure.\n");
    }

    if (pidStatus)
    {
        free(pidStatus);
    }

    return 0;
}

// Create and initailizes a data structure for representing pids;
// Returns -1 if unsuccessful, 1 if successful
int allocate_map() 
{
    pidStatus = (int*)calloc(PID_SIZE,sizeof(int));

    if (pidStatus)
    {
        return 1;
    }

    return -1;
}

// Allocates and returns a pid
// Return -1 if unable to allocate a pid (all pids are in use)
int allocate_pid() 
{
    for (int i = 0; i < PID_SIZE; i++)
    {
        if (pidStatus[i] == 0)
        {
            pidStatus[i] = 1;
            return i + MIN_PID;
        }
    }

    return -1;
}

// Release a pid
void release_pid(int pid)
{
    if (!pidStatus || pid < MIN_PID || pid > MAX_PID)
    {
        return;
    }

    pidStatus[pid - MIN_PID] = 0;
}
