#pragma once
#include <string>
#include <vector>
#include "planete.h"
#include "route.h"
#include "arete.h"

constexpr short INIT = 100;
class Graphe
{
private:
	Arete matrice[INIT][INIT];						// Matrice d�adjacence.
	short nbElements;								// Nombre d��lements 
	float limite;									// La capacit� en carburant du vaisseau utilisant ce graphe. Symbolisant donc sa limite pour atteindre les plan�tes.
	vector<Planete>* planetes;						// Pointeur vers le vector des plan�tes.
public:
	Graphe(vector<Planete>*, const float);			// Constructeur de Graphe.
	~Graphe();										// Destructeur de Graphe.
	short getPlaneteidx(const string) const;		// Getter de l�index d�une Plan�te.
	void ajouterArete(const short, const short);	// Ajouter une ar�te � la matrice.
	void retirerArete(const short, const short);	// Retirer une ar�te � la matrice.
	string toStringMatrice(bool, bool) const;		// Repr�sentation textuelle de la Matrice.
};