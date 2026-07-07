#include <stdio.h>
#include "../includes/menu.h"
#include "../includes/medicine.h"
#include "../includes/prescription.h"
#include "../includes/fileio.h"

void mainMenu() {
    int choice;

    PrescriptionManager pManager;
    initManager(&pManager);
    loadPrescriptions(&pManager);
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
                medicineMenu();
                break;
            case 2:
                // printf("DEBUG: Entering prescription menu\n");
                // prescriptionMenu();
                prescriptionMenu(&pManager);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 3);
}

void medicineMenu() {
    int choice;
    do {
        printf("\n");
        printf("=======================================================\n");
        printf("                    MEDICINE MENU\n");
        printf("=======================================================\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Search Medicine\n");
        printf("0. Back\n");
        printf("=======================================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                printf(" Displaying medicines\n");
                
                // displayMedicine();
                break;
            case 3:
                printf(" Searching medicine by ID\n");
                // printsearchMedicineByID();
                break;
            case 0:
                printf(">> Returning to welcome menu...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
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
                    printf("Failed: ID exists or list is full!\n");
                }
                break;
            }
            case 2: {
                int id;
                printf("Input Prescription Id to delete: "); 
                scanf("%d", &id);
                if (deletePrescription(manager, id)) {
                    printf("Delete successfully!\n");
                    savePrescriptions(manager);
                } else {
                    printf("Not found!\n");
                }
                break;
            }
            case 3:
                displayPrescriptions(manager);
                break;
            case 0:
                savePrescriptions(manager);
                printf(">> Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}