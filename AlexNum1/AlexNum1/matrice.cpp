#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class matrice {
private : 
	double **tableau;
	int colonne, ligne;

public :

	int getL() const {
		return ligne;
	}
	int getC() const {
		return colonne;
	}
	void setLC(int L,int C) {
		colonne = C;
		ligne = L;
	}
	void setValue(int L,int C, double value) {
		tableau[L][C] = value;
	}
	double getValue(int L, int C) const {
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
		for (int i = 0; i < ligne; ++i)
			delete[] tableau[i];
		delete [] tableau;
	}
		//Si la première matrice est de dimension ixj la matrice B doit être de dimension jxp avec p quelconques
	matrice operator *(const matrice &B) const {
		if (getC() != B.getL())
			throw new string ("Multiplication Impossible");
			matrice C (getL(), B.getC(), true);
			for (int i = 0; i < getL(); ++i) {
				for (int j = 0; j < B.getC();++j) {
					for (int k = 0; k < B.getL(); ++k) {
						C.setValue(i, j, C.getValue(i, j) + getValue(i, k)*B.getValue(k, j));
						}
					}
				
				}
			return C;
 
		
		}
	//Matrice B de la même taille que celle de l'addition (Donc C aussi)
	matrice operator +(const matrice &B) {
		matrice C(getL(), getC(), false);
		for(int i=0;i<getL();++i)
			for (int j = 0; j < getC(); ++j) {
				C.setValue(i,j,getValue(i,j)+B.getValue(i,j));
			}
		return C;

	}
	matrice operator -(const matrice &B) {
		matrice C(getL(), getC(), false);
		for (int i = 0; i<getL(); ++i)
			for (int j = 0; j < getC(); ++j) {
				C.setValue(i, j, getValue(i, j) - B.getValue(i, j));
			}
		return C;
	}
	friend ostream &operator <<(ostream &flux,const matrice &A) {
		for (int i = 0; i < A.getL(); ++i) {
			flux << '(';
			for (int j = 0; j < A.getC(); ++j) {
				flux << ' ' << A.getValue(i,j);
			}
			flux << " )"<<endl;
		}
		return flux;
	}
	matrice &operator =(const matrice &A) {
		ligne = A.getL();
		colonne = A.getC();
		for (int i = 0; i < getL(); ++i)
			for (int j = 0; j< getC(); ++j) {
				setValue(i, j, A.getValue(i, j));
			}
		return *this;
	}
	bool operator ==(const matrice &B) {
		
		if ((getC() != B.getC()) || (getL() != B.getL()))
			return false;
		for (int i = 0; i < getL(); ++i)
			for (int j = 0; j < getC(); j++)
				if (getValue(i,j) != B.getValue(i,j))
					return false;
		return true;
	}
	// La matrice doit être carrée
	double det() const {
		if (getC() != getL())
			throw new string("Regarde la taille de ta matrice !!!");
		double determinant = 0;
		if (getL() == 1)
			return getValue(0, 0);
		if (getL() != 2)
			for (int i = 0; i < getL(); ++i) {
				matrice C(getL() - 1, getC() - 1);
				int compteur = 0;
				for (int j = 0; j < getL(); ++j) {
					
					if (j == i) {
								continue;
								}
					else {
						for (int k = 1; k < getC(); ++k) {
							C.setValue(compteur, k - 1, getValue(j, k));
							++compteur;
						}
					}
					}
				cout << C;
				determinant += (i % 2 * -2 + 1)*getValue(i, 0)*C.det();
			}
		else {
			determinant = getValue(0, 0)*getValue(1, 1) - getValue(0, 1)*getValue(1, 0);
		}
		return determinant;
	}
};

int getRandom(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

int main() {
	srand(time(NULL));

	int taille = 3;

	matrice m(taille, taille,true);

	m.setValue(0, 0, 3);
	m.setValue(1, 1, 3);
	m.setValue(2, 2, 1);



	cout << m << "det :";
	cout<< m.det();
	system("PAUSE");

	return 0;

}



