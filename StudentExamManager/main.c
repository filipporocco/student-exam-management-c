#include "universita.h"

int main() {

	list studenti = emptyList(), studenti_aggiornati = emptyList();
	Esame* esami = NULL;
	StatCorso* stats = NULL;
	int dim_e = 0, dim_s = 0, n;
	char file_studenti[MAX_CHAR_FILE_NAME] = "studenti.txt", file_esami[MAX_CHAR_FILE_NAME] = "esami.txt";

	/*welcome(file_studenti, file_esami); */

	// ============ Lettura di studenti e di esami da file .txt ============
	studenti = leggi_studenti(file_studenti);
	esami = leggi_esami(file_esami, &dim_e);

	if (studenti == emptyList() || esami == NULL) {

		if (studenti != emptyList()) {

			freelist(studenti);
		}
		if(esami != NULL) {

			free(esami);
		}
		exit(1);
	}
	else {

		// ============ Aggiornamento media e CFU degli studenti ============
		studenti_aggiornati = aggiorna_studenti(studenti, esami, dim_e);

		// ============ Ordinamento lista di studenti ============
		studenti_aggiornati = mergeSortList(studenti_aggiornati);

		// ============ Ordinamento array di esami ============
		ordina_esami(esami, dim_e);

		// ============ Statistiche per ogni corso ============
		stats = statistiche_corsi(esami, dim_e, &dim_s);

		// ============ Ordinamento array di statistiche corsi ============
		ordina_statistiche(stats, dim_s);

		do {
			printf("Enter 1, 2, 3 or 4:\n\n(1) Print students\n(2) Print courses statistics\n(3) Save students and statistics on binary files\n(4) Exit\n\n");
			scanf_s("%d%*c", &n);

			if (n > 4) {

				printf("\nError! Please try again!\n\n");
			}
			else {

				if (n == 1) {
					showListStudenti(studenti_aggiornati);
				}
				if (n == 2) {

					printArrayStatCorsi(stats, dim_s);
				}
				if (n == 3) {

					//============ Scrittura in file binario di studenti ============
					write_bin_studenti(studenti_aggiornati);

					//============ Scrittura in file binario di statistiche dei corsi ============
					write_bin_corsi(stats, dim_s);

				}
			}

		} while (n != 4);

		//Liberazione memoria
		free(esami);
		free(stats);
		freelist(studenti);
		freelist(studenti_aggiornati);
	}

	return 0;
}