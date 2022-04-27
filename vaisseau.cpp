#include "vaisseau.h"
using namespace std;

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur par d�faut.
* @param	_modele : le nom du vaisseau.
* @param	_capacite : la capacit� en carburant du vaisseau.
*/
Vaisseau::Vaisseau(string _modele, float _capacite, vector<Planete>* _planetes = nullptr): modele(_modele), capacite(_capacite), systeme(_planetes,this->capacite) {}

/**
* Destructeur par d�faut
*/
Vaisseau::~Vaisseau(){}

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter du Mod�le du Vaisseau.
* @return	string du mod�le du vaisseau.
*/
string Vaisseau::getModele() const { return this->modele; }

/**
* Getter de la capacit� en carburant du Vaisseau.
* @return	la capacit� en carburant.
*/
float Vaisseau::getCapacite() const { return this->capacite; }

/**
* Getter du syst�me que le Vaisseau peut emprunter.
* @return	un graphe des plan�tes.
*/
Graphe& Vaisseau::getSysteme() { return this->systeme; }

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
* Obtenir une repr�sentation textuelle du Vaisseau.
* @return	un string du mod�le et capacit� du Vaisseau.
*/
string Vaisseau::toString() const {
	return modele + " " + to_string(capacite);
}

/**
* Surcharge de l�op�rateur ==.
* @param	_vaisseau : le second vaisseau avec lequel comparer.
* @return	true si les mod�les sont les m�mes, false sinon.
*/
bool Vaisseau::operator==(Vaisseau _vaisseau) {
	return this->modele == _vaisseau.modele;
}