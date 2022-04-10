#include "vaisseau.h"
#include <iostream>
using namespace std;

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter du Mod�le du Vaisseau.
* @return	string du mod�le du vaisseau.
*/
string Vaisseau::getModele() const { return this->modele; }

/**
* Getter de la capacit� en carburant du Vaisseau.
* @return	la capcit� en carburant.
*/
float Vaisseau::getCapacite() const { return this->capacite; }

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
* Surcharge de l�op�rateur ==.
* @param	_vaisseau : le second vaisseau avec lequel comparer.
* @return	true si les mod�les sont les m�mes, false sinon.
*/
bool Vaisseau::operator==(Vaisseau _vaisseau) {
	return this->modele == _vaisseau.modele;
}