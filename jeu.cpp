#include "jeu.h"
#include <string>
#include <iostream>
#include <fstream>
#include "planete.h"

using namespace std;

//// CONSTRUCTEURS DESTRUCTEURS ///////////////////////////////////////////////////////////////////

/**
 * Constructeur par d�faut.
 */
Jeu::Jeu() {}

/**
 * Destructeur par d�faut
 */
Jeu::~Jeu() {}

//// FONCTIONS ////////////////////////////////////////////////////////////////////////////////////

/**
 * Ouverture et execution d'un fichier de transactions.
 * Les transactions ne peuvent pas s'ex�cuter si le fichier des vaisseaux doit �tre lu avant le fichier des plan�tes.
 * Le programme n�cessite les plan�tes afin d'instancier les vaisseaux.
 *
 * @param	_fichierTransaction : Le nom du fichier de Transaction.
* @return   true si l'ouverture et la lecture se font sans encombre. False sinon.
 */
bool Jeu::ouverture_transactions(string _fichierTransactions) {

    ifstream fin(_fichierTransactions); //Lecture

    if (!fin) {
        cout << "Le path fourni : "<< _fichierTransactions <<", ne m�ne pas � un fichier." << endl;
        return false;
    }
    // Variables utilis�es pour la transaction
    char caractere;
    string nomFichierSystemeStellaire, nomFichierVaisseaux;
    string typeVaisseau, planeteS, planeteD, nationA, nationB;
    bool planetesEnMemoire = false;

    try {
        cout << "Lecture en cours de : " << _fichierTransactions << '\n';
        // Tant qu'on peut lire le premier caract�re de chaque ligne.
        while (fin >> caractere) {
            switch (caractere) {
                // On souhaite lire un autre fichier txt
            case '#': {

                // Il faut savoir quel autre fichier est � lire, un fichier de Planetes, ou un fichier de Vaisseaux.
                fin >> caractere;
                //Charge un syst�me en m�moire
                if (caractere == 'P') {
                    cout << "Charge les diff�rentes plan�tes en m�moire \n" << endl;
                    fin >> nomFichierSystemeStellaire;
                    if (ouverture_planetes(nomFichierSystemeStellaire)) {
                        planetesEnMemoire = true;
                    }
                    else {
                        throw invalid_argument("Les plan�tes n'ont pas �t� charg�.");
                    }
                }

                //Charger les types de vaisseau en m�moire
                if (caractere == 'V') {
                    cout << "Charge les diff�rents vaisseaux en m�moire \n" << endl;
                    fin >> nomFichierVaisseaux;
                    if(planetesEnMemoire) {
                        if (!ouverture_vaisseaux(nomFichierVaisseaux)) {
                            throw invalid_argument("Les vaisseaux n'ont pas �t� charg�.");
                        }
                    }
                    else {
                        throw invalid_argument("Vous ne pouvez pas charger les vaisseaux sans les plan�tes ");
                    }
                }
                break;
            }

                    // On souhaite ex�cuter trouver une route � partir d'une requ�te.
            case '?': {
                // Il faut savoir de quel type de requ�te il s'agit.
                fin >> caractere;

                // Il s'agit de trouver simplement un chemin entre deux plan�tes.
                if (caractere == '1') {

                    fin >> typeVaisseau >> planeteS >> planeteD;
                    cout << "Existe-t-il une route entre les plan�tes " << planeteS << " et " << planeteD << " pour un vaisseau de type " << typeVaisseau << "?" << endl;
                    planifierRoute("DFS", typeVaisseau, planeteS, planeteD);
                    cout << "\n\n";

                }

                // Il s'agit de trouver le plus court chemin entre deux plan�tes.
                if (caractere == '2') {

                    fin >> typeVaisseau >> planeteS >> planeteD;
                    cout << "Existe-t-il une route la plus courte entre les plan�tes " << planeteS << " et " << planeteD << " pour un vaisseau de type " << typeVaisseau << "?" << endl;
                    planifierRoute("Dijkstra-distance", typeVaisseau, planeteS, planeteD);
                    //cout << " NE FONCTIONNE PAS POUR L INSTANT" << endl;
                    cout << "\n\n";
                }

                // Il s'agit de trouver le chemin le moins dispendieux entre deux plan�tes.
                if (caractere == '3') {
                    fin >> typeVaisseau >> planeteS >> planeteD;
                    cout << "Existe-t-il une route la moins dispendieux entre les plan�tes " << planeteS << " et " << planeteD << " pour un vaisseau de type " << typeVaisseau << "?" << endl;
                    planifierRoute("Dijkstra-cout", typeVaisseau, planeteS, planeteD);
                    //cout << " NE FONCTIONNE PAS POUR L INSTANT" << endl;
                    cout << "\n\n";
                }
                break;
            }
                    // On souhaite ajouter un conflit entre deux nations.
            case '/': {

                fin >> nationA >> nationB;
                cout << "Conflit spatiale entre les nations \n" << endl;
                ajouter_conflit(nationA, nationB);
                break;
            }
                    // On souhaite afficher les informations en m�moire.
            case '&': {
                cout << "Affichages des informations en m�moire " << '\n';
                cout << "_________________________________________" << '\n';

                cout << "Plan�tes : " << '\n';
                for (Planete p : planetes) {
                    cout << " - " << p.toString() << "\n";
                }
                cout << "______________________" << '\n';
                cout << "Vaisseaux : " << '\n';

                for (Vaisseau v : vaisseaux) {
                    cout << " - " << v.toString() << "\n";
                }

                cout << "______________________" << '\n';
                cout << "Conflits : " << '\n';
                for (string c : conflits) {
                    cout << " - " << c << "\n";
                }
                cout << "_________________________________________" << '\n' << endl;


                break;
            }
            }
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
        cout << "Une erreur est survenue lors de la lecture du fichier de transaction." << endl;
        return false;
    }

    fin.close();
    return true;
}

/**
* Ouverture d'un fichier de planetes.
* @param    _fichierPlanetes : Le nom du fichier des Planetes.
* @return   true si l'ouverture et la lecture se font sans encombre. False sinon.
*/
bool Jeu::ouverture_planetes(string _fichierPlanetes) {

    ifstream fin(_fichierPlanetes); //Lecture
    if (!fin) {
        cout << "Le path fourni : " << _fichierPlanetes << ", ne m�ne pas � un fichier." << endl;
        return false;
    }
    // Variables composant d'une plan�te
    string nomPlanete;
    float x;
    float y;
    int population;
    string nation;
    float prixCarburant;

    try {
        // Supprimer les plan�tes pr�c�dentes.
        planetes.clear();
        cout << "Lecture en cours de : " << _fichierPlanetes << '\n';
        // Tant que l�on peut recup�rer les informations
        while (fin >> nomPlanete) {
            fin >> x >> y >> population >> nation >> prixCarburant;
            planetes.push_back(Planete(nomPlanete, x, y, population, nation, prixCarburant));
        }
    }
    catch(exception&){
        cout << "Une erreur est survenue lors de la lecture du fichier des planetes." << endl;
        return false;
    }


    // Fermer la lecture du fichier
    fin.close();
    return true;
}

/**
* Ouverture d'un fichier de vaisseaux.
* @param    _fichierVaisseaux : Le nom du fichier des Vaisseaux.
* @return   true si l'ouverture et la lecture se font sans encombre. False sinon.
*/
bool Jeu::ouverture_vaisseaux(string _fichierVaisseaux) {

    ifstream fin(_fichierVaisseaux); //Lecture
    if (!fin) {
        cout << "Le path fourni : " << _fichierVaisseaux << ", ne m�ne pas � un fichier." << endl;
        return false;
    }

    // Variables composant d'une plan�te
    string Modele;
    float Capacite;
    try {
        // Supprimer les vaisseaux pr�c�dents.
        vaisseaux.clear();
        cout << "Lecture en cours de : " << _fichierVaisseaux << '\n';
        // Tant que l�on peut recup�rer les informations
        while (fin >> Modele) {
            fin >> Capacite;
            vaisseaux.push_back(Vaisseau(Modele, Capacite, &planetes));
        }
    }
    catch (exception&) {
        cout << "Une erreur est survenue lors de la lecture du fichier des vaisseaux." << endl;
        return false;
    }
    // Fermer la lecture du fichier
    fin.close();
    return true;
}

/**
* Ajouter un conflit entre deux nations.
* @param    _nationA : La premi�re nation.
* @param    _nationB : La seconde nation.
*/
void Jeu::ajouter_conflit(string _nationA, string _nationB) {

    // Ajouter ce conflit � la liste des conflits.
    string c = _nationA + "/" + _nationB;
    conflits.push_back(c);

    // Mettre � jour les graphes des vaisseaux.
    for (Vaisseau v : vaisseaux) {
        v.getSysteme().retirerArete(_nationA, _nationB);
    }

}

/**
* @param    _parcours   : Le type de parcours emprunt�.
* @param    _modele     : Le mod�le du vaisseau.
* @param	_depart     : La plan�te source du d�placement.
* @param	_arrivee    : La plan�te destination � atteindre.
*/
void Jeu::planifierRoute(const string _parcours, const string _modele, const string _depart, const string _arrivee) {
    Route res;
    Vaisseau* v = nullptr;

    // V�rifier que le mod�le de vaisseau existe 
    for (short _idx = 0; _idx < (short)vaisseaux.size(); _idx++) {
        if (vaisseaux.at(_idx).getModele() == _modele) {
            v = &(vaisseaux.at(_idx));
        }
    }
    if (v == nullptr) {
        cout << " - Ce mod�le n'existe pas." << endl;
        return;
    }

    if (_parcours == "DFS") {
        res = v->getSysteme().DFS(_depart, _arrivee);
    }
    else if (_parcours == "Dijkstra-distance") {
        res = v->getSysteme().dijkstra(_depart, _arrivee, "distance");
    }
    else if (_parcours == "Dijkstra-cout") {
        res = v->getSysteme().dijkstra(_depart, _arrivee, "cout");
    }
    else {
        cout << " - Ce parcours n'existe pas" << endl;
        return;
    }

    if (res.estVide()) {
        cout << " - Aucune route n'existe entre les plan�tes " << _depart << " et " << _arrivee << ", pour le mod�le : " << _modele << endl;
        return;
    }

    cout << " - Il existe une route entre les plan�tes " << _depart << " et " << _arrivee <<  ", pour le mod�le : " << _modele << '\n';
    cout << " - " << res.toString() << endl;
    if (_parcours == "Dijkstra-distance") {
        cout << " - La distance � parcourir est de : " << res.distance() << '\n';
    }
    else if (_parcours == "Dijkstra-cout") {
        cout << " - Le cout total est de           : " << res.cout() << '\n';
    }
}