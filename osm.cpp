//
// Created by danielle.kut on 2/25/16.
//
#include <fcntl.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include "osm.h"
#include <math.h>

#define FAILED -1
#define DEFAULT_ITERATIONS 1000
#define TO_NANO 1000
#define SUCCESS 0
#define TO_MICRO 1000000
#define DEFAULT_BYTES 256

#define SYSCALL_LOOP_UNROLL 10.0
#define INSTRUCT_LOOP_UNROLL 6.0
#define FUNC_LOOP_UNROLL 10.0
#define DISK_LOOP_UNROLL 3.0

using namespace std;


timeMeasurmentStructure instance;

/**
 * calculate average time for a single operation
 */
static double calculateAvg(double value, unsigned int iterations)
{
    double avg = (value * TO_NANO) / (double)iterations;
    return avg;
}

/**
 *  check if number of iteration is valid. greater then 0.
 */
static void validateIterations(unsigned int &iterations)
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
    try
    {
        instance.machineName = (char *) malloc(DEFAULT_BYTES);
        int hostnameVal = gethostname(instance.machineName,
                                      sizeof(instance.machineName));
        if (hostnameVal < 0)
        {
            instance.machineName = NULL;
        }
        return SUCCESS;
    }
    catch(exception)
    {
        return FAILED;
    }
}


/* finalizer function that the user must call
 * after running any other library function.
 * The function may, for example, free memory or
 * close/delete files.
 * Returns 0 uppon success and -1 on failure
 */
int osm_finalizer()
{
    try{
        free(instance.machineName);
        return SUCCESS;
    }
    catch (exception)
    {
        return FAILED;
    }
}


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_operation_time(unsigned int iterations = DEFAULT_ITERATIONS) {
    try {
        validateIterations(iterations);
        int x = 0, y = 0, z = 0;
        struct timeval start, end;
        while (gettimeofday(&start, NULL) < 0 );
        unsigned int loopIterations = (unsigned int) ceil((double)iterations / INSTRUCT_LOOP_UNROLL);
        for (unsigned int i= 0; i < loopIterations; ++i) {
            x = x + 2;
            y = y + 10;
            z = z + 9;
            x = 0, y = 0, z = 0;
            (void)x;
            (void)y;
            (void)z;
        }
        while (gettimeofday(&end, NULL) < 0);
        double operationTime = ((end.tv_sec - start.tv_sec) * TO_MICRO) +
				(end.tv_usec - start.tv_usec);
        double nanoTime = calculateAvg(operationTime, iterations);
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
    return;
}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations)
{
    validateIterations(iterations);
    try {
        struct timeval start, end;
        while (gettimeofday(&start, NULL) < 0);
        unsigned int loopIterations = (unsigned int) ceil((double)iterations / FUNC_LOOP_UNROLL);
        for (unsigned int i= 0; i < loopIterations; ++i) {
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();
            emptyFunc();

        }
        while (gettimeofday(&end, NULL) < 0);
        double operationTime = ((end.tv_sec - start.tv_sec) * TO_MICRO) +
				(end.tv_usec - start.tv_usec);
        double nanoTime = calculateAvg(operationTime, iterations);
        return nanoTime;
    }
    catch (exception)
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
        struct timeval start, end;
        while (gettimeofday(&start, NULL) < 0);
        unsigned int loopIterations = (unsigned int) ceil((double)iterations / SYSCALL_LOOP_UNROLL);
        for (unsigned int i = 0; i < loopIterations; ++i)
        {
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;
            OSM_NULLSYSCALL;

        }
        while (gettimeofday(&end, NULL) < 0);
        double operationTime = ((end.tv_sec - start.tv_sec) * TO_MICRO) +
				(end.tv_usec - start.tv_usec);
        double nanoAvgTime = calculateAvg(operationTime, iterations);
        return nanoAvgTime;
    }
    catch (exception)
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
        struct timeval start, end;
        while (gettimeofday(&start, NULL) < 0);
        unsigned int loopIterations = (unsigned int) ceil((double)iterations / DISK_LOOP_UNROLL);
        for (unsigned int i= 0; i < loopIterations; ++i)
        {
            int fd;
            fd = open("/tmp/danielle_kut.txt", O_DIRECT|O_CREAT|O_TRUNC|O_SYNC, 0777);
            if(fd == -1)
            {
                return FAILED;
            }
            int unlinkRetVal = unlink("/tmp/danielle_kut.txt");
            int closeRetVal = close(fd);
            if (closeRetVal == -1 | unlinkRetVal == -1)
            {
                return FAILED;
            }
        }
        while (gettimeofday(&end, NULL) < 0);
        double operationTime = ((end.tv_sec - start.tv_sec) * TO_MICRO) +
				(end.tv_usec - start.tv_usec);
        double nanoAvgTime = calculateAvg(operationTime, iterations);
        return nanoAvgTime;
    }
    catch (exception)
    {
        return FAILED;
    }
}

/**
 *
 */
timeMeasurmentStructure measureTimes (unsigned int operation_iterations,
                                      unsigned int function_iterations,
                                      unsigned int syscall_iterations,
                                      unsigned int disk_iterations)
{
    instance.instructionTimeNanoSecond =
			osm_operation_time(operation_iterations);

    instance.functionTimeNanoSecond = osm_function_time(function_iterations);
    instance.trapTimeNanoSecond = osm_syscall_time(syscall_iterations);
    instance.diskTimeNanoSecond = osm_disk_time(disk_iterations);

    if (instance.instructionTimeNanoSecond > 0) {
        if (instance.functionTimeNanoSecond > 0)
        instance.functionInstructionRatio = instance.functionTimeNanoSecond /
                                            instance.instructionTimeNanoSecond;

        if (instance.trapTimeNanoSecond > 0)
        instance.trapInstructionRatio = instance.trapTimeNanoSecond /
                                        instance.instructionTimeNanoSecond;

        if (instance.diskTimeNanoSecond > 0)
        instance.diskInstructionRatio = instance.diskTimeNanoSecond /
                                        instance.instructionTimeNanoSecond;
    } else {
        instance.functionInstructionRatio = FAILED;

        instance.trapInstructionRatio = FAILED;

        instance.diskInstructionRatio = FAILED;
    }

    return instance;
}
