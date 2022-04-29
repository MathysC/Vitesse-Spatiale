#include <algorithm>
#include "graphe.h"
using namespace std;

////// CONSTRUCTEURS DESTRUCTEURS /////////////////////////////////////////////////////////////////

/**
* Constructeur de Graphe.
* @param	_planetes : le vecteur des plan�tes.
* @param	_limite :	la limite repr�sente la capacit� en carburant du vaisseau utilisant ce graphe.
*/
Graphe::Graphe(vector<Planete>* _planetes, float const _limite) {
	hydraterMatrice(_planetes, _limite);
}

/**
* Destructeur de Graphe.
*/
Graphe::~Graphe() {}

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter de l'index d'une Plan�te
* @param	_nomPlanete : le nom de la Planete � trouver.
* @return	l�index d�une Planete correspondante au nom, sinon -1.
*/
short Graphe::getPlaneteidx(const string _nomPlanete) const {
	short i = 0;
	for (auto ite = planetes->cbegin(); ite != planetes->cend(); ++ite) {
		if (ite->getNomPlanete() == _nomPlanete) {
			return i;
		}
		i++;
	}
	return -1;
}

/**
* Getter du pointeur du vector de planetes.
* @return	le pointeur de planetes.
*/
vector<Planete>* Graphe::getPlanetesptr() {
	return this->planetes;
}

/**
* Getter de l'indice du poids minimal.
* M�thode utilis�e pour le parcours Dijkstra.
* @param	_poids : la liste des poids
* @return	l'indice du poids minimal.
*/
short Graphe::getMinDistanceIdx(vector<float>& _poids) {
	float minimum = OUT_OF_BOUND;
	short idxMin = -1;
	for (short _idx = 0; _idx < nbElements; _idx++) {
		if (!visites[_idx] && _poids[_idx] < minimum) {
			minimum = _poids[_idx];
			idxMin = _idx;
		}
	}
	return idxMin;

}

/**
* V�rifie si la liste a �t� compl�tement visit�e ou non.
* @return	true si aucun �l�ment est � false. false sinon.
*/
bool Graphe::estCompletementVisite() const {
	for (short _idx = 0; _idx < nbElements; _idx++) {
		if (!visites[_idx]) {
			return false;
		}
	}
	return true;
}

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
* Mettre � jour la Matrice et les informations du graphe.
* @param	_planetes :	le pointeur du vector de toutes les plan�tes.
* @param	_limite :	la limite du vaisseau.
*/
void Graphe::hydraterMatrice(vector<Planete>* _planetes,float _limite) {
	this->planetes = _planetes;
	this->limite = _limite;
	this->nbElements = 0;
	if (_planetes != nullptr) {
		this->nbElements = (short)_planetes->size();
	}
	this->matrice = vector <vector<Arete>>(nbElements);
	
	// Initialiser la Matrice.
	for (short x = 0; x < nbElements; x++) {
		vector<Arete> Colonne(nbElements, Arete());
		for (short y = 0; y < nbElements; y++) {
			if (x != y) {
				// Initialisation de la structure Arete.
				Colonne[y] = Arete(&planetes->at(x), &planetes->at(y), limite);
				Colonne[y].initialiser(limite);
			}
		}
		matrice[x] = Colonne;
	}
}

/**
* Ajouter/ Mettre � jour l�Arete � l�emplacement _x._y.
* Si le vaisseau permet d�emprunter cette Arete.
* @param	_x : la coordonn�e x dans la matrice.
* @param	_y : la coordonn�e y dans la matrice.
*/
void Graphe::ajouterArete(const short _x, const short _y) {
	if (_x != _y) {
		this->matrice[_x][_y].initialiser(limite);
		this->matrice[_y][_x].initialiser(limite);
	}
}

/**
* Retirer l�Arete � l�emplacement _x._y.
* @param	_x : la coordonn�e x dans la matrice.
* @param	_y : la coordonn�e y dans la matrice.
*/
void Graphe::retirerArete(const short _x, const short _y) {
	if (_x != _y) {
		this->matrice[_x][_y].rendreInaccessible();
		this->matrice[_y][_x].rendreInaccessible();
	}
}

