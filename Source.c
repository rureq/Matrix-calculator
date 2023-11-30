#include "stdio.h"
#include "stdlib.h"
#include "macierze.h"
#include <windows.h>
#define dlugosc_nazwy_pliku 100
// Program pozwalajacy na wczytywanie macierzy z pliku, wykonywanie na nich prostych operacji (dodawanie, odejmowanie, mnozenie), oraz zapis wyniku do pliku


typedef struct _mtx{	// deklaracja struktury macierzy
int col,row,max;		// zmienne struktury: wymiary macierzy i liczba cyfr najdluzszego elementu
double **macierz;		// macierz
} mtx;

FILE *f,*g;				// deklaracja plików - input/output
mtx wynik;				
int wynik_exist = 0;

void wypelnij_macierz(double **macierz, int col, int row) { 
	// funkcja wypelniajaca macierz zgodnie z danymi w pliku
	int i, j;
	for (i = 0; i < col; ++i) {
		for (j = 0; j < row; ++j) {
			fscanf(f, "%lf", &macierz[i][j]);
		}
	}
}

void clear_input() {
	//zapobiega blednemu odczytaniu danych przez scanf 
	//http://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
	fseek(stdin, 0, SEEK_END);
}

void wczytaj_plik(int *znacznik_menu) {
	//wczytuje plik o rozszerzeniu .txt okreslony przez uzytkownika
	char nazwa_pliku[dlugosc_nazwy_pliku];
	int menu;
	printf("Podaj nazwe pliku bez rozszerzenia (.txt):\n");
	scanf("%s", &nazwa_pliku);
	strcat(nazwa_pliku, ".txt");

	f = fopen(nazwa_pliku, "r");
	if (f == NULL) {
		printf("\nWystapil blad podczas wczytywania pliku: %s.\nSprawdz czy plik istnieje w folderze zawierajacym program\n", nazwa_pliku);
		do {
			printf("\n1. Sprobuj ponownie.\n2. Opusc program.\n");
			scanf("%d", &menu);
			clear_input();
		} while (menu < 1 || menu > 2);

		switch (menu)
		{
		case 1:
			wczytaj_plik(znacznik_menu);
			return;
			break;
		case 2:
			*znacznik_menu = 0;
			return;
			break;
		}
	}
	else {
		printf("\nPlik %s wczytano pomyslnie.\n", nazwa_pliku);
		*znacznik_menu = 1;
		Sleep(750);
		system("cls");
		return;
	}
}

void wyswietl_macierz(mtx macierze[]) {
	// wyswietla macierz
	int n;
	printf("Podaj numer macierzy, ktora chcesz wydrukowac:\n");
	scanf("%d", &n);
	drukuj_macierz(macierze[n-1].macierz, macierze[n-1].col, macierze[n-1].row, macierze[n-1].max);
	return;
}

