#include <stdio.h>
#include "../includes/utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
}

int inputPositiveInt(const char *message) {
    int value;
    int valid =0;
    do {
        printf("%s", message);
        if (scanf("%d", &value) != 1) {
            printf("Loi: Vui long nhap mot so nguyen.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        if(value < 0) {
            printf("Value must be positive!\n");
            continue;
        }
        valid = 1;
    } while(!valid);
    return value;
}

float inputPositiveFloat(const char *message) {
    float value;
    int valid =0;
    do {
        printf("%s", message);
        if (scanf("%f", &value) != 1) {
            printf("Loi: Vui long nhap mot so thuc.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        if(value < 0) {
            printf("Value must be positive!\n");
            continue;
        }
        valid = 1;
    } while(!valid);
    return value;
}