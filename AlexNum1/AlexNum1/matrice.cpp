#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class matrice {
private : 
	double **tableau;
	int colonne, ligne;

public :

	int getL() {
		return ligne;
	}
	int getC() {
		return colonne;
	}
	void setLC(int L,int C) {
		colonne = C;
		ligne = L;
	}
	void setValue(int L,int C, double value) {
		tableau[L][C] = value;
	}
	double getValue(int L, int C) {
		return tableau[L][C];
	}



	// matrice A de même taille que matrice créée
	matrice(const matrice &A) {
		ligne = A.getL();
		colonne = A.getC();
		tableau = new double * [ligne];
		for (int i = 0; i < ligne; ++i) {
			tableau[i] = new double [colonne];
			for (int j = 0; j < colonne; ++j) 
				tableau[i][j] = A.getValue(i,j);

		}
	}
	matrice (int i, int j, bool initToZero = false) {
		ligne = i;
		colonne = j;			
		tableau = new double * [ligne];
		for (int i = 0; i < ligne; ++i) {
			tableau[i] = new double[colonne];
			if (initToZero == true)
				for (j = 0; j < colonne; ++j)
					tableau[i][j] = 0;

		}
	}
	~matrice() {
		for (int i = 0; i < ligne; ++i)delete[] tableau[i];
		delete [] tableau;
	}
		//Si la première matrice est de dimension ixj la matrice B doit être de dimension jxp avec p quelconques
	matrice operator *(const matrice &B) const {
		if (colonne != B.ligne)
			throw new string ("Multiplication Impossible");
			matrice C (ligne, B.colonne, true);
			for (int i = 0; i < ligne; ++i) {
				for (int j = 0; j < B.colonne;++j) {
					for (int k = 0; k < B.ligne; ++k) {
						C.tableau[i][j] = C.tableau[i][j] + tableau[i][k] * B.tableau[k][j];
						}
					}
				
				}
			return C;
 
		
		}
	//Matrice B de la même taille que celle de l'addition (Donc C aussi)
	matrice operator +(const matrice &B) {
		matrice C(ligne, colonne, false);
		for(int i=0;i<ligne;++i)
			for (int j = 0; j < colonne; ++j) {
				C.tableau[i][j] = tableau[i][j] + B.tableau[i][j];
			}
		return C;

	}
	matrice operator -(const matrice &B) {
		matrice C(ligne, colonne, false);
		for (int i = 0; i<ligne; ++i)
			for (int j = 0; j < colonne; ++j) {
				C.tableau[i][j] = tableau[i][j] - B.tableau[i][j];
			}
		return C;
	}
	friend ostream &operator <<(ostream &flux,const matrice &A) {
		for (int i = 0; i < A.ligne; ++i) {
			flux << '(';
			for (int j = 0; j < A.colonne; ++j) {
				flux << ' ' << A.tableau[i][j];
			}
			flux << " )"<<endl;
		}
		return flux;
	}
	matrice &operator =(const matrice &A) {
		ligne = A.ligne;
		colonne = A.colonne;
		for (int i = 0; i < ligne; ++i)
			for (int j = 0; j< colonne; ++j) {
				tableau[i][j] = A.tableau[i][j];
			}
		return *this;
	}
	bool operator ==(const matrice &B) {
		
		if ((colonne != B.colonne) || (ligne != B.ligne))
			return false;
		for (int i = 0; i < ligne; ++i)
			for (int j = 0; j < colonne; j++)
				if (tableau[i][j] != B.tableau[i][j])
					return false;
		return true;
	}

};

int getRandom(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

int main() {
	srand(time(NULL));

	int taille = 3;

	matrice m(3, 3);

	for (int ligne = 0; ligne < taille; ++ligne)
		for (int colonne = 0; colonne < taille; ++colonne)
			m.tableau[ligne][colonne] = getRandom(-10, 10);

	matrice a(3, 3);

	for (int ligne = 0; ligne < taille; ++ligne)
		for (int colonne = 0; colonne < taille; ++colonne)
			a.tableau[ligne][colonne] = getRandom(-10, 10);
	cout << a<<endl<<m<<endl;
	cout << a*m;
	system("PAUSE");

	return 0;

}