void operacje(mtx macierze[], int liczba_macierzy) {
	// operacje na macierzach - dodawanie, odejmowanie, mnozenie
	int menu = 0;
	int a, b, i, j;
	printf("\nWybierz operacje, ktora chcesz wykonac:\n1.Dodawanie macierzy\n2.Odejmowanie macierzy\n3.Mnozenie macierzy\n4.Wyjscie do menu\n" );
	do {
		scanf("%d", &menu);
		clear_input();
	} while (menu < 1 || menu > 4);
	if (menu == 4) {
		return;
	}
	printf("Podaj numery macierzy, na ktorych chcesz przeprowadzic operacje\n(nie wszystkie operacje na macierzach sa przemienne, dlatego prosze podac je w odpowiedniej kolejnosci)\n)");
	do {
		scanf("%d%d", &a, &b);
		clear_input();
	} while (a < 1 || a > liczba_macierzy || b < 1 || b > liczba_macierzy);
	
	switch (menu) {
		case 1: {
			if (macierze[a-1].col == macierze[b-1].col  && macierze[a-1].row == macierze[b-1].row) {
				if (wynik_exist == 1) {
					free(wynik.macierz);
				}				
				wynik.macierz = nowa_macierz(macierze[a-1].col, macierze[a - 1].row);
				wynik_exist = 1;
				wynik.col = macierze[a - 1].col;
				wynik.row = macierze[a - 1].row;
				for (i = 0; i < macierze[a - 1].col; ++i) {
					for (j = 0; j < macierze[a - 1].row;++j) {
						wynik.macierz[i][j] = macierze[a - 1].macierz[i][j] + macierze[b - 1].macierz[i][j];
					}
				}
				wynik.max = zwroc_max(wynik.macierz, wynik.col, wynik.row);

				drukuj_macierz(wynik.macierz, wynik.col, wynik.row, wynik.max);
				return;
			}

			else {
				printf("Macierze nie sa kwadratowe lub nie maja takich samych wymiarow, nie mozna przeprowadzic operacji");
				Sleep(2000);
				return;				
			}
			break;
		}
		case 2: {
			if (macierze[a - 1].col == macierze[b - 1].col  && macierze[a - 1].row == macierze[b - 1].row) {
				if (wynik_exist == 1) {
					free(wynik.macierz);
				}
				wynik.macierz = nowa_macierz(macierze[a - 1].col, macierze[a - 1].row);
				wynik_exist = 1;
				wynik.col = macierze[a - 1].col;
				wynik.row = macierze[a - 1].row;
				for (i = 0; i < macierze[a - 1].col; ++i) {
					for (j = 0; j < macierze[a - 1].row; ++j) {
						wynik.macierz[i][j] = macierze[a - 1].macierz[i][j] - macierze[b - 1].macierz[i][j];
					}
				}
			wynik.max = zwroc_max(wynik.macierz, wynik.col, wynik.row);

			drukuj_macierz(wynik.macierz, wynik.col, wynik.row, wynik.max);
			return;
		}

				else {
					printf("Macierze nie sa kwadratowe lub nie maja takich samych wymiarow, nie mozna przeprowadzic operacji");
					Sleep(2000);
					return;

				}

			break;
		}
		case 3: {
			if (macierze[a - 1].row == macierze[b - 1].col) {
				if (wynik_exist == 1) {
					free(wynik.macierz);
				}
				double temp = 0;
				int k;
				wynik.macierz = nowa_macierz(macierze[a - 1].row, macierze[b - 1].col);
				wynik_exist = 1;
				wynik.col = macierze[a - 1].col;
				wynik.row = macierze[b - 1].row;
				for (i = 0; i < wynik.col; ++i) {
					for (j = 0; j < wynik.row; ++j) {
						for (k = 0; k < macierze[a - 1].col; ++k) {
							temp += macierze[a - 1].macierz[i][k] * macierze[b - 1].macierz[k][j];
						}
						wynik.macierz[i][j] = temp;
						temp = 0;
					}
				}
				wynik.max = zwroc_max(wynik.macierz, wynik.col, wynik.row);

				drukuj_macierz(wynik.macierz, wynik.col, wynik.row, wynik.max);
				return;
			}

			else {
				printf("Macierze nie maja odpowiednich wymiarow, nie mozna przeprowadzic operacji");
				Sleep(1500);
				return;

			}

			break;
		}
		case 4: {
			return;
			break;
		}
	}
}

void zapis() {
	// zapis wyniku do pliku
	int i, j;
	if (wynik_exist == 1) {
		g = fopen("wynik.txt", "a");
		if (g != NULL) {
			fprintf(g, "\n\n %d %d\n\n", wynik.col, wynik.row);
			for (i = 0; i < wynik.col; ++i) {
				for (j = 0; j < wynik.row; ++j) {
					fprintf(g, " %*lg", wynik.max, wynik.macierz[i][j]);
				}
				fprintf(g, "\n");
			}
			fprintf(g, "\n");
			free(wynik.macierz);
			wynik_exist = 0;
			fclose(g);
			printf("Zapis sie powiodl.\n");
		}
		else {
			printf("Nie udalo sie otworzyc pliku do zapisu\n");
		}
	}
	else {
		printf("Brak pliku do zapisania, upewnij sie czy wykonano jakas operacje\n");
		return;
	}

}

