#include <iostream>
#include <sqlite3.h>
#include "callbacks.h"
#include "globals.h"


/* HELPER FUNCTIONS */
void printSpecializations()
{
    // print all specializations
    char *ErrorMsg = 0;
    std::string sql = "select * from specializations";
    sqlite3_exec(db, sql.c_str(), printSpecializationsCallback, 0, &ErrorMsg);
    std::cout << "---------------" << std::endl;
}
void createTables()
{
    // create tables (specializations, patients)
    std::string sql = "create table specializations(id int primary key not null, name text not null);"
                      "create table patients(id int primary key not null, name text not null, status text not null, specialization_number int not null, foreign key(specialization_number) references specializations(id));";
    sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}

void insertSpecializations()
{
    const std::string SPECIALIZATIONS[]{"Anesthetics", "Breast Screening", "Cardiology", "Ear, Nose and Throat", "Eldery Services", "Gastroenterology", "General Surgery", "Gynecology", "Hematology", "Neonatal Unit", "Neurology", "Nutrition and Dietetics", " Obstetrics and Gynecology Units", " Oncology", " Ophthalmology", " Orthopedics", " Physiotherapy", " Renal Unit", " Sexual Health", " Urology"};

    // insert intial data in specializations table
    for (int i = 1; i <= SPECIALIZATIONS_NUM; i++)
    {
        std::string sql = "insert into specializations(id,name) values(" + std::to_string(i) + ",'" + SPECIALIZATIONS[i - 1] + "');";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    }
}

int menu()
{
    // print menu and return option
    int option;
    std::cout << "Hospital Managment System" << std::endl
              << "Enter your Choice:" << std::endl
              << "1. Add New Patient." << std::endl
              << "2. Print All Patients." << std::endl
              << "3. Get Next Patient." << std::endl
              << "4. Exit" << std::endl
              << "---------------" << std::endl;
    std::cin >> option;
    return option;
}
