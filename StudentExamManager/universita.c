#include "universita.h"
#include <string.h>

void welcome(char* file_studenti, char *file_esami, char* username) {

	printf("Welcome to the Student and Exam Management program!\n\n");

	printf("Please enter your username (Max 32 characters, no spaces): ");
	scanf_s("%s%*c", username, MAX_CHAR_USERNAME);

	printf("Enter the name of the text file containing the students: ");
	scanf_s("%s%*c", file_studenti, MAX_CHAR_FILE_NAME);
	printf("Enter the name of the text file containing the exams: ");
	scanf_s("%s%*c", file_esami, MAX_CHAR_FILE_NAME);

	printf("\n\n");
}

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

list leggi_studenti(char* file_studenti) {

	FILE* fp;
	list studenti = emptyList();
	Studente temp;

	if (fopen_s(&fp, file_studenti, "r") != 0) {

		printf("\nError opening file \"%s\"\n", file_studenti);
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

void showListStudenti(list l) {

	int cont = 0;
	element el;

	printf("\n----------------------------------------------------------------------------------------------------------\n");
	printf("%-8s | %-32s | %-32s | %-5s | %-5s\n", "ID", "Name", "Surname", "CFU", "Weighted average");
	printf("----------------------------------------------------------------------------------------------------------\n");

	while (!empty(l)) {

		el = head(l);

		printf("%-8d | %-32s | %-32s | %-5d | %-5.2f\n", el.matricola, el.nome, el.cognome, el.cfu, el.media);
		l = tail(l);

		cont++;
	}

	if (cont == 0) {

		printf("\nEmpty list!\n");
	}
	else {

		printf("---------------------------------------------------------------------------------------------------------\n\n");
	}
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

		printf("\nError opening file \"%s\"\n", fileName);
		return NULL;
	}

	do {

		temp = leggi_un_esame(fp);

		if (strcmp(temp.corso, "EOF") && strcmp(temp.corso, "NA")) {

			(*dim)++;
		}

	} while (strcmp(temp.corso, "EOF"));

	if ((esami = (Esame*)malloc(sizeof(Esame) * (*dim))) == NULL) {

		printf("\nAllocation Error!\n");
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

		l1->next = mergeList(l1->next, l2);
		return l1;
	}
	else {

		l2->next = mergeList(l1, l2->next);
		return l2;
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

void mergeArrayEsame(Esame v[], int i1, int i2, int fine, Esame vuoto[]) {

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

void mergeSortArrayEsame(Esame v[], int first, int last, Esame vuoto[]) {

	int mid;

	if (first < last) {

		mid = (last + first) / 2;
		mergeSortArrayEsame(v, first, mid, vuoto);
		mergeSortArrayEsame(v, mid + 1, last, vuoto);
		mergeArrayEsame(v, first, mid + 1, last, vuoto);
	}
}

void ordina_esami(Esame* esami, int dim) {

	Esame* vuoto;

	if ((vuoto = (Esame*)malloc(sizeof(Esame) * dim)) == NULL) {

		printf("Allocation Error!\n");
		return;
	}

	mergeSortArrayEsame(esami, 0, dim - 1, vuoto);
	free(vuoto);
}

// ============ Statistiche per ogni corso ============

StatCorso* statistiche_corsi(Esame* esami, int dim, int* dimStat) {

	StatCorso* s, *temp;
	int i, j, k = 0, somma;
	Bool stop;

	(*dimStat) = 0;

	if ((temp = (StatCorso*)malloc(sizeof(StatCorso) * (dim))) == NULL) {

		printf("Allocation Error!\n");
		return NULL;
	}

	for (i = 0; i < dim; i++) {

		stop = false;
		temp[k].iscritti = 1;
		somma = esami[i].voto;

		for (j = i + 1; j < dim && !stop; j++) {

			if (!strcmp(esami[i].corso, esami[j].corso)) {

				somma = somma + esami[j].voto;
				(temp[k].iscritti)++;
			}
			else {

				stop = true;
			}
		}

		strcpy_s(temp[k].corso, MAX_CHAR_CORSO, esami[i].corso);
		temp[k].media = ((float)somma) / (temp[k].iscritti);
		k++;

		if (!stop) {

			i = j - 1;
		}
		else {

			i = j - 2;
		}
	}

	(*dimStat) = k;

	if ((s = (StatCorso*)malloc(sizeof(StatCorso) * (*dimStat))) == NULL) {

		printf("Allocation Error!\n");
		free(temp);
		return NULL;
	}

	for (i = 0; i < k; i++) {

		s[i] = temp[i];
	}

	free(temp);
	return s;
}

void printArrayStatCorsi(StatCorso v[], int dimLogica) {

	int i;

	printf("\n------------------------------------------------------------------------------------------\n");
	printf("%-50s | %-15s | %-8s\n", "Course", "Average Mark", "Registered");
	printf("------------------------------------------------------------------------------------------\n");

	for (i = 0; i < dimLogica; i++) {

		printf("%-50s | %-15.2f | %-8d\n", v[i].corso, v[i].media, v[i].iscritti);
	}

	printf("------------------------------------------------------------------------------------------\n\n");
}

// ============ Ordinamento array di statistiche corsi ============

int compare_corso(StatCorso s1, StatCorso s2) {

	int result;

	if (s1.media > s2.media) {

		result = -1;
	}
	else {

		if (s1.media < s2.media) {

			result = 1;
		}
		else {

			result = 0;
		}
	}
	
	if (result == 0) {

		result = s2.iscritti - s1.iscritti;
	}

	return result;
}

void mergeArrayStats(StatCorso v[], int i1, int i2, int fine, StatCorso vuoto[]) {

	int i = i1, j = i2, k = i1;

	while (i <= i2 - 1 && j <= fine) {

		if (compare_corso(v[i], v[j]) < 0) {

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

void mergeSortArrayStats(StatCorso v[], int first, int last, StatCorso vuoto[]) {

	int mid;

	if (first < last) {

		mid = (last + first) / 2;
		mergeSortArrayStats(v, first, mid, vuoto);
		mergeSortArrayStats(v, mid + 1, last, vuoto);
		mergeArrayStats(v, first, mid + 1, last, vuoto);
	}
}

void ordina_statistiche(StatCorso* stats, int dim) {

	StatCorso* vuoto;

	if ((vuoto = (StatCorso*)malloc(sizeof(StatCorso) * dim)) == NULL) {

		printf("Allocation Error!\n");
		return;
	}

	mergeSortArrayStats(stats, 0, dim - 1, vuoto);
	free(vuoto);
}

//============ Scrittura in file binario di studenti ============

void write_bin_studenti(list studenti, char* username) {

	FILE* fp;
	element e;
	char bin_fileName[MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1];

	strcpy_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, username);
	strcat_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, "_");
	strcat_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, "students.bin");

	if (fopen_s(&fp, bin_fileName, "wb") != 0) {

		printf("\nError opening file \"%s\"\n", bin_fileName);
		return;
	}

	while (!empty(studenti)) {

		e = head(studenti);
		fwrite(&e, sizeof(Studente), 1, fp);
		studenti = tail(studenti);
	}

	printf("\nData saved on binary file \"%s\" succefully!", bin_fileName);
	fclose(fp);
}

//============ Scrittura in file binario di statistiche dei corsi ============

void write_bin_corsi(StatCorso* stats, int dim, char* username) {

	FILE* fp;
	int i;
	char bin_fileName[MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1];

	strcpy_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, username);
	strcat_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, "_");
	strcat_s(bin_fileName, MAX_CHAR_FILE_NAME + MAX_CHAR_USERNAME - 1, "courses.bin");

	if (fopen_s(&fp, bin_fileName, "wb") != 0) {

		printf("\nError opening file \"%s\"\n",  bin_fileName);
		return;
	}

	for (i = 0; i < dim; i++) {

		fwrite(&(stats[i]), sizeof(StatCorso), 1, fp);
	}

	printf("\nData saved on binary file \"%s\" succefully!\n\n", bin_fileName);
	fclose(fp);
}