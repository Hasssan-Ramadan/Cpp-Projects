#include <iostream>
#include <deque>
#include <vector>
#include <sqlite3.h>

using namespace std;

const int SPECIALIZATIONS_NUM = 20;

struct Patient
{
    string name, status;
    int specialization;
};

sqlite3 *db;
vector<deque<Patient>> PATIENT_QUEUES(20);

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static int callback2(void *data, int argc, char **argv, char **azColName)
{
    cout << argv[0] << ". " << argv[1] << endl;
    return 0;
}

void print_specializations()
{
    char *ErrorMsg = 0;
    string sql = "SELECT * From SPECIALIZATIONS";
    sqlite3_exec(db, sql.c_str(), callback2, 0, &ErrorMsg);
    cout << "---------------" << endl;
}

static int rows_num_callback(void *count, int argc, char **argv, char **azColName)
{
    int *c = (int *)count;
    *c = atoi(argv[0]);
    return 0;
}

static int max_id_callback(void *max, int argc, char **argv, char **azColName)
{
    int *cMax = (int *)max;
    *cMax = atoi(argv[0]);
    return 0;
}

void add_new_patient()
{
    string buffer;
    Patient newPatient;
    cout << "Enter Patient Name: ";
    getline(cin, buffer);
    getline(cin, newPatient.name);
    cout << "Enter Specialization Number(Don't know? Enter 0 to Print them): ";
    cin >> newPatient.specialization;
    if (newPatient.specialization == 0)
    {
        print_specializations();
        cout << "Enter Specialization Number: ";
        cin >> newPatient.specialization;
    }
    while (newPatient.specialization > SPECIALIZATIONS_NUM || newPatient.specialization < 1)
    {
        cout << "Wrong Specialization Number, Enter the Right One: ";
        cin >> newPatient.specialization;
    }
    cout << "Enter Patient Status ('urgent' or 'regular'): ";
    cin >> newPatient.status;
    while (newPatient.status != "urgent" && newPatient.status != "regular")
    {
        cout << "Wrong Status, Enter the Right One: ";
        cin >> newPatient.status;
    }
    char *ErrorMsg = 0;
    string sql = "SELECT MAX(ID) FROM PATIENTS";
    int max;
    sqlite3_exec(db, sql.c_str(), max_id_callback, &max, &ErrorMsg);
    sql = "INSERT INTO PATIENTS(ID, NAME, STATUS, SPECIALIZATION_NUMBER) VALUES(" + to_string(max + 1) + ", '" + newPatient.name + "', '" + newPatient.status + "', " + to_string(newPatient.specialization) + ");";
    sqlite3_exec(db, sql.c_str(), callback, 0, &ErrorMsg);
    cout << "Patient Added Successfully!" << endl;
    cout << "---------------" << endl;
}

static int specialization_name_callback(void *name, int argc, char **argv, char **azColName)
{
    string *temp = (string *)name;
    *temp = argv[0];
    return 0;
}

static int print_all_callback(void *data, int argc, char **argv, char **azColName)
{
    cout << "Name: " << argv[0] << ", Status: " << argv[1] << endl;
    return 0;
}

void print_all_patients()
{
    string sql;
    for (int i = 1; i <= SPECIALIZATIONS_NUM; i++)
    {
        int count;
        sql = "SELECT COUNT(*) FROM PATIENTS WHERE SPECIALIZATION_NUMBER = " + to_string(i) + ";";
        sqlite3_exec(db, sql.c_str(), rows_num_callback, &count, 0);
        string name;
        sql = "SELECT NAME FROM SPECIALIZATIONS WHERE ID = " + to_string(i) + ";";
        sqlite3_exec(db, sql.c_str(), specialization_name_callback, &name, 0);
        if (count)
        {
            cout << "There are " << count << " Patients in " << name << " Specialization (Number " << i << ")" << endl;
            sql = "SELECT NAME, STATUS FROM PATIENTS WHERE SPECIALIZATION_NUMBER = " + to_string(i) + ";";
            sqlite3_exec(db, sql.c_str(), print_all_callback, 0, 0);
            cout << endl;
        }
    }
    cout << "---------------" << endl;
}

static int print_name_callback(void *data, int argc, char **argv, char **azColName)
{
    cout << argv[0] << " Please Go to the Dr." << endl;
    return 0;
}

void get_next_patient()
{
    int specialization;
    cout << "Enter Specialization Number(Don't know? Enter '0' to Print them): ";
    cin >> specialization;
    if (specialization == 0)
    {
        print_specializations();
        cout << "Enter Specialization Number: ";
        cin >> specialization;
    }
    int count;
    string sql = "SELECT COUNT(*) FROM PATIENTS WHERE SPECIALIZATION_NUMBER = " + to_string(specialization) + ";";
    sqlite3_exec(db, sql.c_str(), rows_num_callback, &count, 0);
    if (count)
    {
        sql = "SELECT NAME FROM PATIENTS WHERE SPECIALIZATION_NUMBER = " + to_string(specialization) + " ORDER BY STATUS DESC, ID ASC LIMIT 1;";
        sqlite3_exec(db, sql.c_str(), print_name_callback, 0, 0);
        sql = "DELETE FROM PATIENTS WHERE SPECIALIZATION_NUMBER = " + to_string(specialization) + " ORDER BY STATUS DESC, ID ASC LIMIT 1;";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    }
    else
    {
        cout << "No Patients at the Moment, Have Rest, Dr." << endl;
    }
    cout << "---------------" << endl;
}

int menu()
{
    int option;
    cout << "Hospital Managment System" << endl
         << "Enter your Choice:" << endl
         << "1. Add New Patient." << endl
         << "2. Print All Patients." << endl
         << "3. Get Next Patient." << endl
         << "4. Exit" << endl
         << "---------------" << endl;
    cin >> option;
    return option;
}

int main()
{
    string sql;
    const string SPECIALIZATIONS[]{"Anesthetics", "Breast Screening", "Cardiology", "Ear, Nose and Throat", "Eldery Services", "Gastroenterology", "General Surgery", "Gynecology", "Hematology", "Neonatal Unit", "Neurology", "Nutrition and Dietetics", " Obstetrics and Gynecology Units", " Oncology", " Ophthalmology", " Orthopedics", " Physiotherapy", " Renal Unit", " Sexual Health", " Urology"};
    sqlite3_open("hospital.db", &db);
    sql = "CREATE TABLE SPECIALIZATIONS(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);"
          "CREATE TABLE PATIENTS(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL, STATUS TEXT NOT NULL, SPECIALIZATION_NUMBER INT NOT NULL, FOREIGN KEY(SPECIALIZATION_NUMBER) REFERENCES SPECIALIZATIONS(ID));";
    sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    for (int i = 1; i < SPECIALIZATIONS_NUM; i++)
    {
        sql = "INSERT INTO SPECIALIZATIONS(ID,NAME) VALUES(" + to_string(i) + ",'" + SPECIALIZATIONS[i - 1] + "');";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    }

    while (true)
    {
        int option = menu();
        switch (option)
        {
        case 1:
            add_new_patient();
            break;
        case 2:
            print_all_patients();
            break;
        case 3:
            get_next_patient();
            break;
        case 4:
            return 0;
        default:
            cout << "Wrong Option!" << endl;
            break;
        }
    }
    sqlite3_close(db);
    return 0;
}