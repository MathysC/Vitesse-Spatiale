#pragma once
#include <string>
using namespace std;

/**
* Impl�mentation de la liste sous forme de tableau.
* 
* Dans le cadre de ce projet, le nombre d��l�ments tels que les plan�tes, les vaisseaux reste inchang� d�s l�initialisation de la liste.
* Le projet ne n�cessite pas l�ajout ou la suppression d��l�ments.
*/
template <class T>
class Liste
{
private:
	short int courant;			// Index courant.
	short int nbElement;		// Nombre d��l�ment dans la liste.
	short int tailleMax;		// Taille maximale de la liste.
	T* elements;				// Tableau d��l�ments.
public:
	Liste(const short int);		// Constructeur de la liste.
	~Liste();					// Destructeur de la liste.
	bool trouver(const T&);		// Trouver un �l�ment dans la liste.
	void supprimer(const T&);	// Supprimer un �l�ment dans la liste.
	void insererFin(const T&);	// Ins�rer un �l�ment � la liste.
	void fixerTete();			// Fixer le noeud courant � la t�te de la liste.
	bool estDansListe();		// V�rifier que le noeud courant est dans la liste.
	void suivant();				// Incr�menter de 1 le compteur courant.
	T valeurCourante() const;	// Obtenir la valeur courante.
	string toString() const;	// Obtenir une repr�sentation textuelle des �l�ments de la liste.
	short int longueur() const;	// Obtenir le nombre d��l�ment dans la liste.
};

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur de liste.
* @param	_taille : taille maximale du tableau d��l�ments.
*/
template<class T>
Liste<T>::Liste(const short int _taille) {
	this->tailleMax = _taille;
	nbElement = 0;
	courant = 0;
	elements = new T[_taille];
}

/**
* Destructeur de liste.
*/
template<class T>
Liste<T>::~Liste() {
	delete[] elements;
}

//// AUTRES FONCTIONS /////////////////////////////////////////////////////////////////////////////

/**
* Fonction indiquant la pr�sence, ou non, d�un �l�ment dans la liste.
* @param	_element : l��l�ment � trouver.
* @returns	true si l��l�ment existe dans la liste, false sinon.
*/
template<class T>
bool Liste<T>::trouver(const T& _element) {
	for (fixerTete(); estDansListe(); suivant()) {
		if (valeurCourante() == _element) {
			return true;
		}
	}

	return false;
}

/**
* Supprimer l��l�ment voulu de la liste, s�il est dans la liste.
* @param	_element : l��l�ment � chercher et supprimer.
*/
template<class T>
void Liste<T>::supprimer(const T& _element) {
	// Si l��l�ment est dans le tableau
	if (trouver(_element)) {
		// On d�cale tous les �l�ments depuis son emplacement
		for (short int i = courant; i < nbElement - 1; i++) {
			elements[i] = elements[i + 1];
		}
		nbElement--;
	}
}

/**
* Ajouter l��l�ment � la fin de la liste.
* @param	_element : l��l�ment � ajouter � la liste.
*/
template<class T>
void Liste<T>::insererFin(const T& _element) {
	elements[nbElement] = _element;
	nbElement++;
}

/**
* Repositionner le pointeur courant � la t�te de la liste.
*/
template <class T>
void Liste<T>::fixerTete() {
	courant = 0;
}

/**
* V�rifier que le pointeur courant se trouve dans la liste.
* @return	true si le pointeur ne se trouve pas en fin de liste, false sinon.
*/
template <class T>
bool Liste<T>::estDansListe() {
	return (courant >= 0) && (courant < nbElement);
}

/**
* Incr�menter le compteur courant.
*/
template <class T>
void Liste<T>::suivant() {
	courant++;
}

/**
* Obtenir l��l�ment courant dans la liste.
* @return	un �lement de type T.
*/
template <class T>
T Liste<T>::valeurCourante() const {
	return elements[courant];
}

/**
* Obtenir une repr�sentation textuelle des �l�ments de la liste.
* @return	un string avec la repr�sentation textuelle de chaque �l�ment de la liste.
*/
template <class T>
string Liste<T>::toString() const {
	string res;
	for (fixerTete(); estDansListe(); suivant()) {
		T _temp = valeurCourante();
		res += _temp.toString() + '\n';
	}
	return res;
}

/**
* Obtenir le nombre d��l�ment dans la liste.
* @return	un short int du nombre d��l�ment.
*/
template <class T>
short int Liste<T>::longueur() const {
	return nbElement;
}
