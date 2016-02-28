//
// Created by danielle.kut on 2/25/16.
//
#include "osm.h"
#include <iostream>
using namespace std;
int main()
{
    osm_init();
    cout << osm_operation_time(100000)<< endl;
    cout << osm_function_time(100000) << endl;
    cout << osm_syscall_time(100000) << endl;
    cout << osm_disk_time(100000)<< endl;
    osm_finalizer();
    return 0;
}
