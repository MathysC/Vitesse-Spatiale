#include "planete.h"
#include <iostream>
using namespace std;


// Constructeur par d�faut.

Planete::Planete(){}

bool Planete::operator==(Planete _planete) {
	return this->nomPlanete == _planete.nomPlanete;
}