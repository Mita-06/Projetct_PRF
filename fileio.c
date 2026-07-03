#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/fileio.h"

#define MEDICINE_FILE "../data/medicines.dat"
#define PRESCRIPTION_FILE "../data/prescriptions.dat"

// --- QUẢN LÝ FILE MEDICINE ---

void saveMedicines(Medicine *list, int count) {
    FILE *fp = fopen(MEDICINE_FILE, "w");
    if (fp == NULL) {
        printf("Cannot open %s for writing!\n", MEDICINE_FILE);
        return;
    }

    // Ghi số lượng thuốc ở dòng đầu tiên để phục vụ việc cấp phát động khi load
    fprintf(fp, "%d\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%d,%.2f,%s\n",
                list[i].id,
                list[i].name,
                list[i].category,
                list[i].quantity,
                list[i].price,
                list[i].expiryDate);
    }
    
    fclose(fp);
    printf("Medicines saved successfully to %s!\n", MEDICINE_FILE);
}

int loadMedicines(Medicine **list) {
    FILE *fp = fopen(MEDICINE_FILE, "r");
    if (fp == NULL) {
        printf("No medicine file found at %s.\n", MEDICINE_FILE);
        *list = NULL;
        return 0;
    }

    int count = 0;
    if (fscanf(fp, "%d\n", &count) != 1 || count <= 0) {
        fclose(fp);
        *list = NULL;
        return 0;
    }

    // Cấp phát bộ nhớ động dựa trên số lượng count đọc được từ dòng đầu
    *list = (Medicine *)malloc(count * sizeof(Medicine));
    if (*list == NULL) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        char line[200];
        if (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\r\n")] = 0; // Xóa ký tự xuống dòng
            
            // Đọc dữ liệu phân tách bằng dấu phẩy khớp với struct Medicine
            sscanf(line, "%[^,],%[^,],%[^,],%d,%f,%s",
                   (*list)[i].id,
                   (*list)[i].name,
                   (*list)[i].category,
                   &(*list)[i].quantity,
                   &(*list)[i].price,
                   (*list)[i].expiryDate);
        }
    }

    fclose(fp);
    printf("Medicines loaded successfully (%d items)!\n", count);
    return count;
}

// --- QUẢN LÝ FILE PRESCRIPTION ---

void savePrescriptions(Prescription *list, int count) {
    FILE *fp = fopen(PRESCRIPTION_FILE, "w");
    if (fp == NULL) {
        printf("Cannot open %s for writing!\n", PRESCRIPTION_FILE);
        return;
    }

    // Ghi số lượng đơn thuốc ở dòng đầu
    fprintf(fp, "%d\n", count);
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%d\n",
                list[i].prescriptionID,
                list[i].patientName,
                list[i].pharmacistName,
                list[i].medicineID,
                list[i].quantity);
    }

    fclose(fp);
    printf("Prescriptions saved successfully to %s!\n", PRESCRIPTION_FILE);
}

int loadPrescriptions(Prescription **list) {
    FILE *fp = fopen(PRESCRIPTION_FILE, "r");
    if (fp == NULL) {
        printf("No prescription file found at %s.\n", PRESCRIPTION_FILE);
        *list = NULL;
        return 0;
    }

    int count = 0;
    if (fscanf(fp, "%d\n", &count) != 1 || count <= 0) {
        fclose(fp);
        *list = NULL;
        return 0;
    }

    // Cấp phát bộ nhớ động cho danh sách đơn thuốc
    *list = (Prescription *)malloc(count * sizeof(Prescription));
    if (*list == NULL) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        char line[200];
        if (fgets(line, sizeof(line), fp)) {
            line[strcspn(line, "\r\n")] = 0;
            
            sscanf(line, "%d,%[^,],%[^,],%[^,],%d",
                   &(*list)[i].prescriptionID,
                   (*list)[i].patientName,
                   (*list)[i].pharmacistName,
                   (*list)[i].medicineID,
                   &(*list)[i].quantity);
        }
    }

    fclose(fp);
    printf("Prescriptions loaded successfully (%d items)!\n", count);
    return count;
}
