#include <stdio.h>
#include <stdlib.h>

#include "../includes/fileio.h"

void saveMedicines(Medicine *list, int count) {
    FILE *fp = fopen("medicines.dat", "wb");
    if (fp == NULL) {
        printf("Cannot open medicines.dat\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(list, sizeof(Medicine), count, fp);
    fclose(fp);
    printf("Medicines saved successfully!\n");
}

int loadMedicines(Medicine **list) {
    FILE *fp = fopen("medicines.dat", "rb");
    if (fp == NULL) {
        printf("No medicine file found.\n");
        return 0;
    }
    int count;
    fread(&count, sizeof(int), 1, fp);
    *list = malloc(count * sizeof(Medicine));
    if (*list == NULL) {
        fclose(fp);
        return 0;
    }
    fread(*list, sizeof(Medicine), count, fp);
    fclose(fp);
    printf("Medicines loaded successfully!\n");
    return count;
}

void savePrescriptions(Prescription *list, int count) {
    FILE *fp = fopen("prescriptions.dat", "wb");
    if (fp == NULL) {
        printf("Cannot open prescriptions.dat\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(list, sizeof(Prescription), count, fp);
    fclose(fp);
    printf("Prescriptions saved successfully!\n");
}

int loadPrescriptions(Prescription **list) {
    FILE *fp = fopen("prescriptions.dat", "rb");
    if (fp == NULL) {
        printf("No prescription file found.\n");
        return 0;
    }
    int count;
    fread(&count, sizeof(int), 1, fp);
    *list = malloc(count * sizeof(Prescription));
    if (*list == NULL) {
        fclose(fp);
        return 0;
    }
    fread(*list, sizeof(Prescription), count, fp);
    fclose(fp);
    printf("Prescriptions loaded successfully!\n");
    return count;
}