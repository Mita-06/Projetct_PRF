#ifndef FILEIO_H
#define FILEIO_H

#include "medicine.h"
#include "prescription.h"

void saveMedicines(Medicine *list, int count);
int loadMedicines(Medicine **list);
void savePrescriptions(Prescription *list, int count);
int loadPrescriptions(Prescription **list);

#endif