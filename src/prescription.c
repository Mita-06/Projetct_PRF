#include <stdio.h>
#include "../includes/prescription.h"
#include "../includes/utils.h"

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

Prescription inputPrescription() {
    Prescription p;
    p.id = inputPositiveInt("Input Id: ");
    printf("Input Patient Name: "); 
    scanf(" %49[^\n]", p.patientName);
    clearInputBuffer();
    printf("Input Pharmacist Name: "); 
    scanf(" %49[^\n]", p.pharmacistName);
    clearInputBuffer();
    printf("Input Medicine Id: "); 
    scanf(" %49[^\n]", p.medicineId);
    clearInputBuffer();
    p.quantity = inputPositiveInt("Input Quantity: ");
    return p;
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
    printf("\n================================================================================\n");
    printf("                          PRESCRIPTION LIST\n");
    printf("================================================================================\n");
    if (manager->count == 0) {
        printf("\033[33mNo prescriptions available in the system!\033[0m\n");
        return;
    }
    printf("%-8s | %-15s | %-20s | %-12s | %-8s\n", 
           "ID", "Patient Name", "Pharmacist", "Medicine ID", "Quantity");
    printf("--------------------------------------------------------------------------------\n");

    // In từng dòng dữ liệu theo đúng khung độ rộng đã chia
    for (int i = 0; i < manager->count; i++) {
        printf("%-8d | %-15s | %-20s | %-12s | %-8d\n",
               manager->list[i].id,
               manager->list[i].patientName,
               manager->list[i].pharmacistName,
               manager->list[i].medicineId,
               manager->list[i].quantity);
    }
    printf("================================================================================\n");
}