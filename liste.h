#pragma once
#include "noeud.h"
#include <string>
using namespace std;

template <class T>
class liste
{
	noeud<T>* tete;				// Pointeur de la t�te de la liste.
	noeud<T>* queue;			// Pointeur de la queue de la liste.
	noeud<T>* courant;			// Pointeur de l'�l�ment courant de la liste.

	liste();					// Constructeur de la liste.
	~liste();					// Destructeur de la liste.
	bool trouver(const T&);		// Trouver un �l�ment dans la liste.
	void supprimer(T&);			// Supprimer un �l�ment dans la liste.
	void insererFin(T&);		// Ins�rer un �l�ment � la liste.
	void fixerTete();			// Fixer le noeud courant � la t�te de la liste.
	bool estDansListe();		// V�rifier que le noeud courant est dans la liste.
	noeud<T>* suivant();		// "Incr�menter" le noeud courant.
	string toString();			// Obtenir une repr�sentation textuelle des �l�ments de la liste.
};

