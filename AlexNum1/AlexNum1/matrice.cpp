#include <iostream>
using namespace std;

class matrice {
public: 
	double **tableau;
	int colonne, ligne;

	// matrice A de même taille que matrice créée
	matrice(matrice &A) {
		ligne = A.ligne;
		colonne = A.colonne;
			for (int i = 0; i < ligne; ++i)
				for (int j = 0; i < colonne; ++j) {
					tableau[i][j] = A.tableau[i][j];
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
	matrice &operator =(matrice &A) {
		ligne = A.ligne;
		colonne = A.colonne;
		for (int i = 0; i < ligne; ++i)
			for (int j = 0; i < colonne; ++j) {
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

int main() {
	matrice A(2,2);
	matrice B(2,2);
	A.tableau[0][0] = 1;
	A.tableau[1][1] = 2;
	A.tableau[0][1] = 2;
	A.tableau[1][0] = 3;
	B.tableau[0][0] = 1;
	B.tableau[1][1] = 1;
	B.tableau[0][1] = 0;
	B.tableau[1][0] = 0;
	matrice C(2, 2);
	C = A*B;
	cout << C;

	return 0;
}


