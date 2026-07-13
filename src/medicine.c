#include <stdio.h>
#include <string.h>
#include "../includes/medicine.h"
#include "../includes/fileio.h"

// Khởi tạo
void initMedicineManager(MedicineManager* manager) {
    manager->count = 0;
}

// Tìm theo ID (chuỗi)
Medicine* findMedicineById(MedicineManager* manager, const char* id) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->medicines[i].id, id) == 0) {
            return &manager->medicines[i];
        }
    }
    return NULL;
}

// Thêm thuốc
int addMedicine(MedicineManager* manager, Medicine m) {
    if (manager->count >= MAX_MEDICINES) return 0;
    if (findMedicineById(manager, m.id) != NULL) return 0;

    manager->medicines[manager->count] = m;
    manager->count++;
    saveMedicines(manager->medicines, manager->count);
    return 1;
}

// Xóa thuốc
int deleteMedicine(MedicineManager* manager, const char* id) {
    int index = -1;
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->medicines[i].id, id) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return 0;

    for (int i = index; i < manager->count - 1; i++) {
        manager->medicines[i] = manager->medicines[i + 1];
    }
    manager->count--;
    saveMedicines(manager->medicines, manager->count);
    return 1;
}

// Cập nhật thuốc
int updateMedicine(MedicineManager* manager, Medicine m) {
    Medicine* current = findMedicineById(manager, m.id);
    if (current == NULL) return 0;

    strcpy(current->name, m.name);
    strcpy(current->category, m.category);
    current->quantity = m.quantity;
    current->price = m.price;
    strcpy(current->expiryDate, m.expiryDate);
    saveMedicines(manager->medicines, manager->count);
    return 1;
}

void findMedicineByName(MedicineManager* manager, const char* keyword) {
    int found = 0;
    printf("\n\033[33mResults for '%s':\033[0m\n", keyword);
    printf("%-10s %-25s %-15s %-8s %-10s %-12s\n", "ID", "Ten Thuoc", "Loai", "SL", "Gia", "Het Han");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < manager->count; i++) {
        if (strstr(manager->medicines[i].name, keyword) != NULL) {
            printf("%-10s %-25s %-15s %-8d %-10.2f %-12s\n",
                   manager->medicines[i].id,
                   manager->medicines[i].name,
                   manager->medicines[i].category,
                   manager->medicines[i].quantity,
                   manager->medicines[i].price,
                   manager->medicines[i].expiryDate);
            found = 1;
        }
    }
    if (!found) printf("\033[33mNo medicines found matching '%s'!\033[0m\n", keyword);
}

void sortByQuantity(MedicineManager* manager) {
    for (int i = 0; i < manager->count - 1; i++) {
        for (int j = i + 1; j < manager->count; j++) {
            if (manager->medicines[i].quantity > manager->medicines[j].quantity) {
                Medicine temp = manager->medicines[i];
                manager->medicines[i] = manager->medicines[j];
                manager->medicines[j] = temp;
            }
        }
    }
        saveMedicines(manager->medicines, manager->count);
    printf("\033[32mSort by quantity completed successfully!\033[0m\n");
}

// Hiển thị danh sách
void displayMedicines(MedicineManager* manager) {
   printf("\n======================================================================================\n");
    printf("                                     MEDICINE LIST\n");
    printf("======================================================================================\n");
    if (manager->count == 0) {
        printf("\033[33mNo medicines in the system!\033[0m\n");
        printf("======================================================================================\n");
        return;
    }
    printf("%-8s | %-20s | %-15s | %-8s | %-10s | %-10s\n", 
           "ID", "Medicine Name", "Category", "Quantity", "Price", "Expiry Date");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < manager->count; i++) {
        printf("%-8s | %-20s | %-15s | %-8d | %-10.2f | %-10s\n", 
               manager->medicines[i].id,
               manager->medicines[i].name,
               manager->medicines[i].category,
               manager->medicines[i].quantity,
               manager->medicines[i].price,
               manager->medicines[i].expiryDate);
    }
    printf("======================================================================================\n");
}