/**
* Retirer une ar�te � la matrice via deux nations.
* @param	_nationA : la premi�re nation.
* @param	_nationB : la seconde nation.
*/
void Graphe::retirerArete(const string _nationA, const string _nationB) {
	vector<short> planetesDeA,planetesDeB;
	string nationTmp ="";
	for (short _idx = 0; _idx < nbElements; _idx++) {
		nationTmp = planetes->at(_idx).getNation();
		if (nationTmp == _nationA) {
			planetesDeA.push_back(_idx);
		}
		else if (nationTmp == _nationB) {
			planetesDeB.push_back(_idx);
		}
	}

	for (short x : planetesDeA) {
		for (short y : planetesDeB) {
			retirerArete(x, y);
		}
	}
}

/**
* Obtenir la repr�sentation textuelle de la Matrice.
* @param	_printCout : afficher le cout de voyage sur l�Arete.
* @param	_printDistance : afficher la poidsCourant de parcours l�Arete.
* @return	les informations de chaque Ar�te.
*/
string Graphe::toStringMatrice(bool _printCout, bool _printDistance) const {
	string res;
	for (short x = 0; x < nbElements; x++) {
		res += "| ";
		for (short y = 0; y < nbElements; y++) {
			if (_printCout) {
				// G�rer cout
				float cout = matrice[x][y].getCout();
				if (cout == 0.0f) {
					res += '0';
				}
				else if (cout == OUT_OF_BOUND) {
					res += "inf";
				}
				else {
					res += to_string((int)cout);
				}
			}

			if (_printCout && _printDistance) { res += ", "; }

			if (_printDistance) {
				// G�rer poidsCourant
				float dist = matrice[x][y].getDistance();
				if (dist == 0.0f) {
					res += '0';
				}
				else if (dist == OUT_OF_BOUND) {
					res += "inf";
				}
				else {
					res += to_string((int)dist);
				}
			}
			res += " | ";
		}
		res += '\n';
	}
	return res;
}

//// PARCOURS ////

/**
* R�initialise la liste des visites � false.
*/
void Graphe::nettoyerVisite() {
	this->visites = vector<bool>(nbElements, false);
}

/**
* Parcours DFS pour obtenir une route entre deux Planetes.
* @param	_src : le nom de la Planete source, le point de d�part.
* @param	_dst : le nom de la Planete destination, l'arriv�e.
* @return	la Route compl�te � emprunter.
*/
Route Graphe::DFS(const string _src, const string _dst) {
	Route res;
	// Si les deux plan�tes demand�es existent, on peut effectuer le parcours DFS.
	if (getPlaneteidx(_src) != -1 && getPlaneteidx(_dst) != -1) {
		this->nettoyerVisite();
		short _etape = 0;
		this->aideDFS(_src, _dst, res, _etape);
	}

	// Si le chemin ne parvient pas � la destination voulue.
	if (res.arrivee() == nullptr || res.arrivee()->getNomPlanete() != _dst) {
		return Route();
	}
	return res;
}

/**
* Fonction r�cursive de parcours DFS du Graphe.
* @param	_src :	la plan�te source du d�placement.
* @param	_dst :	la plan�te destination � atteindre.
* @param	_route:	la route couramment planifi�e.
* @param	_etape:	l��tape couramment modifi�e.
*/
void Graphe::aideDFS(const string _src, const string _dst, Route& _route, short& _etape) {
	// Nous parcourons le graphe si et seulement si la destination n�est pas atteinte.
	//  Si il n�y a pas d�arriv�e 
	//   (seulement au lancement)		// Si les noms ne correspondent pas
	if (_route.arrivee() == nullptr || _route.arrivee()->getNomPlanete() != _dst) {

		// Obtenir l�index de la source et de la destination.
		short _idxsrc = this->getPlaneteidx(_src);
		short _idxdst = this->getPlaneteidx(_dst);

		// Marquer visit�e cette plan�te source.
		this->visites[_idxsrc] = true;

		// On parcourt les autres plan�tes depuis la plan�te source.
		for (short _y = 0; _y < nbElements; _y++) {
			
			// On v�rifie que l�autre plan�te est accessible et n�a pas �t� visit�.
			if (matrice[_idxsrc][_y].getDistance() <= limite && !visites[_y]) {
			
				if (_route.arrivee() == nullptr || _route.arrivee()->getNomPlanete() != _dst) {
					_route.modifierEtape(_etape, matrice[_idxsrc][_y]);
					// On passe � la prochaine �tape.
					_etape++;
					aideDFS(matrice[_idxsrc][_y].dst->getNomPlanete(), _dst, _route, _etape);
					_etape--;
				}
			

			}

		}
		// On repasse sur cette �tape.
		//_etape--;

	}
}

