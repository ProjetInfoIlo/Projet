#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Matrice.cpp"
using namespace std;

int getRandom(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

int main() {
	srand(time(NULL));

	int taille = 3;

	Matrice m(taille, taille - 1);
	
	for (int ligne = 0; ligne < taille; ++ligne)
		for (int colonne = 0; colonne < taille - 1; ++colonne)
			m.setValue(ligne, colonne, getRandom(-10, 10));

	Matrice p(taille - 1, taille);

	for (int ligne = 0; ligne < taille - 1; ++ligne)
		for (int colonne = 0; colonne < taille; ++colonne)
			p.setValue(ligne, colonne, getRandom(-10, 10));

	cout << m  << endl << p << endl;

	cout << m * p << endl;

	system("PAUSE");

	return 0;
}