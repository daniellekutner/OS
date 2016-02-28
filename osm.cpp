//
// Created by danielle.kut on 2/25/16.
//
#include <fcntl.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include "osm.h"
#define FAILED -1
#define DEFAULT_ITERATIONS 1000
#define SUCCESS 0

using namespace std;

static double checkLoopTime(unsigned int iterations)
{
    struct timeval start, end, sub;
    while (gettimeofday(&start, NULL) < 0 );
    for (int i = 0; i < iterations; i++)
    {
        // empty loop
    }
    while (gettimeofday(&end, NULL) < 0);
    timersub(&start, &end, &sub);
    return sub.tv_usec;
}

double calculateAvg(double value, unsigned int iterations)
{
    double avg = value / (double)iterations;
    double nanoTime = avg * DEFAULT_ITERATIONS;
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

}


/* finalizer function that the user must call
 * after running any other library function.
 * The function may, for example, free memory or
 * close/delete files.
 * Returns 0 uppon success and -1 on failure
 */
int osm_finalizer()
{

}


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations = DEFAULT_ITERATIONS) {
    try {
        validateIterations(iterations);
        double emptyLoopTime = checkLoopTime(iterations);
        int x, y, z;
        struct timeval start, end, sub;
        while (gettimeofday(&start, NULL) < 0 );
        for (int i = 0; i < iterations; i++) {
            x = 2 + 6;
            y = 10 + 6;
            z = 9 + 8;
        }
        while (gettimeofday(&end, NULL) < 0);
        timersub(&start, &end, &sub);
        double operationTime = sub.tv_usec - emptyLoopTime;
        double nanoTime = calculateAvg(operationTime, iterations);
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
    double emptyLoopTime = checkLoopTime(iterations);
    try {
        struct timeval start, end, sub;
        while (gettimeofday(&start, NULL) < 0);
        for (int i = 0; i < iterations; i++) {
            emptyFunc();
        }
        while (gettimeofday(&end, NULL) < 0);
        timersub(&start, &end, &sub);
        double operationTime = sub.tv_usec - emptyLoopTime;
        double nanoTime = calculateAvg(operationTime, iterations);
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
        double emptyLoopTime = checkLoopTime(iterations);
        struct timeval start, end, sub;
        while (gettimeofday(&start, NULL) < 0);
        for (int i = 0; i < iterations; i++)
        {
            OSM_NULLSYSCALL;
        }
        while (gettimeofday(&end, NULL) < 0);
        timersub(&start, &end, &sub);
        cout << sub.tv_usec << "\n" << emptyLoopTime << endl;
        double operationTime = sub.tv_usec - emptyLoopTime;
        double nanoAvgTime = calculateAvg(operationTime, iterations);
        cout << nanoAvgTime << endl; // TODO DEL this and check for more
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
    try {
        validateIterations(iterations);
        double emptyLoopTime = checkLoopTime(iterations);
        struct timeval start, end, sub;
        while (gettimeofday(&start, NULL) < 0);
        for (int i = 0; i < iterations; i++)
        {
            int fd = openat(AT_FDCWD, "file.txt", O_DIRECT);
            close(fd);
        }
        while (gettimeofday(&end, NULL) < 0);
        timersub(&start, &end, &sub);
        cout << sub.tv_usec << "\n" << emptyLoopTime << endl;
        double operationTime = sub.tv_usec - emptyLoopTime;
        double nanoAvgTime = calculateAvg(operationTime, iterations);
        cout << nanoAvgTime << endl; // TODO DEL this and check for more
        return nanoAvgTime;
    }
    catch (exception) // TODO check that exception is correct
    {
        return FAILED;
    }

}



timeMeasurmentStructure measureTimes (unsigned int operation_iterations,
                                      unsigned int function_iterations,
                                      unsigned int syscall_iterations,
                                      unsigned int disk_iterations)
{

}
