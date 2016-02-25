//
// Created by danielle.kut on 2/25/16.
//
#include "osm.h"

#define FAILED -1

#define DEFAULT_ITERATIONS 1000
#define CONVERT_TO_NANO(x) (x * 1000) //TODO FIX YONIS MACRO

using namespace std;

/* Initialization function that the user must call
 * before running any other library function.
 * The function may, for example, allocate memory or
 * create/open files.
 * Returns 0 uppon success and -1 on failure
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
        if (iterations == 0) {
            iterations = DEFAULT_ITERATIONS;
        }
        int x, y, z;
        struct timeval start, end, sub;
        gettimeofday(&start, NULL);
        for (int i = 0; i < iterations; i++) {
            x = 2 + 6;
            y = 10 + 6;
            z = 9 + 8;
        }
        gettimeofday(&end, NULL);
        timersub(&start, &end, &sub);
        double nanoTime = CONVERT_TO_NANO(sub.tv_usec);
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

}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   */
double osm_function_time(unsigned int iterations)
{
    try {
        if (iterations == 0) {
            iterations = DEFAULT_ITERATIONS;
        }
        struct timeval start, end, sub;
        gettimeofday(&start, NULL);
        for (int i = 0; i < iterations; i++) {
            emptyFunc();
        }
        gettimeofday(&end, NULL);
        timersub(&start, &end, &sub);
        double nanoTime = CONVERT_TO_NANO(sub.tv_usec);
        cout << nanoTime << endl;
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
        if (iterations == 0) {
            iterations = DEFAULT_ITERATIONS;
        }
        struct timeval start, end, sub;
        gettimeofday(&start, NULL);
        for (int i = 0; i < iterations; i++)
        {
            int returnVal = OSM_NULLSYSCALL;
        }
        gettimeofday(&end, NULL);
        timersub(&start, &end, &sub);
        double nanoTime = CONVERT_TO_NANO(sub.tv_usec);
        cout << nanoTime << endl;
        return nanoTime;
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

}

