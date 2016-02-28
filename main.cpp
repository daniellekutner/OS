//
// Created by danielle.kut on 2/25/16.
//
#include "osm.h"
int main()
{
    osm_init();
    osm_operation_time(1000);
    osm_function_time(1000);
    osm_syscall_time(1000);
    osm_disk_time(1000);
    osm_finalizer();
    return 0;
}
