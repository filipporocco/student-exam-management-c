#include "universita.h"
#include <string.h>

int readField(char buffer[], char sep, FILE* fp) {

	int i = 0;
	char ch = fgetc(fp);

	while (ch != sep && ch != '\0' && ch != EOF && ch != '\n') {

		buffer[i] = ch;
		i++;
		ch = fgetc(fp);
	}

	buffer[i] = '\0';
	return ch;
}

// ============ Lettura di studenti da file .txt ============

Studente leggi_uno_studente(FILE* fp) {

	Studente s;
	int r, i = 0;

	if ((r = fscanf_s(fp, "%d", &(s.matricola))) == 1) {

		if ((r = readField(s.nome, '@', fp)) == '@') {

			if ((r = readField(s.cognome, '@', fp)) == '@') {

				if ((r = fscanf_s(fp, "%d %f", &(s.cfu), &(s.media))) != 2) {

					if (r == EOF) {

						strcpy_s(s.nome, MAX_CHAR_NOME, "EOF");
					}
					else {

						strcpy_s(s.nome, MAX_CHAR_NOME, "NA");
					}
				}
			}
			else {

				if (r == EOF) {

					strcpy_s(s.nome, MAX_CHAR_NOME, "EOF");
				}
				else {

					strcpy_s(s.nome, MAX_CHAR_NOME, "NA");
				}
			}
		}
		else {

			if (r == EOF) {

				strcpy_s(s.nome, MAX_CHAR_NOME, "EOF");
			}
			else {

				strcpy_s(s.nome, MAX_CHAR_NOME, "NA");
			}
		}
	}
	else {

		if (r == EOF) {

			strcpy_s(s.nome, MAX_CHAR_NOME, "EOF");
		}
		else {

			strcpy_s(s.nome, MAX_CHAR_NOME, "NA");
		}
	}

	if (strlen(s.nome) == 0 || strlen(s.cognome) == 0 || s.cfu < 3 || s.media < 18 || s.media > 30) {

		if (strlen(s.nome) == 0 || strlen(s.cognome) == 0 || (s.cfu != 0 && s.media != 0)) {

			strcpy_s(s.nome, MAX_CHAR_NOME, "NA");
		}
	}

	return s;
}

list leggi_studenti(char* fileName) {

	FILE* fp;
	list studenti = emptyList();
	Studente temp;

	if (fopen_s(&fp, fileName, "r") != 0) {

		printf("Errore in apertura del file \"%s\"\n", fileName);
		return emptyList();
	}

	do {

		temp = leggi_uno_studente(fp);

		if (strcmp(temp.nome, "EOF") && strcmp(temp.nome, "NA")) {

			studenti = cons(temp, studenti);
		}

	} while (strcmp(temp.nome, "EOF"));

	fclose(fp);
	return studenti;
}

// ============ Lettura di esami da file .txt ============

Esame leggi_un_esame(FILE* fp) {

	Esame e;
	int r;

	if ((r = readField(e.corso, '@', fp)) == '@') {

		if ((r = fscanf_s(fp, "%d %d %d\n", &(e.voto), &(e.studente), &(e.cfu))) != 3) {

			if (r == EOF) {

				strcpy_s(e.corso, MAX_CHAR_CORSO, "EOF");
			}
			else {

				strcpy_s(e.corso, MAX_CHAR_CORSO, "NA");
			}
		}
	}
	else {

		if (r == EOF) {

			strcpy_s(e.corso, MAX_CHAR_CORSO, "EOF");
		}
		else {

			strcpy_s(e.corso, MAX_CHAR_CORSO, "NA");
		}
	}

	if (strlen(e.corso) == 0 || e.cfu < 3 || e.cfu > 12 || e.voto < 18 || e.voto > 30) {

		strcpy_s(e.corso, MAX_CHAR_CORSO, "NA");
	}

	return e;
}

Esame* leggi_esami(char* fileName, int* dim) {

	FILE* fp;
	Esame* esami;
	Esame temp;
	int i = 0;

	(*dim) = 0;

	if (fopen_s(&fp, fileName, "r") != 0) {

		printf("Errore in apertura del file \"%s\"!\n", fileName);
		return NULL;
	}

	do {

		temp = leggi_un_esame(fp);

		if (strcmp(temp.corso, "EOF") && strcmp(temp.corso, "NA")) {

			(*dim)++;
		}

	} while (strcmp(temp.corso, "EOF"));

	if ((esami = (Esame*)malloc(sizeof(Esame) * (*dim))) == NULL) {

		printf("Allocation Error!\n");
		fclose(fp);
		return NULL;
	}

	rewind(fp);

	do {

		temp = leggi_un_esame(fp);

		if (strcmp(temp.corso, "EOF") && strcmp(temp.corso, "NA")) {

			esami[i] = temp;
			i++;
		}

	} while (i < (*dim) && strcmp(temp.corso, "EOF"));

	fclose(fp);
	return esami;
}

// ============ Aggiornamento media e CFU degli studenti ============

float nuova_media_ponderata(Studente s, int voto, int cfu) {

	float somma = (s.media) * (s.cfu);

	return ((somma + (voto * cfu)) / (cfu + s.cfu));
}

