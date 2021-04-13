#include <iostream>

/* CALLBACK FUNCTIONS */
int printSpecializationsCallback(void *data, int argc, char **argv, char **azColName)
{
    // print the specialization id, and name respectively
    std::cout << argv[0] << ". " << argv[1] << std::endl;
    return 0;
}

int getCountCallback(void *count, int argc, char **argv, char **azColName)
{
    // get count of tuples
    int *c = (int *)count;
    *c = atoi(argv[0]);
    return 0;
}

int getSpecializationNameCallback(void *name, int argc, char **argv, char **azColName)
{
    // get the name of specified specialization
    std::string *temp = (std::string *)name;
    *temp = argv[0];
    return 0;
}

int printAllPatientsCallback(void *data, int argc, char **argv, char **azColName)
{
    // print patient name, and status recpectively
    std::cout << "Name: " << argv[0] << ", Status: " << argv[1] << std::endl;
    return 0;
}

int printNextPatientCallback(void *data, int argc, char **argv, char **azColName)
{
    std::cout << argv[0] << " Please Go to the Dr." << std::endl;
    return 0;
}
