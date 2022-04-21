#pragma once
#include <string>
#include <vector>
#include <array>
#include "planete.h"
#include "route.h"
#include "arete.h"

constexpr short INIT = 100;
class Graphe
{
private:
	Arete matrice[INIT][INIT];									// Matrice d�adjacence.
	short nbElements;											// Nombre d��lements 
	float limite;												// La capacit� en carburant du vaisseau utilisant ce graphe. Symbolisant donc sa limite pour atteindre les plan�tes.
	vector<Planete>* planetes;									// Pointeur vers le vector des plan�tes.

	array<bool, INIT> visites;									// Array des (index des) plan�tes visit�es.
	void aideDFS(const string, const string, Route&, short&);	// Fonction R�cursif du parcours DFS.
public:
	Graphe(vector<Planete>*, const float);						// Constructeur de Graphe.
	~Graphe();													// Destructeur de Graphe.
	short getPlaneteidx(const string) const;					// Getter de l�index d�une Plan�te.
	void ajouterArete(const short, const short);				// Ajouter une ar�te � la matrice.
	void retirerArete(const short, const short);				// Retirer une ar�te � la matrice.
	string toStringMatrice(bool, bool) const;					// Repr�sentation textuelle de la Matrice.
	void nettoyerVisite();										// R�initialiser la liste des visites.
	Route DFS(const string, const string);						// Parcours DFS du Graphe.
};