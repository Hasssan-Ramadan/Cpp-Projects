#include <iostream>
#include <deque>
#include <vector>

using namespace std;

const int SPECIALIZATIONS_NUM = 20;
const string SPECIALIZATIONS[]{"Anesthetics", "Breast Screening", "Cardiology", "Ear, Nose and Throat", "Eldery Services", "Gastroenterology", "General Surgery", "Gynecology", "Hematology", "Neonatal Unit", "Neurology", "Nutrition and Dietetics", " Obstetrics and Gynecology Units", " Oncology", " Ophthalmology", " Orthopedics", " Physiotherapy", " Renal Unit", " Sexual Health", " Urology"};

struct Patient
{
    string name, status;
    int specialization;
};

vector<deque<Patient>> PATIENT_QUEUES(20);

void print_specializations()
{
    for (int idx = 0; idx < SPECIALIZATIONS_NUM; idx++)
        cout << idx + 1 << ". " << SPECIALIZATIONS[idx] << endl;
    cout << "---------------" << endl;
}

void add_new_patient()
{
    Patient newPatient;
    cout << "Enter Patient Name: ";
    getline(cin, newPatient.name);
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
    if (newPatient.status == "regular")
        PATIENT_QUEUES[newPatient.specialization - 1].push_back(newPatient);
    else if (newPatient.status == "urgent")
        PATIENT_QUEUES[newPatient.specialization - 1].push_front(newPatient);
    cout << "Patient Added Successfully!" << endl;
    cout << "---------------" << endl;
}

void print_all_patients()
{
    for (int i = 0; i < SPECIALIZATIONS_NUM; i++)
    {
        if (!PATIENT_QUEUES[i].empty())
        {
            cout << "There are " << PATIENT_QUEUES[i].size() << " Patients in " << SPECIALIZATIONS[i] << " Specialization (Number " << i + 1 << ")" << endl;
            for (auto patient : PATIENT_QUEUES[i])
            {
                cout << "Name: " << patient.name << ", Status: " << patient.status << endl;
            }
            cout << endl;
        }
    }
    cout << "---------------" << endl;
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
    if (PATIENT_QUEUES[specialization - 1].empty())
    {
        cout << "No Patients at the Moment, Have Rest, Dr." << endl;
    }
    else
    {
        Patient Next_patient = PATIENT_QUEUES[specialization - 1].front();
        PATIENT_QUEUES[specialization - 1].pop_front();
        cout << Next_patient.name << " Please Go to the Dr." << endl;
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
    return 0;
}