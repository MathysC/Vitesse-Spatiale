#include "route.h"

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
* Constructeur par d�faut.
*/
Route::Route() {}

/**
* Destructeur par d�faut.
*/
Route::~Route(){}

//// GETTERS SETTERS //////////////////////////////////////////////////////////////////////////////

/**
* Getter du point de d�part.
* @return	La premi�re plan�te de cette route.
*/
Planete* Route::depart() const { 
    if (!this->etapes.empty()) {
        return this->etapes.front().src;
    }
    else {
        return nullptr;
    }
}

/**
* Getter du point d�arriv�e.
* @return	La derni�re plan�te de cette route.
*/
Planete* Route::arrivee() const { 
    if (!this->etapes.empty()) {
        return this->etapes.back().dst;
    }
    else {
        return nullptr;
    }
}

bool Route::estVide() const
{
    return etapes.empty();
}

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
* Calcul du cout de cette route.
* @param	_vaisseau : le vaisseau voulant emprunter la route.
* @return	le cout total du parcours de cette route, ou -1 si le vaisseau ne peut emprunter cette route.
*/
float Route::cout() const {
    float res = 0;
    for (auto it = etapes.cbegin(); it != etapes.cend(); ++it) {
        res += (*it).getCout();
    }
    return res;
}

/**
* Calcul de la distance parcourue avec cette route.
* @param	_vaisseau : le vaisseau voulant emprunter la route.
* @return	la distance totale du parcours de cette route, ou -1 si le vaisseau ne peut emprunter cette route.
*/
float Route::distance() const {
    float res = 0;
    for (auto it = etapes.cbegin(); it != etapes.cend(); ++it) {
        res += (*it).getDistance();
    }
    return res;
}

/**
* Modification d�une �tape � un emplacement.
* @param	_index : l�emplacement auquel placer la plan�te.
* @param	_etape : une �tape � ajouter � cette route.
*/
void Route::modifierEtape(const short _index, const Arete _etape){
	
    // On v�rifie que ce ne soit pas le TOUT premier �l�ment que l�on ajoute
    // Ou que l�on souhaite pas modifier un index n�gatif
    if (this->etapes.size() != 0 && _index > 0) {

        // On v�rifie que l�index que l�on veut modifier est inf�rieur au nombre d��l�ments
        if (_index < (short)this->etapes.size()) {
            this->etapes[_index] = _etape;
        }
        // Sinon on ajoute simplement � la fin
        else {
            this->etapes.push_back(_etape);
        }
    }

    // Sinon on ajoute simplement au d�but
    else {
        this->etapes.push_front(_etape);
    }
}

/**
* Insertion d�une �tape � la fin.
* @param	_etape : une �tape � ajouter � cette route.
*/
void Route::ajouterEtape(const Arete _etape) {
	this->etapes.push_back(_etape);
}

/**
* Repr�sentation textuelle de la route.
* @return   un string avec le nom de toutes les plan�tes visit�es.
*/
string Route::toString() const {
    string res ="";
    if (!etapes.empty()) {
        for (auto it = etapes.cbegin(); it != etapes.cend(); ++it) {
            res += (*it).src->getNomPlanete() + " >> ";
        }

        res += arrivee()->getNomPlanete();
    }
    return res;
}