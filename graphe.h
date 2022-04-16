#pragma once
#include <string>
#include <vector>
#include "planete.h"

constexpr short INIT = 100;
constexpr auto OUT_OF_BOUND = numeric_limits<float>::max();

/**
* Une ar�te contient un cout et une distance � parcourir pour aller de la source � la destination.
*/
struct Arete {
	Planete* src;		// La source de l�ar�te, la plan�te de d�part.
	Planete* dst;		// La destination de l�ar�te, la plan�te d�arriv�e.
	float distance;		// Distance entre deux planetes.
	float cout;			// Cout de d�placement entre deux planetes.

	Arete() {
		this->src = this->dst = nullptr;
		rendreInaccessible();
		
	}
	/**
	* Constructeur de Arete.
	* @param	_src : La planete source.
	* @param	_dst : La planete destination.
	* @param	_limite : la capacit� en carburant du vaisseau, soit sa limite de d�placement.
	*/
	Arete(Planete* _src, Planete* _dst, const float _limite) {
		this->src = _src;
		this->dst = _dst;
		initialiser(_limite);
	}
	/**
	* Initialiser les donn�es de la structure.
	* @param	_limite : la capacit� en carburant du vaisseau, soit sa limite de d�placement.
	*/
	void initialiser(float const _limite) {
		// Si la distance est inf�rieur � la limite, c�est que le chemin est prenable par utilisable par le vaisseau.
		if (calculerDistance() < _limite) {
			rendreAccessible();
		}
		else {
			rendreInaccessible();
		}
	}
	
	/**
	* Calculer la distance s�parant la Planete source de la destination.
	* @return	la distance en float.
	*/
	float calculerDistance() const {
		return (float)sqrt(pow(dst->getX() - src->getX(),2) + pow(dst->getY() - src->getY(),2));
	};
	
	/**
	* Obtenir le cout de d�placement entre la Planete source et la Planete destination.
	* @return	le cout en float.
	*/
	float calculerCout() const {
		return src->getPrixCarburant() * calculerDistance();
	};
	
	/**
	* Rendre accessible le noeud. 
	* Il faut donc mettre � jour les informations.
	*/
	void rendreAccessible() {
		cout = calculerCout();
		distance = calculerDistance();
	}
	
	/**
	* Rendre inaccessible le noeud.
	*/ 
	void rendreInaccessible() {
		cout = distance = OUT_OF_BOUND;
};
	};

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
	void ajouterArete(const short, const short);	// Ajouter une ar�te � la matrice.
	void retirerArete(const short, const short);	// Retirer une ar�te � la matrice.
	string toStringMatrice() const;					// Repr�sentation textuelle de la Matrice.
};
