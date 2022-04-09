#pragma once
#include "liste.h"
using namespace std;

template<class T>
class Graphe
{
private:
	bool** matriceAdj;										// Matrice d�adjacence des �l�ments.
	short int nbElements;									// Nombre d��l�ments utilis� dans la matrice.
	
	bool** initMatrice();									// Initialisation d�une matrice vide.
public:
	Liste<T>* elements;										// Liste cha�n�e des elements.

	Graphe(Liste<T>*);										// Constructeur de Graphe.
	~Graphe();												// Destructeur de Graphe.
	void ajouterArete(const short int, const short int);	// Ajouter une ar�te � la matrice.
	void retirerArete(const short int, const short int);	// Retirer une ar�te � la matrice.
	bool estArete(const short int, const short int);		// V�rifier s�il y a une ar�te.
	string toStringMatrice() const;							// Obtenir une repr�sentation textuelle de la matrice d�adjacence.
	/*
	* Dans le cadre de ce projet, il n�est pas question d�insertion ou suppression d��l�ments depuis le graphe,
	* La restructuration du graphe n�est donc pas n�cessaire
	*/
	//void ajouterElement(T&);
	//void retirerElement(T&);
	//void hydrateMatrice(bool**);

};

#include "graphe.h"

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur de graphe.
* @param	_liste : la liste cha�n�e d'�l�ments que poss�de la matrice d'adjacence.
*/
template<class T>
Graphe<T>::Graphe(Liste<T>* _liste) {
	elements = _liste;
	matriceAdj = initMatrice();
}

/**
* Destructeur de graphe.
*/
template<class T>
Graphe<T>::~Graphe() {
	for (short int x = 0; x < nbElements; x++) {
		// Supprimer les colonnes de la matrice d'adjacence
		delete[] matriceAdj[x];
	}
	// Supprimer la matrice
	delete[] matriceAdj;
}

/**
* Initialisation de la matrice d�adjacence.
*/
template<class T>
bool** Graphe<T>::initMatrice() {
	bool** _matrice;
	nbElements = elements->longueur();
	// Initialiser la matrice
	_matrice = new bool* [nbElements];

	// Initialiser l'axe x
	for (short int x = 0; x < nbElements; x++) {
		_matrice[x] = new bool[nbElements];

		// Initialiser l'axe y
		for (short int y = 0; y < nbElements; y++) {
			_matrice[x][y] = false;
		}
	}

	return _matrice;
}

//// AUTRES FONCTIONS /////////////////////////////////////////////////////////////////////////////

/**
* Ajouter une ar�te � la matrice.
* Donc la passer � true.
* @param	_x : Coordonn�e x dans la matrice.
* @param	_y : Coordonn�e y dans la matrice.
*/
template<class T>
void Graphe<T>::ajouterArete(const short int _x,const  short int _y) {
	// La condition permet de garder la diagonale de la matrice vide
	if(_x != _y){
		matriceAdj[_x][_y] = true;
		matriceAdj[_y][_x] = true;
	}
}

/**
* Retirer une ar�te � la matrice.
* Donc la passer � false.
* @param	_x : Coordonn�e x dans la matrice.
* @param	_y : Coordonn�e y dans la matrice.
*/
template<class T>
void Graphe<T>::retirerArete(const short int _x,const short int _y) {
	matriceAdj[_x][_y] = false;
	matriceAdj[_y][_x] = false;
}

/**
* Obtenir une repr�sentation visuelle de la matrice d�adjacence.
* @return	un string repr�sentant un tableau avec les �tats.
*/
template<class T>
string Graphe<T>::toStringMatrice() const {
	string res;
	for (short int x = 0; x < nbElements; x++) {
		res += "| " ;
		for (short int y = 0; y < nbElements; y++) {
			res += to_string(matriceAdj[x][y]) + " | ";
		}
		res += '\n';
		
	}
	return res;
}

/**
* Savoir s�il y a une ar�te entre deux noeuds du graphe.
* @return	true s�il y a un lien, false sinon.
*/
template<class T>
bool Graphe<T>::estArete(const short int _x, const short int _y) {
	return matriceAdj[_x][_y];
}

///**
//* Ajouter un �l�ment � la liste des �l�ments.
//* @param	_ele : un element de type T.
//*/
//template<class T>
//void Graphe<T>::ajouterElement(T& _ele) {
//	elements.insererFin(_ele);
//}
//
///**
//* Supprimer un �l�ment � la liste des �l�ments.
//* @param	_ele : un element de type T.
//*/
//template<class T>
//void Graphe<T>::retirerElement(T& _ele) {
//	elements.supprimer(_ele);
//}
//
//template<class T>
//void Graphe<T>::hydrateMatrice(bool** _matrice) {
//
//}
