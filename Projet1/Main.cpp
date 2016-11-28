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

	Matrice m(2, 2);
	
	for (int ligne = 0; ligne < 2; ++ligne)
		for (int colonne = 0; colonne < 2; ++colonne)
			m.setValue(ligne, colonne, getRandom(-10, 10));

	cout << m << endl;
	cout << m.comatrice() << endl;

	system("PAUSE");

	return 0;
}