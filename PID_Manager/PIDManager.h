#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_PID 300
#define MAX_PID 5000
#define PID_SIZE (MAX_PID - MIN_PID + 1)

int* pidStatus;