void menu(mtx macierze[], int *znacznik_menu, int liczba_macierzy) {
	// menu glowne
	int wybor_menu;
	printf("\n1. Wyswietl macierz z pliku.\n");
	printf("2. Wykonaj operacje na macierzach z pliku.\n");
	printf("3. Zapisz wynik do pliku.\n");
	printf("4. Opusc program.\n");

	do {
		printf("Prosze wybrac liczbe z zakresu 1-4.\n");
		scanf("%d", &wybor_menu);
		clear_input();
	} while (wybor_menu < 1 || wybor_menu > 4);
	system("cls");
	printf("Wybrano pozycje nr. %d\n", wybor_menu);
	switch (wybor_menu) {
	case 1:
		wyswietl_macierz(macierze);
		*znacznik_menu = 1;
		break;
		
	case 2:
		operacje(macierze, liczba_macierzy);
		*znacznik_menu = 1;
		break;
	case 3:
		zapis();
		*znacznik_menu = 1;
		break;
	case 4:
		break;
	}
}

int main(void) {					// tu zaczyna sie main
	int i, col, row, liczba_macierzy, znacznik_menu;
	znacznik_menu = 0;

	wczytaj_plik(&znacznik_menu);	// tu wzywamy funkcje zalaczajaca plik do programu

	if (f == NULL) {				// tu, jesli pliku nie udalo sie odczytac, a uzytkownik chce wyjsc z programu, zapewniamy ze kod nie bedzie wykonywal operacji na plikach
		return 0;
	}
	
	fscanf(f, "%d", &liczba_macierzy); // jesli sie udalo zalaczyc plik, sprawdzamy ile macierzy jest w pliku
	
	mtx* macierze;						// zaczynamy wrzucac macierze do pamieci
	macierze = (mtx*)malloc(liczba_macierzy*sizeof(mtx));
	for (i = 0; i < liczba_macierzy; ++i) {
		fscanf(f, "%d%d", &col, &row);
		macierze[i].macierz = nowa_macierz(col, row);
		macierze[i].col = col;
		macierze[i].row = row;
		wypelnij_macierz(macierze[i].macierz, macierze[i].col, macierze[i].row);
		macierze[i].max = zwroc_max(macierze[i].macierz, macierze[i].col, macierze[i].row);
		//drukuj_macierz(macierze[i].macierz, macierze[i].col, macierze[i].row, macierze[i].max);
	}
	
	printf("Witaj w kalkulatorze macierzy, wybierz funkcje z menu (numer):\n");
	while (znacznik_menu == 1) { // tu sie zaczyna menu, dopoki funckje z menu zwracaja znacznik_menu = 1 menu bedzie sie pokazywalo
		znacznik_menu = 0;
		menu(macierze, &znacznik_menu, liczba_macierzy);

	}
	
	for (i = 0; i < liczba_macierzy; ++i) { // zwolnienie pamieci dla poszczegolnych macierzy 
		zwolnij_pamiec(macierze[i].macierz, macierze[i].col, macierze[i].row);
	}

	free(macierze); // i dla tablicy przechowujacej macierze

	if (wynik_exist == 1) {		//zwolnienie pamieci wyniku, tylko jesli zostala ona na niego zaalokowana
		free(wynik.macierz);
	}

	if (f != NULL) {
		fclose(f);		// zamykamy plik
	}
	
	if (g != NULL) {
		fclose(f);		// zamykamy plik
	}

	return 0; // do widzenia!
}




