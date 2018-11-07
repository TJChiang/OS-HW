#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    int AmountPoint = 0;
    int Circle = 0;

    while (AmountPoint <= 0)
    {
        printf("Amout of Point:\n");
        scanf("%d", &AmountPoint);
    }

#pragma omp parallel for num_threads(8)
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
    }

    double pi = 4.0 * Circle / AmountPoint;
    printf("The desired amount of points (%d) is: %f \n", AmountPoint, pi);
    return 0;
}
