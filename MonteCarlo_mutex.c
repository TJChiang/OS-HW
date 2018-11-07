#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int InCircle = 0;
int PointPerThread = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count(void* randSeed)
{
    int CircleThread = 0;
    unsigned int rand_state = rand();

    for (int i; i < PointPerThread; i++)
    {
        double X = rand_r(&rand_state) / (double)RAND_MAX;
        double Y = (double)rand() / RAND_MAX;

        if (((X * X) + (Y * Y)) < 1)
        {
            CircleThread++;
        }
    }

    // lock and accumulate points in circle per thread to global InCircle
    pthread_mutex_lock(&mutex);
    InCircle += CircleThread;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char** argv)
{
    srand(time((unsigned)NULL));

    int ThreadCount = 0;
    int AmountPoint = 0;

    while (AmountPoint <= 0 && ThreadCount <=0)
    {
        printf("Amount of points:\n");
        scanf("%d", &AmountPoint);
        printf("The number of thread:\n");
        scanf("%d", &ThreadCount);
    }

    PointPerThread = AmountPoint / ThreadCount;

    pthread_t *threads = malloc(ThreadCount * sizeof(pthread_t));
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    unsigned int* randSeed = (unsigned int*)malloc(2 * sizeof(unsigned int));
    for (int i = 0; i < ThreadCount; i++)
    {
        randSeed[0] = rand();
        randSeed[1] = rand();
        pthread_create(&threads[i], &attr, count, randSeed);
    }

    for (int i = 0; i < ThreadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);
    free(randSeed);

    double pi = 4.0 * InCircle / AmountPoint;
    printf("%d points: PI = %f", AmountPoint, pi);

    return 0;
}