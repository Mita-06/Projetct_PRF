#ifndef MEDICINE_H
#define MEDICINE_H

#define MAX_MEDICINES 100
#define NAME_LENGTH 50

typedef struct {
    char id[50];              // Mã thuốc kiểu chuỗi
    char name[NAME_LENGTH];   // Tên thuốc
    char category[50];        // Loại thuốc
    int quantity;             // Số lượng
    float price;              // Giá tiền
    char expiryDate[20];   
} Medicine;

typedef struct {
    Medicine medicines[MAX_MEDICINES];
    int count;
} MedicineManager;

void initMedicineManager(MedicineManager* manager);
int addMedicine(MedicineManager* manager, Medicine medicine);
int deleteMedicine(MedicineManager* manager, const char* id);
int updateMedicine(MedicineManager* manager, Medicine medicine);
Medicine* findMedicineById(MedicineManager* manager, const char* id);
void findMedicineByName(MedicineManager* manager, const char* keyword);
void sortByQuantity(MedicineManager* manager);
void displayMedicines(MedicineManager* manager);

#endif