list aggiorna_studenti(list studenti, Esame* esami, int dim) {

	int i;
	list result = emptyList();
	element el;

	while (!empty(studenti)) {

		el = head(studenti);

		for (i = 0; i < dim; i++) {

			if (el.matricola == esami[i].studente) {

				el.media = nuova_media_ponderata(el, esami[i].voto, esami[i].cfu);
				el.cfu = el.cfu + esami[i].cfu;
			}
		}

		result = cons(el, result);
		studenti = tail(studenti);
	}

	return result;
}

// ============ Ordinamento lista di studenti ============

int compare_studenti(Studente s1, Studente s2) {

	int result;
	float m1 = s1.media, m2 = s2.media;

	if (m1 > m2) {

		result = -1;
	}
	else {

		if (m1 < m2) {

			result = 1;
		}
		else {

			result = 0;
		}
	}

	if (result == 0) {

		result = s2.cfu - s1.cfu;
	}

	if (result == 0) {

		result = strcmp(s1.cognome, s2.cognome);
	}

	if (result == 0) {

		result = strcmp(s1.nome, s2.nome);
	}

	return result;
}

list mergeList(list l1, list l2) {

	if (empty(l1)) {

		return l2;
	}
	if (empty(l2)) {

		return l1;
	}

	if (compare_studenti(head(l1), head(l2)) <= 0) {

		return cons(head(l1), mergeList(tail(l1), l2));
	}
	else {

		return cons(head(l2), mergeList(l1, tail(l2)));
	}

}

void splitList(list l, list* a, list* b) {

	list slow;
	list fast;

	if (empty(l) || empty(tail(l))) {

		*a = l;
		*b = emptyList();
		return;
	}

	slow = l;
	fast = tail(l);

	while (!empty(fast)) {

		fast = tail(fast);

		if (!empty(fast)) {

			slow = tail(slow);
			fast = tail(fast);
		}
	}

	*a = l;
	*b = slow->next;
	slow->next = NULL;
}

list mergeSortList(list l) {

	list a, b;

	if (empty(l) || empty(tail(l))) {

		return l;
	}

	splitList(l, &a, &b);

	a = mergeSortList(a);
	b = mergeSortList(b);

	return mergeList(a, b);
}

// ============ Ordinamento array di esami ============

int compare_esame(Esame e1, Esame e2) {

	int result = strcmp(e1.corso, e2.corso);

	if (result == 0) {

		result = e2.voto - e1.voto;
	}

	if (result == 0) {

		result = e1.studente - e2.studente;
	}

	return result;
}

void merge(Esame v[], int i1, int i2, int fine, Esame vuoto[]) {

	int i = i1, j = i2, k = i1;

	while (i <= i2 - 1 && j <= fine) {

		if (compare_esame(v[i], v[j]) < 0) {

			vuoto[k] = v[i];
			i++;
		}
		else {

			vuoto[k] = v[j];
			j++;
		}

		k++;
	}

	while (i <= i2 - 1) {

		vuoto[k] = v[i];
		i++;
		k++;
	}

	while (j <= fine) {

		vuoto[k] = v[j];
		j++;
		k++;
	}

	for (i = i1; i <= fine; i++) {

		v[i] = vuoto[i];
	}

}

void mergeSort(Esame v[], int first, int last, Esame vuoto[]) {

	int mid;

	if (first < last) {

		mid = (last + first) / 2;
		mergeSort(v, first, mid, vuoto);
		mergeSort(v, mid + 1, last, vuoto);
		merge(v, first, mid + 1, last, vuoto);
	}
}

void ordina_esami(Esame* esami, int dim) {

	Esame* vuoto;

	if ((vuoto = (Esame*)malloc(sizeof(Esame) * dim)) == NULL) {

		printf("Allocation Error!\n");
		return;
	}

	mergeSort(esami, 0, dim - 1, vuoto);
	free(vuoto);
}

// ============ Statistiche per ogni corso ============

StatCorso* statistiche_corsi(Esame* esami, int dim, int* dimStat) {

	StatCorso* s;
	int i, j, k = 0, somma;
	Bool stop;

	(*dimStat) = 0;

	for (i = 0; i < dim; i++) {

		stop = false;

		for (j = i + 1; j < dim && !stop; j++) {

			if (strcmp(esami[i].corso, esami[j].corso)) {

				stop = 1;
			}
		}

		(*dimStat)++;
		i = j - 1;
	}

	if ((s = (StatCorso*)malloc(sizeof(StatCorso) * (*dimStat))) == NULL) {

		printf("Allocation Error!\n");
		return NULL;
	}

	for (i = 0; k < (*dimStat) && i < dim; i++) {

		stop = false;
		s[k].iscritti = 1;
		somma = esami[i].voto;

		for (j = i + 1; j < dim && !stop; j++) {

			if (strcmp(esami[i].corso, esami[j].corso)) {

				stop = 1;
			}
			else {

				somma = somma + esami[j].voto;
				(s[k].iscritti)++;
			}
		}

		strcpy_s(s[k].corso, MAX_CHAR_CORSO, esami[i].corso);
		s[k].media = ((float)somma) / (s[k].iscritti);
		k++;
		i = j - 2;
	}

	return s;
}