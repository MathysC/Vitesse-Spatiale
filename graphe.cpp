#include "graphe.h"

/**
* Constructeur de graphe.
* @parem	_nb		le nombre d'�l�ments que poss�de la matrice d'adjacence.		
*/
template<class T>
graphe<T>::graphe(const short int _nb) {
	nbElements = _nb;
}

template<class T>
void graphe<T>::initMatrice(const short int _nb) {
	// Initialiser la matrice
	matriceAdj = new bool* [nbElements];

	// Initialiser l'axe x
	for (short int x = 0; x < nbElements; x++) {
		matriceAdj[x] = new bool[nbElements];

		// Initialiser l'axe y
		for (short int y = 0; y < nbElements; y++) {
			matriceAdj[x][y] = false;
		}
	}
}

// Destructeur de graphe.
template<class T>
graphe<T>::~graphe() {
	for (short int x = 0; x < nbElements; x++) {
		// Supprimer les colonnes de la matrice d'adjacence
		delete[] matriceAdj[x];
	}
	// Supprimer la matrice
	delete[] matriceAdj;
}

/**
* Ajouter une ar�te � la matrice.
* Donc la passer � true.
* @param	_x	Coordonn�e x dans la matrice.
* @param	_y	Coordonn�e y dans la matrice.
*/
template<class T>
void graphe<T>::ajouterArete(short int _x, short int _y) {
	matriceAdj[_x][_y] = true;
	matriceAdj[_y][_x] = true;
}

/**
* Retirer une ar�te � la matrice.
* Donc la passer � false.
* @param	_x	Coordonn�e x dans la matrice.
* @param	_y	Coordonn�e y dans la matrice.
*/
template<class T>
void graphe<T>::retirerArete(short int _x, short int _y) {
	matriceAdj[_x][_y] = false;
	matriceAdj[_y][_x] = false;
}

/**
* Ajouter un �l�ment � la liste des �l�ments.
* @param	_ele	un element de type T.
*/
template<class T>
void graphe<T>::ajouterElement(T& _ele) {
	elements.ajouterfin(_ele);
}

/**
* Supprimer un �l�ment � la liste des �l�ments.
* @param	_ele	un element de type T.
*/
template<class T>
void graphe<T>::retirerElement(T& _ele) {
	elements.supprimer(_ele);
}
