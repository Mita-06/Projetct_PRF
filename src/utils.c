#include <stdio.h>
#include "../includes/utils.h"

void clearInputBuffer() {
    while(getchar() != '\n');
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
}

int inputPositiveInt(const char *message) {
    int value;
    do {
        printf("%s", message);
        scanf("%d", &value);
        if(value < 0) {
            printf("Value must be positive!\n");
        }
    } while(value < 0);
    return value;
}

float inputPositiveFloat(const char *message) {
    float value;
    do {
        printf("%s", message);
        scanf("%f", &value);
        if(value < 0) {
            printf("Value must be positive!\n");
        }
    } while(value < 0);
    return value;
}