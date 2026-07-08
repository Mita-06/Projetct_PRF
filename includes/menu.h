#ifndef MENU_H
#define MENU_H

#include "medicine.h"
#include "prescription.h"

void mainMenu();
void medicineMenu(MedicineManager* manager);
void prescriptionMenu(PrescriptionManager* manager); 
#endif