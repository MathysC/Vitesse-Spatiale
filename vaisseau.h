#pragma once
#include <string>
#include <vector>
#include "graphe.h"
#include "planete.h"
using namespace std;

class Vaisseau
{
private:
	string modele;										// Mod�le du Vaisseau.
	float capacite;										// Capacit� en carburant du Vaisseau.
	Graphe systeme;										// Syst�me empruntable par le Vaisseau.
public:
	Vaisseau(vector<Planete>*);							// Constructeur par d�faut.
	Vaisseau(string, float, vector<Planete>*);			// Constructeur de Vaisseau.
	~Vaisseau();										// Destructeur par d�faut.
	string getModele() const;							// Getter de modele. 
	float getCapacite() const;							// Getter de la capacite en carburant.
	Graphe& getSysteme();								// Getter du Systeme.
	string toString() const;							// Obtenir une repr�sentation textuelle.
	friend ostream& operator<< (ostream&, Vaisseau&);	// Surcharge de l�op�rateur <<.
	friend istream& operator>> (istream&, Vaisseau&);	// Surcharge de l�op�rateur >>.
};
