#pragma once
#include <string>
#include <vector>
#include <array>
#include "planete.h"
#include "route.h"
#include "arete.h"

class Graphe
{
private:
	vector<vector<Arete>> matrice;								// Matrice d�adjacence.
	short nbElements;											// Nombre d��lements 
	float limite;												// La capacit� en carburant du vaisseau utilisant ce graphe. Symbolisant donc sa limite pour atteindre les plan�tes.
	vector<Planete>* planetes;									// Pointeur vers le vector des plan�tes.
	vector<bool> visites;										// Array des (index des) plan�tes visit�es.
	void aideDFS(const string, const string, Route&, short&);	// Fonction R�cursif du parcours DFS.
	short getMinDistanceIdx(vector<float>&);					// Obtenir l'indice du poids minimal dans la liste des poids.
	bool EstcompletementVisite() const;							// V�rifier que la liste a �t� compl�tement visit�.
public:
	Graphe(vector<Planete>*, const float);						// Constructeur de Graphe.
	~Graphe();													// Destructeur de Graphe.
	short getPlaneteidx(const string) const;					// Getter de l�index d�une Plan�te.
	void ajouterArete(const short, const short);				// Ajouter une ar�te � la matrice.
	void retirerArete(const short, const short);				// Retirer une ar�te � la matrice.
	void retirerArete(const string, const string);				// Retirer une ar�te � la matrice via deux nations.
	string toStringMatrice(bool, bool) const;					// Repr�sentation textuelle de la Matrice.
	void nettoyerVisite();										// R�initialiser la liste des visites.
	Route DFS(const string, const string);						// Parcours DFS du Graphe.
	Route dijkstra(const string, const string);					// Parcours Dijkstra du Graphe.
};