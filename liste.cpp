#include "liste.h"

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur de liste.
*/
template <class T>
liste<T>::liste(){
	tete = courant = queue = new noeud<T>();
}

/**
* Destructeur de liste.
*/
template <class T>
liste<T>::~liste(){
	while (tete != NULL) {
		courant = tete;
		tete = tete->_suivant;
		delete courant;
	}
}

//// AUTRES FONCTIONS /////////////////////////////////////////////////////////////////////////////

/**
* Fonction indiquant la pr�sence, ou non, d�un �l�ment dans la liste.
* @param	_element : l��l�ment � trouver.
* @returns	true si l��l�ment existe dans la liste, false sinon.
*/
template <class T>
bool liste<T>::trouver(const T& _element){
	// Parcours de la liste
	for (fixerTete(); estDansListe(); suivant()) {
		T _temp = valeurCourante();
		if (_temp == _element) {
			return true;
		}
	}
	return false; // L��l�ment recherch� ne se trouve pas dans la liste
}

/**
* Supprimer l��l�ment voulu de la liste, s�il est dans la liste.
* @param	_element : l��l�ment � chercher et supprimer.
*/
template <class T>
void liste<T>::supprimer(const T& _element){
	if (trouver(_element)) {
		noeud<T>* _tempCourant = courant->suivant;
		courant->suivant = _tempCourant->suivant;
		if (queue == _tempCourant) {
			queue = courant;
		}
		delete _tempCourant;
	}
}

/**
* Ajouter l��l�ment � la fin de la liste.
* @param	_element : l��l�ment � ajouter � la liste.
*/
template <class T>
void liste<T>::insererFin(const T& _element) {
	queue = queue->suivant = new noeud<T>(_element);
}

/**
* Repositionner le pointeur courant � la t�te de la liste.
*/
template <class T>
void liste<T>::fixerTete() {
	courant = tete;
}

/**
* V�rifier que le pointeur courant se trouve dans la liste.
* @return	true si le pointeur ne se trouve pas en fin de liste, false sinon.
*/
template <class T>
bool liste<T>::estDansListe() {
	return (courant != nullptr) && (courant->suivant != nullptr);
}

/**
* D�placer le pointeur courant sur le noeud suivant.
*/
template <class T>
void liste<T>::suivant() {
	if (courant != nullptr) {
		courant = courant->suivant;
	}
}

/**
* Obtenir l��l�ment courant dans la liste.
* @return	un �lement de type T.
*/
template <class T>
T liste<T>::valeurCourante() const {
	return courant->_suivant->element;
}

/**
* Obtenir une repr�sentation textuelle des �l�ments de la liste.
* @return	un string avec la repr�sentation textuelle de chaque �l�ment de la liste.
*/
template <class T>
string liste<T>::toString() {
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
short int liste<T>::longueur() const {
	short int _nb = 0;
	for (fixerTete(); estDansListe(); suivant()) {
		_nb++;
	}
	return _nb;
}