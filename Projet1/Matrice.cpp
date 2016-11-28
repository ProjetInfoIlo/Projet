#include <iostream>
using namespace std;

class Matrice {

	private:
		int lignes, colonnes;
		double **matrice;

	public:
		Matrice(int lignes, int colonnes, bool initToZero = false) {
			this->lignes = lignes;
			this->colonnes = colonnes;

			matrice = new double*[lignes];
			for (int i = 0; i < lignes; ++i) {
				matrice[i] = new double[colonnes];
				if (initToZero) for (int j = 0; j < colonnes; ++j) matrice[i][j] = 0;
			}
		}

		Matrice(const Matrice& m) {
			this->lignes = m.lignes;
			this->colonnes = m.colonnes;

			matrice = new double*[lignes];
			for (int i = 0; i < lignes; ++i) {
				matrice[i] = new double[colonnes];
				for (int j = 0; j < colonnes; ++j) matrice[i][j] = m.getValue(i, j);
			}
		}

		~Matrice() {
			for (int i = 0; i < lignes; ++i) delete[] matrice[i];
			delete[] matrice;
		}

		void setValue(int ligne, int colonne, double value) {
			matrice[ligne][colonne] = value;
		}

		double getValue(int ligne, int colonne) const {
			return matrice[ligne][colonne];
		}

		friend ostream& operator << (ostream& stream, const Matrice& m) {
			for (int ligne = 0; ligne < m.lignes; ++ligne) {
				for (int colonne = 0; colonne < m.colonnes - 1; ++colonne) stream << m.getValue(ligne, colonne) << " ";
				stream << m.getValue(ligne, m.colonnes - 1) << endl;
			}

			return stream;
		}

		Matrice operator * (double x) const {
			return x * *this;
		}

		//le probleme de:
		//Matrice operator * (double x)
		//est qu'il ne marche que si le double est à droite dans l'opération
		//donc 5 * A (par exemple) ne marche pas
		//donc on ajoute la fonction suivante en complément
		friend Matrice operator * (double x, const Matrice& m) {
			Matrice result(m);

			for (int ligne = 0; ligne < m.lignes; ++ligne)
				for (int colonne = 0; colonne < m.colonnes; ++colonne)
					result.setValue(ligne, colonne, m.getValue(ligne, colonne) * x);

			return result;
		}

		Matrice operator * (const Matrice& m) const {
			if (lignes != m.colonnes) throw new string("Multiplication impossible");

			Matrice result(m.lignes, m.colonnes, true);

			for (int ligne = 0; ligne < m.lignes; ++ligne)
				for (int colonne = 0; colonne < m.colonnes; ++colonne)
					for (int i = 0; i < lignes; ++i)
						result.setValue(ligne, colonne, result.getValue(ligne, colonne) + getValue(ligne, i) * m.getValue(i, colonne));

			return result;
		}

		Matrice operator + (const Matrice& m) const {
			if (lignes != m.lignes || colonnes != m.colonnes) throw new string("Addition impossible");

			Matrice result(lignes, colonnes);

			for (int ligne = 0; ligne < m.lignes; ++ligne)
				for (int colonne = 0; colonne < m.colonnes; ++colonne)
					result.setValue(ligne, colonne, m.getValue(ligne, colonne) + getValue(ligne, colonne));

			return result;
		}

		Matrice operator - (const Matrice& m) const {
			if (lignes != m.lignes || colonnes != m.colonnes) throw new string("Addition impossible");

			Matrice result(lignes, colonnes);

			for (int ligne = 0; ligne < m.lignes; ++ligne)
				for (int colonne = 0; colonne < m.colonnes; ++colonne)
					result.setValue(ligne, colonne, m.getValue(ligne, colonne) - getValue(ligne, colonne));

			return result;
		}

		double determinant() {
			if (lignes != colonnes) throw new string("Calcul determinant impossible");

			//pas besoin de vérifier colonnes == 2...
			if (lignes == 2) return getValue(0, 0) * getValue(1, 1) - getValue(0, 1) * getValue(1, 0);
			else {
				double somme = 0;
				for (int i = 0; i < colonnes; ++i) {
					Matrice sousMatrice(lignes - 1, colonnes - 1);

					for (int colonne = 1; colonne < colonnes; ++colonne) {
						int subLigne = 0;

						for (int ligne = 0; ligne < lignes; ++ligne) {
							if (ligne == i) continue;

							sousMatrice.setValue(subLigne, colonne - 1, getValue(ligne, colonne));
							++subLigne;//on pourrait test (ligne > i) mais plus lourd niveau calcul
						}
					}

					somme += (i % 2 * -2 + 1) * getValue(i, 0) * sousMatrice.determinant();
					//on développe par rapport à la première ligne, donc on a juste (-1)^i
					//ce qui revient a faire (i % 2 * -2 + 1), moche mais mieux que Math.pow...
					//sans oublié que on commence a i = 0
				}

				return somme;
			}
		}
};