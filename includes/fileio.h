#ifndef FILEIO_H
#define FILEIO_H
#include <string.h>
#include "medicine.h"
#include "prescription.h"

void saveMedicines(Medicine *list, int count);
int loadMedicines(Medicine **list);
void savePrescriptions(PrescriptionManager *manager);
int loadPrescriptions(PrescriptionManager* manager);

#endif