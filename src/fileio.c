#include <stdio.h>
#include <stdlib.h>

#include "../includes/fileio.h"
#include "../includes/prescription.h"
#include "../includes/medicine.h"

#define MEDICINE_FILE "data/medicines.dat"
#define PRESCRIPTION_FILE "data/prescriptions.dat"

void saveMedicines(Medicine *list, int count) {
    FILE *fp = fopen(MEDICINE_FILE, "w");
    if (fp == NULL) {
        printf("\033[31mCannot open %s for writing!\033[0m\n", MEDICINE_FILE);
        return;
    }
    
    for (int i = 0; i < count; i++) {
        // Ghi id dưới dạng chuỗi %s (ví dụ: MED001)
        fprintf(fp, "%s|%s|%s|%d|%.2f|%s\n",
                list[i].id,
                list[i].name,
                list[i].category,
                list[i].quantity,
                list[i].price,
                list[i].expiryDate);
    }
    
    fclose(fp);
    printf("\033[32mMedicines saved successfully to %s!\033[0m\n", MEDICINE_FILE);
}

int loadMedicines(Medicine **list) {
    FILE *fp = fopen(MEDICINE_FILE, "r");
    if (fp == NULL) {
        printf("\033[33mNotification: No medicine file found at %s.\033[0m\n", MEDICINE_FILE);
        *list = NULL;
        return 0;
    }

    char line[256];
    int capacity = 0;

    // Lần 1: Quét từ đầu đến hết file để đếm số lượng dòng thực tế
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) > 0) {
            capacity++;
        }
    }

    if (capacity == 0) {
        fclose(fp);
        *list = NULL;
        return 0;
    }

    // Cấp phát vùng nhớ động dựa trên số dòng (int capacity) vừa đếm được
    *list = (Medicine *)malloc(capacity * sizeof(Medicine));
    if (*list == NULL) {
        fclose(fp);
        return 0;
    }

    rewind(fp);
    int count = 0;

    // Lần 2: Quét trực tiếp từng dòng cho đến khi hết file
    while (count < capacity && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        // Quét chuỗi ID thuốc bằng định dạng %[^|] thay vì %d
        int parsed = sscanf(line, "%[^|]|%[^|]|%[^|]|%d|%f|%[^|]",
                            (*list)[count].id,
                            (*list)[count].name,
                            (*list)[count].category,
                            &(*list)[count].quantity,
                            &(*list)[count].price,
                            (*list)[count].expiryDate);
        if (parsed == 6) {
            count++;
        }
    }

    fclose(fp);
    printf("\033[32mMedicines loaded successfully (%d items)!\033[0m\n", count);
    return count; 
}

// --- QUẢN LÝ FILE PRESCRIPTION ---


void savePrescriptions(PrescriptionManager* manager) {
    FILE *fp = fopen(PRESCRIPTION_FILE, "w");
    if (fp == NULL) {
        printf("\033[31mError: Cannot open file '%s' for writing!\033[0m\n", PRESCRIPTION_FILE);
        return;
    }
    
    for (int i = 0; i < manager->count; i++) {
        // Ghi medicineId dưới dạng chuỗi %s
        fprintf(fp, "%d|%s|%s|%s|%d\n",
                manager->list[i].id,
                manager->list[i].patientName,
                manager->list[i].pharmacistName,
                manager->list[i].medicineId, 
                manager->list[i].quantity);
    }

    fclose(fp);
    printf("\033[32mPrescriptions saved successfully to '%s'!\033[0m\n", PRESCRIPTION_FILE);
}

int loadPrescriptions(PrescriptionManager* manager) {
    FILE *fp = fopen(PRESCRIPTION_FILE, "r");
    if (fp == NULL) {
        printf("\033[33mNotification: No prescription file found. Starting with 0 records.\033[0m\n");
        manager->count = 0;
        return 0;
    }

    manager->count = 0;
    char line[256];
    
    //  Quét trực tiếp từng dòng bằng fgets cho đến khi hết file hoặc đầy mảng tĩnh
    while (manager->count < MAX_PRESCRIPTIONS && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0; 
        
        // Bỏ qua nếu dòng trống
        if (strlen(line) == 0) continue;

        Prescription p;
        // Đọc medicineId bằng định dạng chuỗi %[^|]
        int parsed = sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%d",
                            &p.id,
                            p.patientName,
                            p.pharmacistName,
                            p.medicineId, 
                            &p.quantity);
        
        if (parsed == 5) {
            manager->list[manager->count] = p;
            manager->count++;
        }
    }

    fclose(fp);
    printf("\033[32mPrescriptions loaded successfully (%d items)!\033[0m\n", manager->count);
    return 1;
}