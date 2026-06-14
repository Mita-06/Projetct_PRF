#include <stdio.h>
#include <stdlib.h>
#include "prescription.h"

int main() {
    Prescription *list = NULL;
    int n = 0;
    int choice;

    // Tải dữ liệu cũ từ file
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

    // Giải phóng bộ nhớ trước khi thoát
    free(list); 
    return 0;
}