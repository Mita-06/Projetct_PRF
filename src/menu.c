#include <stdio.h>
#include "../includes/menu.h"
#include "../includes/medicine.h"
#include "../includes/prescription.h"

void mainMenu() {
    int choice;

    do {
        printf("\n");
        printf("=================================\n");
        printf(" PHARMACY MANAGEMENT SYSTEM\n");
        printf("=================================\n");
        printf("1. Medicine Management         \n");
        printf("2. Prescription Management     \n");
        printf("3. Exit                        \n");
        printf("=================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        printf("choice = %d\n", choice);
        switch(choice) {
            case 1:
            printf("DEBUG: Entering medicine menu\n");
                medicineMenu();
                break;
            case 2:
                printf("DEBUG: Entering prescription menu\n");
                prescriptionMenu();
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
        printf("\n=== MEDICINE MENU ===\n");
        printf("1. Add Medicine\n");
        printf("2. Display Medicines\n");
        printf("3. Search Medicine\n");
        printf("0. Back\n");
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
    } while(choice != 3);
}

void prescriptionMenu() {
    int choice;
    Prescription *list = NULL;
    int n = 0;
    loadPrescriptions(&list, &n);
    do {
        printf("\n--- MENU QUAN LY DON THUOC ---\n");
        printf("1. Them don thuoc moi\n");
        printf("2. Hien thi danh sach don thuoc\n");
        printf("3. Thoat va Luu du lieu\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addPrescription(&list, &n);
                break;
            case 2:
                displayPrescriptions(list, n);
                break;
            case 3:
                savePrescriptions(list, n);
                printf("Da luu du lieu. Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 3);
}