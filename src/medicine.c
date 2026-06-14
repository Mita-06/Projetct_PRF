#include <stdio.h>
#include <string.h>
#include "../includes/medicine.h"

void inputMedicine(Medicine *m) {
    printf("Enter medicine ID: ");
    scanf("%s", m->id);

    getchar();

    printf("Enter medicine name: ");
    fgets(m->name, 50, stdin);
    m->name[strlen(m->name) - 1] = '\0';

    printf("Enter category: ");
    fgets(m->category, 30, stdin);
    m->category[strlen(m->category) - 1] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &m->quantity);

    printf("Enter price: ");
    scanf("%f", &m->price);

    printf("Enter expiry date (YYYY-MM-DD): ");
    scanf("%s", m->expiryDate);
}

void displayMedicine(Medicine m) {
    printf("\n----- Medicine Information -----\n");
    printf("ID: %s\n", m.id);
    printf("Name: %s\n", m.name);
    printf("Category: %s\n", m.category);
    printf("Quantity: %d\n", m.quantity);
    printf("Price: %.2f\n", m.price);
    printf("Expiry Date: %s\n", m.expiryDate);
}
