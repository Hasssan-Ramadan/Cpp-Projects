#ifndef CALLBACKS
#define CALLBACKS
extern int printSpecializationsCallback(void *data, int argc, char **argv, char **azColName);
extern int getCountCallback(void *count, int argc, char **argv, char **azColName);
extern int getSpecializationNameCallback(void *name, int argc, char **argv, char **azColName);
extern int printAllPatientsCallback(void *data, int argc, char **argv, char **azColName);
extern int printNextPatientCallback(void *data, int argc, char **argv, char **azColName);
#endif