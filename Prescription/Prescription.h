#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#define MAX_PRESCRIPTIONS 100

typedef struct {
    int id;
    char patientName[50];
    char pharmacistName[50];
    char medicineId[20]; // Da thay doi thanh kieu chuoi (string)
    int quantity;
} Prescription;

typedef struct {
    Prescription list[MAX_PRESCRIPTIONS];
    int count;
} PrescriptionManager;

void initManager(PrescriptionManager* manager);
int addPrescription(PrescriptionManager* manager, Prescription p);
int deletePrescription(PrescriptionManager* manager, int id);
void displayPrescriptions(PrescriptionManager* manager);

#endif