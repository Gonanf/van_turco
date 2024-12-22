/**
 * @file mod.cpp
 */

/**
 * 
 */
typedef struct {
    int PID;
    char* name;
    process* children;
} process;