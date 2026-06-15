#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\includes\prescription.h"

void addPrescription(Prescription **list, int *n) {
    *list = (Prescription *)realloc(*list, (*n + 1) * sizeof(Prescription));
    
    printf("Nhap ID don thuoc: ");
    scanf("%d", &(*list)[*n].prescriptionID);
    printf("Nhap ten benh nhan: ");
    scanf(" %[^\n]s", (*list)[*n].patientName); // Dùng %[^\n] để nhập được cả khoảng trắng
    printf("Nhap ten duoc si: ");
    scanf(" %[^\n]s", (*list)[*n].pharmacistName);
    printf("Nhap ID thuoc: ");
    scanf("%d", &(*list)[*n].medicineID);
    printf("Nhap so luong: ");
    scanf("%d", &(*list)[*n].quantity);
    
    (*n)++;
}

void displayPrescriptions(Prescription *list, int n) {
    printf("\n%-5s | %-15s | %-15s | %-10s | %-8s\n", "ID", "Benh Nhan", "Duoc Si", "ID Thuoc", "So Luong");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d | %-15s | %-15s | %-10d | %-8d\n", 
               list[i].prescriptionID, list[i].patientName, list[i].pharmacistName, 
               list[i].medicineID, list[i].quantity);
    }
}

void savePrescriptions(Prescription *list, int n) {
    FILE *fp = fopen("prescriptions.dat", "wb"); // [cite: 8]
    if (fp) {
        fwrite(&n, sizeof(int), 1, fp);
        fwrite(list, sizeof(Prescription), n, fp);
        fclose(fp);
    }
}

void loadPrescriptions(Prescription **list, int *n) {
    FILE *fp = fopen("prescriptions.dat", "rb"); // [cite: 8]
    if (fp) {
        fread(n, sizeof(int), 1, fp);
        *list = (Prescription *)malloc((*n) * sizeof(Prescription)); // 
        fread(*list, sizeof(Prescription), *n, fp);
        fclose(fp);
    }
}