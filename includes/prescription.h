#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

typedef struct {
    int prescriptionID;
    char patientName[50];
    char pharmacistName[50];
    int medicineID;
    int quantity;
} Prescription;

// Nguyên mẫu hàm
void addPrescription(Prescription **list, int *n);
void displayPrescriptions(Prescription *list, int n);
void savePrescriptions(Prescription *list, int n);
void loadPrescriptions(Prescription **list, int *n);

#endif