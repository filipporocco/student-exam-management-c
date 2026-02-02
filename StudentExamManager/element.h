#pragma once

#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>
#include <stdlib.h>

//Studente
#define MAX_CHAR_NOME 65
#define MAX_CHAR_COGNOME 65

//Esame & StatCorso
#define MAX_CHAR_CORSO 51

typedef struct {

	int matricola;
	char nome[MAX_CHAR_NOME], cognome[MAX_CHAR_COGNOME];
	int cfu;
	float media;

}Studente;

typedef struct {

	char corso[MAX_CHAR_CORSO];
	int voto, studente, cfu;

}Esame;

typedef struct {

	char corso[MAX_CHAR_CORSO];
	float media;
	int iscritti;

}StatCorso;

typedef Studente element;

typedef enum {

	false, true

}Bool;

#endif