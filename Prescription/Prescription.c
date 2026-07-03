#include <stdio.h>
#include "Prescription.h"

void initManager(PrescriptionManager* manager) {
    manager->count = 0;
}

int addPrescription(PrescriptionManager* manager, Prescription p) {
    if (manager->count >= MAX_PRESCRIPTIONS) {
        return 0;
    }
    
    // Kiem tra trung ID don thuoc
    for (int i = 0; i < manager->count; i++) {
        if (manager->list[i].id == p.id) {
            return 0;
        }
    }

    manager->list[manager->count] = p;
    manager->count++;
    return 1;
}

int deletePrescription(PrescriptionManager* manager, int id) {
    int index = -1;
    for (int i = 0; i < manager->count; i++) {
        if (manager->list[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        return 0;
    }

    // Don mang sau khi xoa
    for (int i = index; i < manager->count - 1; i++) {
        manager->list[i] = manager->list[i + 1];
    }
    manager->count--;
    return 1;
}

void displayPrescriptions(PrescriptionManager* manager) {
    if (manager->count == 0) {
        printf("List is empty!\n");
        return;
    }
    
    printf("\nPrescription List\n");
    printf("%-5s | %-20s | %-20s | %-10s | %-8s\n", "ID", "Patient", "Pharmacist", "MedID", "Qty");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < manager->count; i++) {
        // Su dung %s cho medicineId thay vi %d
        printf("%-5d | %-20s | %-20s | %-10s | %-8d\n",
               manager->list[i].id,
               manager->list[i].patientName,
               manager->list[i].pharmacistName,
               manager->list[i].medicineId,
               manager->list[i].quantity);
    }
}