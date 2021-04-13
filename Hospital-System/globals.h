#ifndef GLOBALS
#define GLOBALS
#include <iostream>
#include <sqlite3.h>

/* GLOBAL VARIABLES */
extern sqlite3 *db;
extern const int SPECIALIZATIONS_NUM;
struct Patient
{
    std::string name, status;
    int specialization;
};

#endif