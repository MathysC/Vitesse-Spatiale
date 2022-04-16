#pragma once
#include "graphe.h"
#include "liste.h"
#include "planete.h"
#include "vaisseau.h"
#include <string>
using namespace std;

class jeu
{
private:
	const string PATH = "Fichiers/";

	Graphe<Planete> systeme;		// Graphe repr�sentant les relations entre les plan�tes.
	Liste<string> conflits;			// Liste cha�n�e des conflits entre nations de ce jeu.
	Liste<Vaisseau> vaisseaux;		// Liste des vaisseaux du jeu.

public:
	jeu();
	~jeu();

	void ouverture_transaction(string _fichierTransaction);
};

