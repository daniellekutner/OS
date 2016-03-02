//
// Created by danielle.kut on 2/25/16.
//
#include "osm.h"
#include <iostream>
using namespace std;
int main()
{
    osm_init();
    auto blah = measureTimes(10, 10, 10, 10);

    cout << "Machine Name: " << blah.machineName << endl;
    cout << "instructionTimeNanoSecond: " << blah.instructionTimeNanoSecond << endl;
    cout << "functionTimeNanoSecond: " << blah.functionTimeNanoSecond << endl;
    cout << "trapTimeNanoSecond: " << blah.trapTimeNanoSecond << endl;
    cout << "diskTimeNanoSecond: " << blah.diskTimeNanoSecond<< endl;
    cout << "functionInstructionRatio: " << blah.functionInstructionRatio << endl;
    cout << "trapInstructionRatio: " << blah.trapInstructionRatio << endl;
    cout << "diskInstructionRatio: " << blah.diskInstructionRatio << endl;

    osm_finalizer();


    return 0;
}
