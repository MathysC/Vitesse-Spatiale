#pragma once
#include "planete.h"
constexpr auto OUT_OF_BOUND = numeric_limits<float>::max();

/**
* Classe repr�sentant les ar�tes, les liens entre les diff�rentes plan�tes.
* Chaque ar�te est compos�e des distances et cout afin d�aller de la plan�te source � la plan�te destination.
*/
class Arete
{
private:
	float distance;							// Distance entre deux planetes.
	float cout;								// Cout de d�placement entre deux planetes.
public:
	Planete* src;							// La source de l�ar�te, la plan�te de d�part.
	Planete* dst;							// La destination de l�ar�te, la plan�te d�arriv�e.
	Arete();								// Constructeur par d�faut.
	Arete(Planete*, Planete*, const float);	// Constructeur de Ar�te.
	~Arete();								// Destructeur par d�faut.
	float getDistance() const;				// Getter de Distance.
	float getCout() const;					// Getter de Cout.
	void initialiser(float const);			// Initialisation de l�Arete.
	float calculerDistance() const;			// Calcul de la distance entre src et dst.
	float calculerCout() const;				// Calcul du cout entre src et dst.
	void rendreAccessible();				// Rendre l�Arete accessible.
	void rendreInaccessible();				// Rendre l�Arete inaccessible.
};
