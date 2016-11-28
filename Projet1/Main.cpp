#include <iostream>
#include <stdlib.h>
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

	Matrice m(3, 3);
	
	for (int ligne = 0; ligne < taille; ++ligne)
		for (int colonne = 0; colonne < taille; ++colonne)
			m.setValue(ligne, colonne, getRandom(-10, 10));

	cout << m * m.inverse() << endl;

	system("PAUSE");

	return 0;
}