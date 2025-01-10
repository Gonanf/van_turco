#include "libarbys/libarbys.hpp"

/**
 * @file mod.cpp
 *
 * @brief This file manages most of the microkernel basic features (Serial commands, executables, process, memory, etc)
 */

/**
 *
 */
typedef struct process{
    int PID;
    char *name;
    process *children;
};