/**
* Parcours Dijkstra pour obtenir la route la plus courte entre deux plan�tes.
* @param	_src : le nom de la Planete source, le point de d�part.
* @param	_dst : le nom de la Planete destination, l'arriv�e.
* @return	la Route compl�te � emprunter.
*/
Route Graphe::dijkstra(const string _src, const string _dst,const string _choix) {
	Route res;

	short idxSource = getPlaneteidx(_src);
	short idxDesti = getPlaneteidx(_dst);

	// Si les deux plan�tes demand�es n�existent pas. Inutile de chercher un chemin.
	// Si le choix n'est pas correcte, inutile d'effectuer une recherche.
	if (idxSource == -1 || idxDesti == -1 || (_choix != "cout" && _choix != "distance")) {
		return Route();
 	}

	//Reinitialisation de la liste des plan�tes visit�es.
	// Les plan�tes visit�es correspondront aux plan�tes fix�es.
	this->nettoyerVisite();

	// Initialisation de la liste des poids des plan�tes
	vector<float> poids(nbElements, OUT_OF_BOUND);
	// Initialisation de la liste des provenances
	vector<short> provientDe(nbElements, -1);

	short idxCourant = idxSource;
	poids[idxCourant] = 0;
	provientDe[idxCourant] = idxSource;
	float poidsCourant = OUT_OF_BOUND;
	/*
		* Exemple:
				  0	 10     20
		  ______________________
						10
		0|		      C ---- A
		 |	14.14	/ |      |
		 |		   /  |      |
	   10|		  E   | 20   | 20
		 |		   \  |      |
		 |	14.14	\ |   10 |
	   20|			  B ---- D


	* Exemple � la fin de l��x�cution de la boucle while
					A	B	C	D	E
	 poids      :	0	30	10	20	24.14
	 provientDe :	A	E	A	A	C

	 Le chemin le plus court entre A et B est donc => A > C > E > B (6)

	 (Dans ce programme, les index A-E sont des indices (shorts) repr�sentant l�emplacement des plan�tes dans le vector planetes)
	*/

	// Remplir les vector poids et provientDe des valeurs de parcours du graphe par Dijkstra
	// Utilisation de any_of OU de estCompletementVisite().
	while (any_of(begin(visites), end(visites), [](bool b) {return b==false; })) {
		idxCourant = getMinDistanceIdx(poids);
		// Si idxCourant est �gale � -1 c'est que nous ne pouvons pas aller plus loin, nous arr�tons le parcours l�.
		if (idxCourant == -1) {
			break;
		}
		visites[idxCourant] = true;
		for (short _idx = 0; _idx < nbElements; _idx++) {
			if (!visites[_idx] && poids[idxCourant] != OUT_OF_BOUND) {
				if (_choix == "distance") {
					poidsCourant = matrice[idxCourant][_idx].getDistance();
				}
				else if (_choix == "cout") {
					poidsCourant = matrice[idxCourant][_idx].getCout();
				}
				if (poids[idxCourant] + poidsCourant < poids[_idx]) {
					// Mettre � jour le poids pour attendre cet indice
					poids[_idx] = poids[idxCourant] + poidsCourant;
					// Indiquer l�indice ayant permis d�attendre celui
					provientDe[_idx] = idxCourant;
				}
			}
		}

	}
	
	// Si aucun sommet ne m�ne � la destination, on n'a pas de Route.
	if (provientDe[idxDesti] == -1) {
		return Route();
	}
	// On passe idxCourant � -1 afin de le r�utiliser sans qu�il pose de soucis
	idxCourant = -1;
	/*
		Avec cette boucle, nous allons lire la liste des �tapes du chemin pour aller
		de la source � la destination dans le sens inverse.
	*/
	while (idxCourant != idxSource) {
		idxCourant = provientDe[idxDesti];
		// On ajoute � chaque fois � l�avant de la liste
		res.modifierEtape(-1, matrice[idxCourant][idxDesti]);
		idxDesti = idxCourant;
	}
	
	// Si le chemin ne parvient pas � la destination voulue.
	if (res.arrivee() == nullptr || res.arrivee()->getNomPlanete() != _dst) {
		return Route();
	}
	return res;
}