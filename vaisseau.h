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
};
