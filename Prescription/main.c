#include <stdio.h>
#include "Prescription.h"

//-----------------------------------------------------
void displayMenu() {
    printf("\n=======================================================\n");
    printf("      PRESCRIPTION MANAGEMENT\n");
    printf("=======================================================\n");
    printf("1. Add Prescription\n");
    printf("2. Delete Prescription\n");
    printf("3. Display Prescriptions\n");
    printf("0. Exit\n");
    printf("=======================================================\n");
}

//-----------------------------------------------------
Prescription inputPrescription() {
    Prescription p;
    printf("Input Id: "); 
    scanf("%d", &p.id);
    
    printf("Input Patient Name: "); 
    scanf(" %[^\n]", p.patientName);
    
    printf("Input Pharmacist Name: "); 
    scanf(" %[^\n]", p.pharmacistName);
    
    // Da thay doi format nhap cho medicineId thanh chuoi
    printf("Input Medicine Id: "); 
    scanf(" %[^\n]", p.medicineId);
    
    printf("Input Quantity: "); 
    scanf("%d", &p.quantity);
    
    return p;
}

//-----------------------------------------------------
void processAdd(PrescriptionManager* manager) {
    Prescription p = inputPrescription();
    if (addPrescription(manager, p)) {
        printf("Add successfully!\n");
    } else {
        printf("Failed: ID exists or list is full!\n");
    }
}

//-----------------------------------------------------
void processDelete(PrescriptionManager* manager) {
    int id;
    printf("Input Prescription Id: "); 
    scanf("%d", &id);
    if (deletePrescription(manager, id)) {
        printf("Delete successfully!\n");
    } else {
        printf("Not found!\n");
    }
}

//-----------------------------------------------------
void processMenu(PrescriptionManager* manager, int choice) {
    switch (choice) {
        case 1: processAdd(manager); break;
        case 2: processDelete(manager); break;
        case 3: displayPrescriptions(manager); break;
        case 0: printf("Goodbye!\n"); break;
        default: printf("Invalid choice!\n");
    }
}

//-----------------------------------------------------
int main() {
    PrescriptionManager manager;
    initManager(&manager);
    int choice;
    do {
        displayMenu();
        printf("Your choice: ");
        scanf("%d", &choice);
        processMenu(&manager, choice);
    } while (choice != 0);
    return 0;
}