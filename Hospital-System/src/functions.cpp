#include <iostream>
#include "../headers/globals.h"
#include "../headers/helpers.h"
#include "../headers/callbacks.h"


/* MAIN FUNCTIONS */
void addNewPatient()
{
    // insert new patient in patients
    // get new patient details
    std::string buffer;
    Patient newPatient;
    std::cout << "Enter Patient Name: ";
    std::getline(std::cin, buffer);
    std::getline(std::cin, newPatient.name);
    std::cout << "Enter Specialization Number(Don't know? Enter 0 to Print them): ";
    std::cin >> newPatient.specialization;
    // print specializations if user entered 0
    if (newPatient.specialization == 0)
    {
        printSpecializations();
        std::cout << "Enter Specialization Number: ";
        std::cin >> newPatient.specialization;
    }
    // handle wrong specialization numbers (must be between 1 and specialization number)
    while (newPatient.specialization > SPECIALIZATIONS_NUM || newPatient.specialization < 1)
    {
        std::cout << "Wrong Specialization Number, Enter the Right One: ";
        std::cin >> newPatient.specialization;
    }
    std::cout << "Enter Patient Status ('urgent' or 'regular'): ";
    std::cin >> newPatient.status;
    // handle wrong statuses (must be regular or urgent)
    while (newPatient.status != "urgent" && newPatient.status != "regular")
    {
        std::cout << "Wrong Status, Enter the Right One: ";
        std::cin >> newPatient.status;
    }
    // get the nextID (unique key)
    int count = 0;
    char *ErrorMsg = 0;
    std::string sql = "select count(1) from patients";
    sqlite3_exec(db, sql.c_str(), getCountCallback, &count, &ErrorMsg);
    int nextID = count + 1;

    // insert the new patient and alert the user
    sql = "insert into patients(id, name, status, specialization_number) values(" + std::to_string(nextID) + ", '" + newPatient.name + "', '" + newPatient.status + "', " + std::to_string(newPatient.specialization) + ");";
    sqlite3_exec(db, sql.c_str(), 0, 0, &ErrorMsg);
    std::cout << "Patient Added Successfully!" << std::endl;
    std::cout << "---------------" << std::endl;
}

void printAllPatients()
{
    // print all patients in all specializations
    std::string sql;
    // for every specialization, print all its patients if exist
    for (int i = 1; i <= SPECIALIZATIONS_NUM; i++)
    {
        // get name of specialization
        std::string name;
        sql = "select name from specializations where id = " + std::to_string(i) + ";";
        sqlite3_exec(db, sql.c_str(), getSpecializationNameCallback, &name, 0);

        // get count of patients in specialization
        int count;
        sql = "select count(1) from patients where specialization_number = " + std::to_string(i) + ";";
        sqlite3_exec(db, sql.c_str(), getCountCallback, &count, 0);

        // if any patients exist, print them all.
        if (count)
        {
            std::cout << "There are " << count << " Patients in " << name << " Specialization (Number " << i << ")" << std::endl;
            sql = "select name, status from patients where specialization_number = " + std::to_string(i) + ";";
            sqlite3_exec(db, sql.c_str(), printAllPatientsCallback, 0, 0);
            std::cout << std::endl;
        }
    }
    std::cout << "---------------" << std::endl;
}

void getNextPatient()
{
    // get the next patient in a certain specialization
    int specialization;
    std::cout << "Enter Specialization Number(Don't know? Enter '0' to Print them): ";
    std::cin >> specialization;
    if (specialization == 0)
    {
        printSpecializations();
        std::cout << "Enter Specialization Number: ";
        std::cin >> specialization;
    }
    // get the count of patients in the specified specialization
    int count;
    std::string sql = "select count(1) from patients where specialization_number = " + std::to_string(specialization) + ";";
    sqlite3_exec(db, sql.c_str(), getCountCallback, &count, 0);
    // if any patients exist, get the next one. otherwise alert the user
    if (count)
    {
        // select the first patient and print its name
        sql = "select name from patients where specialization_number = " + std::to_string(specialization) + " order by status desc, id asc limit 1;";
        sqlite3_exec(db, sql.c_str(), printNextPatientCallback, 0, 0);
        // delete the first patient ,from db, who was printed
        sql = "delete from patients where specialization_number = " + std::to_string(specialization) + " order by status desc, id asc limit 1;";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    }
    else
    {
        std::cout << "No Patients at the Moment, Have Rest, Dr." << std::endl;
    }
    std::cout << "---------------" << std::endl;
}