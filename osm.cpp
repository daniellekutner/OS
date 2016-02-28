//
// Created by danielle.kut on 2/25/16.
//
#include "osm.h"
#define FAILED -1
#define DEFAULT_ITERATIONS 1000
#define SUCCESS 0

using namespace std;

FILE*pFile;


double calculateAvg(double value, unsigned int iterations)
{
    double avg = value / (double)iterations;
    double nanoTime = avg * 1000;
    return nanoTime;
}

void validateIterations(unsigned int &iterations)
{
    if (iterations == 0) {
        iterations = DEFAULT_ITERATIONS;
    }
}

/* Initialization function that the user must call
 * before running any other library function.
 * The function may, for example, allocate memory or
 * create/open files.
 * Returns 0 upon success and -1 on failure
 */
int osm_init()
{
    pFile = fopen("pFile.txt", "w");
    if (pFile == NULL)
    {
        return FAILED;
    }
    fputs("OS ex1 is soooo cool, we love OS give us a good grade :):):):):) ", pFile);
    fflush(pFile);
    return SUCCESS;
}


/* finalizer function that the user must call
 * after running any other library function.
 * The function may, for example, free memory or
 * close/delete files.
 * Returns 0 uppon success and -1 on failure
 */
int osm_finalizer()
{
    if(pFile != NULL)
    {
        fclose(pFile);
        return SUCCESS;
    }
    return FAILED;
}


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations = DEFAULT_ITERATIONS) {
    try {
        validateIterations(iterations);
        int x, y, z;
        struct timeval start, end, sub;
        double timeSum = 0;
        for (int i = 0; i < iterations; i++) {
            gettimeofday(&start, NULL);
            x = 2 + 6;
            y = 10 + 6;
            z = 9 + 8;
            gettimeofday(&end, NULL);
            timersub(&start, &end, &sub);
            timeSum += sub.tv_usec;
        }
        double nanoTime = calculateAvg(timeSum, iterations);
        cout << nanoTime << endl;
        return nanoTime;
    }
    catch (exception)
    {
        return FAILED;
    }
}

/*
 * empty function for inner use in osm_function_time
 */
static void emptyFunc()
{
    //Stays empty
}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations)
{
    validateIterations(iterations);
    try {
        struct timeval start, end, sub;
        double timeSum = 0;
        for (int i = 0; i < iterations; i++) {
            gettimeofday(&start, NULL);
            emptyFunc();
            gettimeofday(&end, NULL);
            timersub(&start, &end, &sub);
            timeSum += sub.tv_usec;
        }
        double nanoTime = calculateAvg(timeSum, iterations);
        cout << nanoTime << endl; //TODO DEL
        return nanoTime;
    }
    catch (exception) // TODO check that exception is correct
    {
        return FAILED;
    }
}


/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_syscall_time(unsigned int iterations)
{
    try {
        validateIterations(iterations);
        struct timeval start, end, sub;
        double timeSum = 0;
        for (int i = 0; i < iterations; i++)
        {
            gettimeofday(&start, NULL);
            OSM_NULLSYSCALL;
            gettimeofday(&end, NULL);
            timersub(&start, &end, &sub);
            timeSum += sub.tv_usec;
        }
        double nanoAvgTime = calculateAvg(timeSum, iterations);
        cout << nanoAvgTime << endl;
        return nanoAvgTime;
    }
    catch (exception) // TODO check that exception is correct
    {
        return FAILED;
    }

}

/* Time measurement function for accessing the disk.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_disk_time(unsigned int iterations)
{

    if(pFile == NULL)
    {
        return FAILED;
    }
    try {
        validateIterations(iterations);
        double timeSum = 0;
        struct timeval start, end, sub;
        for (int i = 0; i < iterations; i++)
        {
            gettimeofday(&start, NULL);
            fputs("OS ex1", pFile);
            gettimeofday(&end, NULL);
            timersub(&start, &end, &sub);
            timeSum += sub.tv_usec;
        }
        double nanoAvgTime = calculateAvg(timeSum, iterations);

        cout << nanoAvgTime << endl; // TODO DEL this and check for more
        return nanoAvgTime;
    }
    catch (exception) // TODO check that exception is correct
    {
        if (pFile != NULL)
        {
            fclose(pFile);
        }
        return FAILED;
    }
}
