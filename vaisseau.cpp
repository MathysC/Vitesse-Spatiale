#include "vaisseau.h"
using namespace std;

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur par d�faut.
*/
Vaisseau::Vaisseau(vector<Planete>* _planetes = nullptr):modele(""),capacite(0), systeme(_planetes,this->capacite) {}

/**
* Constructeur de Vaisseau.
* @param	_modele :	le nom du vaisseau.
* @param	_capacite : la capacit� en carburant du vaisseau.
*/
Vaisseau::Vaisseau(string _modele, float _capacite, vector<Planete>* _planetes = nullptr): modele(_modele), capacite(_capacite), systeme(_planetes,this->capacite) {}

/**
* Destructeur par d�faut.
*/
Vaisseau::~Vaisseau(){}

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter du Mod�le du Vaisseau.
* @return	le mod�le du vaisseau.
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
	return modele + " " + to_string((short)capacite);
}

/*
* Surcharge de l�op�rateur <<. Retour du toString de Vaisseau.
* @param _out :			le stream de output.
* @param _vaisseau :	le Vaisseau � repr�senter.
* @return				le stream � jour.
*/
ostream& operator<<(ostream& _out, Vaisseau& _vaisseau)
{
	_out << _vaisseau.toString();
	return _out;
}

/*
* Surcharge de l�op�rateur >>. R�cup�ration des informations formant un Vaisseau.
* @param _in :			le stream d�input.
* @param _vaisseau :	le Vaisseau � modifier.
* @return				Le stream � jour.
*/
istream& operator>>(istream& _fin, Vaisseau& _vaisseau)
{
	// On r�cup�re les informations
	_fin >> _vaisseau.modele >> _vaisseau.capacite;

	// On met � jour le systeme de ce vaisseau.
	_vaisseau.getSysteme().hydraterMatrice(_vaisseau.getSysteme().getPlanetesptr(),_vaisseau.getCapacite());
	return _fin;
}