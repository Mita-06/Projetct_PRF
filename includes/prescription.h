#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include "medicine.h"

typedef struct {
    int prescriptionID;
    char patientName[50];
    char pharmacistName[50];
    char medicineID[20];
    int quantity;
} Prescription;

void addPrescription(Prescription **list, int *n);
long dateToLong(char *dateStr);
int isDuplicatePrescriptionID(Prescription *list,int n,int id);
#endif