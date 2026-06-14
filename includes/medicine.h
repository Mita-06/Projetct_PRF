#ifndef MEDICINE_H
#define MEDICINE_H


typedef struct {
    char id[20];
    char name[50];
    char category[30];
    int quantity;
    float price;
    char expiryDate[15];
} Medicine;

void inputMedicine(Medicine *m);
void displayMedicine(Medicine m);
void addMedicine();
#endif
