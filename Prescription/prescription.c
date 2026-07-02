#include <stdio.h>
#include "Prescription.h"

void initManager(PrescriptionManager* manager) {
    manager->count = 0;
}

int addPrescription(PrescriptionManager* manager, Prescription p) {
    if (manager->count >= MAX_PRESCRIPTIONS) {
        return 0;
    }
    
    // Kiem tra trung ID
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

    // Don mang
    for (int i = index; i < manager->count - 1; i++) {
        manager->list[i] = manager->list[i + 1];
    }
    manager->count--;
    return 1;
}

void displayPrescriptions(PrescriptionManager* manager) {
    printf("\nPrescription List\n");
    for (int i = 0; i < manager->count; i++) {
        printf("%d | %s | %s | %d | %d\n",
               manager->list[i].id,
               manager->list[i].patientName,
               manager->list[i].pharmacistName,
               manager->list[i].medicineId,
               manager->list[i].quantity);
    }
}
