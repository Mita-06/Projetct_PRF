#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/prescription.h"

void addPrescription(Prescription **list, int *n) {
    *list = (Prescription *)realloc(*list, (*n + 1) * sizeof(Prescription));
    printf("Nhap ID don thuoc: ");
    scanf("%d", &(*list)[*n].prescriptionID);
    printf("Nhap ten benh nhan: ");
    scanf("%s", (*list)[*n].patientName);
    printf("Nhap ten duoc si: ");
    scanf("%s", (*list)[*n].pharmacistName);
    printf("Nhap ID thuoc: ");
    scanf("%s", (*list)[*n].medicineID);
    printf("Nhap so luong: ");
    scanf("%d", &(*list)[*n].quantity);
    (*n)++;
}

