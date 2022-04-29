#pragma once
#include <deque>
#include "arete.h"
#include "planete.h"

/**
* Repr�sentation des routes s�parant une plan�te source � une plan�te destination. 
* Une route peut �tre obtenu via le parcours DFS ou dijkstra.
*/
class Route
{
private:
	deque<Arete> etapes;							// file des �tapes.
public:
	Route();										// Constructeur par d�faut.
	~Route();										// Destructeur par d�faut.
	Planete* depart() const;						// Getter du point de d�part.
	Planete* arrivee() const;						// Getter du point d�arriv�e.
	bool estVide() const;							// V�rifier si cette route poss�de des �tapes ou non.
	float cout() const;								// Calcul du cout de cette route.
	float distance() const;							// Calcul de la distance parcourue avec cette route.
	void modifierEtape(const short, const Arete);	// Modification d�une �tape � un emplacement.
	void ajouterEtape(const Arete);					// Insertion d�une �tape � la fin.
	string toString() const;						// Repr�sentation textuelle de la route.
};