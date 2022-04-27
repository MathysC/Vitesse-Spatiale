#include "planete.h"
using namespace std;

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur par d�faut.
* @param	_nomPlanete : le nom de la Plan�te.
* @param	_x : la coordonn�e x de la Plan�te.
* @param	_y : la coordonn�e y de la Plan�te.
* @param	_population : la population de la Plan�te.
* @param	_nation : la nation de la Plan�te.
* @param	_prixCarburant : le prix du Carburant sur la Plan�te.
*/
Planete::Planete(string _nomPlanete, float _x, float _y, int _population, string _nation, float _prixCarburant ){
	this->nomPlanete = _nomPlanete;
	this->x = _x;
	this->y = _y;
	this->population = _population;
	this->nation = _nation;
	this->prixCarburant = _prixCarburant;
}

/**
* Destructeur par d�faut
*/
Planete::~Planete(){}

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter du nom de la plan�te.
* @return	string du nom de la plan�te.
*/
string Planete::getNomPlanete() const { return this->nomPlanete; }

/**
* Getter de la coordonn�e x.
* @return	la coordonn�e x de la plan�te.
*/
float Planete::getX() const { return this->x; }

/**
* Getter de la coordonn�e y.
* @return	la coordonn�e y de la plan�te.
*/
float Planete::getY() const { return this->y; }

/**
* Getter de la population.
* @return	la population de la plan�te.
*/
int Planete::getPopulation() const { return this->population; }

/**
* Getter de la nation.
* @return	la nation de la plan�te.
*/
string Planete::getNation() const { return this->nation; }

/**
* Getter du prix du carburant.
* @return	le prix du carburant de la plan�te.
*/
float Planete::getPrixCarburant() const { return this->prixCarburant; }

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
* Obtenir une repr�sentation textuelle de la Planete.
* @return	un string avec les �l�ments de la Planete.
*/
string Planete::toString() const {
	return nomPlanete + " " + to_string(x) + " " + to_string(y) + " "
		+ to_string(population) + " " + nation + " " + to_string(prixCarburant);
}

/**
* Surcharge de l�op�rateur ==.
* @param	_planete : la seconde planete avec laquelle comparer.
* @return	true si les noms sont les m�mes, false sinon.
*/
bool Planete::operator==(Planete _planete) {
	return this->nomPlanete == _planete.nomPlanete;
}



