#pragma once
#include "stdio.h"
#include "stdlib.h"
// W tym pliku zostalo zebrane kilka funkcji, aby glowny kod byl bardziej przejrzysty

int digits_count(double f) {
	//sprawdza ilosc cyfr przed przecinkiem zadanej liczby
	int n = (int)f;
	int licznik = 0;

	while (n != 0) {
		n /= 10;
		licznik += 1;
	}
	return licznik;
}

int zwroc_max(double** macierz, int col, int row) {
	// funkcja zwracajaca liczbe cyfr najdluzszego elementu macierzy
	int max, i, j;
	max = 0;

	for (i = 0; i < col; ++i) {
		for (j = 0; j<row; ++j) {
			if (digits_count(macierz[i][j])>max) {
				max = digits_count(macierz[i][j]);
			}
		}
	}
	return max;
}

double** nowa_macierz(int col, int row) {
	// tworzy nowa pusta macierz i zwraca do niej wskaznik
	double ** macierz;
	int i;
	macierz = (double**)malloc(col*sizeof(double*));
	for (i = 0; i < col; ++i) {
		macierz[i] = (double*)malloc(row*sizeof(double));
	}

	return macierz;
}

void drukuj_macierz(double **macierz, int col, int row, int max) {
	// drukuje zadana macierz
	int i, j;
	printf("\n");
	for (i = 0; i < col; ++i) {
		for (j = 0; j < row; ++j) {
			printf(" %*.1lf", max + 2, macierz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void zwolnij_pamiec(double** macierz, int col, int row) {
	// zwalnia pamiec dla zadanej macierzy
	int i;
	for (i = 0; i < col; ++i) {
		free(macierz[i]);
	}
	free(macierz);
}