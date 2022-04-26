#pragma once
#include <string>
using namespace std;

class Vaisseau
{
private:
	string modele;					// Mod�le du Vaisseau.
	float capacite;					// Capacit� en carburant du Vaisseau.
public:
	Vaisseau(string, float);		// Constructeur par d�faut.
	~Vaisseau();					// Destructeur par d�faut.
	string getModele() const;		// Getter de modele. 
	float getCapacite() const;		// Getter de la capacite en carburant.
	string toString() const;		// Obtenir une repr�sentation textuelle.
	bool operator == (Vaisseau);	// Surcharge de l'op�rateur == pour les comparaisons.


			/*
				* Surcharge de l�op�rateur <<. Retour du toString de Vaisseau.
				* @param _out :			le stream de output.
				* @param _vaisseau :	la vaisseau � repr�senter.
				* @returns				le stream � jour.
				*/

	friend ostream& operator<< (ostream& _out, Vaisseau& _vaisseau) {

		_out << (_vaisseau.getModele()) + " " + to_string(_vaisseau.getCapacite());
		return _out;
	}
};
