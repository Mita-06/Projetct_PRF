#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/menu.h"
#include "../includes/medicine.h"
#include "../includes/prescription.h"
#include "../includes/fileio.h"

void mainMenu() {
    int choice;

    PrescriptionManager pManager;
    initManager(&pManager);
    loadPrescriptions(&pManager);

    MedicineManager mManager;
    initMedicineManager(&mManager);
    Medicine* tempNewList = NULL;
    int loadedMedicinesCount = loadMedicines(&tempNewList);
    if (loadedMedicinesCount > 0 && tempNewList != NULL) {
        for (int i = 0; i < loadedMedicinesCount && i < MAX_MEDICINES; i++) {
            mManager.medicines[i] = tempNewList[i];
            mManager.count++;
        }
        free(tempNewList); 
    }
    do {
        printf("\n");
        printf("=======================================================\n");
        printf("              PHARMACY MANAGEMENT SYSTEM\n");
        printf("=======================================================\n");
        printf("1. Medicine Management         \n");
        printf("2. Prescription Management     \n");
        printf("3. Exit                        \n");
        printf("=======================================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        printf("choice = %d\n", choice);
        switch(choice) {
            case 1:
                medicineMenu(&mManager);
                break;
            case 2:
                prescriptionMenu(&pManager);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("\033[31mInvalid choice!\033[0m\n");
        }
    } while(choice != 3);
}

void medicineMenu(MedicineManager* manager) {
    int choice;
    do {
        printf("\n");
        printf("=======================================================\n");
        printf("                    MEDICINE MENU\n");
        printf("=======================================================\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Find Medicine By Name\n");
        printf("4. Find Medicine By ID\n");
        printf("5. Update Medicine Info\n");
        printf("6. Delete Medicine\n");
        printf("7. Sort By Quantity\n");
        printf("0. Back\n");
        printf("=======================================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        switch(choice) {
            case 1:{
                Medicine m;
                rewind(stdin);
                printf("Input ID (Ex: MED001): ");
                scanf(" %[^\n]", m.id);
                printf("Input Medicine Name: ");
                scanf(" %[^\n]", m.name);
                printf("Input Category: ");
                scanf(" %[^\n]", m.category);
                printf("Input Quantity: ");
                scanf("%d", &m.quantity);
                printf("Input Price: ");
                scanf("%f", &m.price);
                printf("Input Expiry Date (dd/mm/yyyy): ");
                scanf(" %[^\n]", m.expiryDate);
                
                if (addMedicine(manager, m)) {
                    printf("\033[32mAdd medicine successfully!\033[0m\n");
                } else {
                    printf("\033[31mFailed: Medicine ID already exists or list is full!\033[0m\n");
                }
                break;
            }
            case 2:                
                displayMedicines(manager);
                break;
            case 3:{
                char keyword[50];
                printf("Input medicine name to search: ");
                scanf(" %[^\n]", keyword);
                findMedicineByName(manager, keyword);
                break;
            }
            case 4:{
                char id[50];
                printf("Input the exact Medicine ID to search: ");
                scanf(" %[^\n]", id);
                
                Medicine* ptr = findMedicineById(manager, id);
                if (ptr != NULL) {
                    printf("\nInformation of the found medicine:\n");
                    printf("%-10s %-25s %-15s %-8s %-10s %-12s\n", "ID", "Medicine Name", "Category", "Quantity", "Price", "Expiry Date");
                    printf("--------------------------------------------------------------------------------\n");
                    
                    Medicine targetMed = *ptr; 
                    printf("%-10s %-25s %-15s %-8d %-10.2f %-12s\n",
                            targetMed.id, targetMed.name, targetMed.category, targetMed.quantity, targetMed.price, targetMed.expiryDate);
                } else {
                    printf("\033[31mFailed to find medicine with ID '%s'!\033[0m\n", id);
                }
                break;
            }
            case 5:{
                Medicine m;
                rewind(stdin);
                printf("Input the Medicine ID to update: ");
                scanf(" %[^\n]", m.id);
                printf("Input the new Medicine Name: ");
                scanf(" %[^\n]", m.name);
                printf("Input the new Category: ");
                scanf(" %[^\n]", m.category);
                printf("Input the new Quantity: ");
                scanf("%d", &m.quantity);
                printf("Input the new Price: ");
                scanf("%f", &m.price);
                printf("Input the new Expiry Date (dd/mm/yyyy): ");
                scanf(" %[^\n]", m.expiryDate);

                if (updateMedicine(manager, m)) {
                    printf("\033[32mUpdate medicine information successfully!\033[0m\n");
                } else {
                    printf("\033[31mFailed to find medicine with ID '%s'!\033[0m\n", m.id);
                }    
                break;
            }
            case 6:{
                char id[50];
                printf("Input the Medicine ID to delete: ");
                scanf(" %[^\n]", id);
                if (deleteMedicine(manager, id)) {
                    printf("\033[32mDelete medicine successfully!\033[0m\n");
                } else {
                    printf("\033[31mFailed to find medicine with ID '%s'!\033[0m\n", id);
                }
                break;      
            }
            case 7:
                sortByQuantity(manager);
                break;
            case 0:
                printf(">> Returning to welcome menu...\n");
                break;
                
            default:
                printf("\033[31mInvalid choice!\033[0m\n");
        }
    } while(choice != 0);
}


void prescriptionMenu(PrescriptionManager* manager) {
    int choice;
    do {
        printf("\n=======================================================\n");
        printf("                 PRESCRIPTION MANAGEMENT\n");
        printf("=======================================================\n");
        printf("1. Add Prescription\n");
        printf("2. Delete Prescription\n");
        printf("3. Display Prescriptions\n");
        printf("0. Back\n");
        printf("=======================================================\n");
        printf("Your choice: ");
        rewind(stdin); // Xóa sạch mọi ký tự dư thừa trong bộ đệm bàn phím
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Prescription p = inputPrescription();
                if (addPrescription(manager, p)) {
                    printf("Add successfully!\n");
                    savePrescriptions(manager);
                } else {
                    printf("\033[31mFailed: ID exists or list is full!\033[0m\n");
                }
                break;
            }
            case 2: {
                int id;
                printf("Input Prescription Id to delete: "); 
                scanf("%d", &id);
                if (deletePrescription(manager, id)) {
                    printf("\033[32mDelete successfully!\033[0m\n");
                    savePrescriptions(manager);
                } else {
                    printf("\033[31mNot found!\033[0m\n");
                }
                break;
            }
            case 3:
                displayPrescriptions(manager);
                break;
            case 0:
                savePrescriptions(manager);
                printf("\033[33m>> Returning to main menu\033[0m\n");
                break;
            default:
                printf("\033[31mInvalid choice!\033[0m\n");
        }
    } while (choice != 0);
}