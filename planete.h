#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
* Impl�mentation des Planetes.
* 
* Une Planete repr�sente un Sommet dans un Graphe.
* Chaque plan�te est identifi�e par un nom unique. 
* Son emplacement est determin� par x et y.
*/
class Planete
{
private:
	string nomPlanete;									// Nom de la Plan�te.
	float x;											// Coordonn�e x de la Plan�te.
	float y;											// Coordonn�e y de la Plan�te.
	int population;										// Le nombre d�individus sur la Plan�te.
	string nation;										// Le nom de la nation dirigeant la Plan�te.
	float prixCarburant;								// le prix du Carburant sur la Plan�te.
public:
	Planete();											// Constructeur par d�faut.
	Planete(string, float, float, int, string, float);	// Constructeur de la Plan�te.
	~Planete();											// Destructeur par d�faut de la Plan�te.
	string getNomPlanete() const;						// Getter du nom de la Plan�te.
	float getX() const;									// Getter de la coordonn�e x de la Plan�te.
	float getY() const;									// Getter de la coordonn�e x de la Plan�te.
	int getPopulation() const;							// Getter de la population de la Plan�te.
	string getNation() const;							// Getter de la nation de la Plan�te.
	float getPrixCarburant() const;						// Getter du prix du Carburant sur la Plan�te.
	string toString() const;							// Repr�sentation textuelle des �l�ments d�crivant la Plan�te.
	friend ostream& operator<< (ostream&, Planete&);	// Surcharge de l�op�rateur <<.
	friend istream& operator>> (istream&, Planete&);	// Surcharge de l�op�rateur >>.
};
