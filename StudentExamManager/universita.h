#pragma once

#ifndef UNIVERSITA_H
#define UNIVERSITA_H

#include "list.h"

int readField(char buffer[], char sep, FILE* fp);

// ============ Lettura di studenti da file .txt ============
Studente leggi_uno_studente(FILE* fp);
list leggi_studenti(char* fileName);

// ============ Lettura di esami da file .txt ============
Esame leggi_un_esame(FILE* fp);
Esame* leggi_esami(char* fileName, int* dim);

// ============ Aggiornamento media e CFU degli studenti ============
float nuova_media_ponderata(Studente s, int voto, int cfu);
list aggiorna_studenti(list studenti, Esame* esami, int dim);

// ============ Ordinamento lista di studenti ============
int compare_studenti(Studente s1, Studente s2);
list mergeList(list l1, list l2);
void splitList(list l, list* a, list* b);
list mergeSortList(list l);

// ============ Ordinamento array di esami ============
int compare_esame(Esame e1, Esame e2);
void merge(Esame v[], int i1, int i2, int fine, Esame vuoto[]);
void mergeSort(Esame v[], int first, int last, Esame vuoto[]);
void ordina_esami(Esame* esami, int dim);

// ============ Statistiche per ogni corso ============
StatCorso* statistiche_corsi(Esame* esami, int dim, int* dimStat);

#endif