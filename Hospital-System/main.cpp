/* HEADERS */
#include <iostream>
#include "functions.h"
#include "helpers.h"
#include "globals.h"

sqlite3 *db;
const int SPECIALIZATIONS_NUM = 20;

int main()
{
    // open ,or create if doesn't exist, database and tables
    sqlite3_open("hospital.db", &db);
    createTables();
    // insert specializations' name if they don't exist
    insertSpecializations();
    // run system until exit
    while (true)
    {
        int option = menu();
        switch (option)
        {
        case 1:
            addNewPatient();
            break;
        case 2:
            printAllPatients();
            break;
        case 3:
            getNextPatient();
            break;
        case 4:
            return 0;
        default:
            std::cout << "Wrong Option!" << std::endl;
            break;
        }
    }
    // close database
    sqlite3_close(db);
    return 0;
}