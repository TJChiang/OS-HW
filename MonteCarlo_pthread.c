#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int AmountPoint = 0;
int Circle = 0;

void *MCCircle(void *X)
{
    for (int i = 0; i < AmountPoint; i++)
    {
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;

        if (((X * X) + (Y * Y)) <= 1)
        {
            Circle++;
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    pthread_t thread;

    while (AmountPoint <= 0)
    {
        printf("Amout of Point:\n");
        scanf("%d", &AmountPoint);
    }
    pthread_create(&thread, NULL, &MCCircle, NULL);
    pthread_join(thread, NULL);

    double pi = 4.0 * Circle / AmountPoint;
    printf("The desired amount of points (%d) is: %f \n", AmountPoint, pi);
    return 0;
}
