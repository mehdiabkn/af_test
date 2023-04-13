// TestAF.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "O_D.h"
#include "FlightNbr.h"

#include <stdio.h>
#include <iostream>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;


int big_file(vector<O_D> o_d, string filename) {
    unsigned int vecSize = o_d.size();
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier" << std::endl;
        return 1;
    }
    file << "Origine;Destination;Min tarif;Max tarif;Tarif moyen" << std::endl;
    int status = 0;
    for (unsigned int i = 0; i < vecSize; i++)
    {
        o_d[i].write_into_file(filename);
    }

    return 1;
}
void affiche_vecteur_o_d(vector<O_D> o_d) {
    unsigned int vecSize = o_d.size();

    std::cout << "on affiche : " << endl;
    for (unsigned int i = 0; i < vecSize; i++)
    {
        o_d[i].toString();
    }
}
vector<O_D> lire_fichier(string fichier) {
    ifstream file(fichier);
    vector<O_D> o_d = { };

    if (!file.is_open()) {
        cerr << "Impossible d'ouvrir le fichier" << endl;
        O_D err = O_D(NULL, NULL, {});
        o_d.push_back(err);
        return o_d;
    }

    
    char* o = new char[4];
    char* o_previous = new char[4]; // Nous permettra de vérifier si on est passé à un nouveau o&d
    char* d = new char[4];
    char* d_previous= new char[4]; // Nous permettra de vérifier si on est passé à un nouveau o&d
    
    set<long> tarifs;


    o_previous[0] = 'x';
    o_previous[1] = 'y';
    o_previous[2] = 'z';
    o_previous[3] = '\0';
    d_previous[0] = 'x';
    d_previous[1] = 'y';
    d_previous[2] = 'z';
    d_previous[3] = '\0'; 
    // Lire chaque ligne du fichier
    string line;
    bool is_header = true;  // indicateur pour la première ligne
    char* tampon_o; // Pour ne pas copier le pointeur et avoir une perte de données
    char* tampon_d; // Pour ne pas copier le pointeur et avoir une perte de données
    while (getline(file, line)) {
        if (is_header) {
            is_header = false;
            continue;  // sauter la première ligne
        }


        stringstream ss(line);
        string value;



        // Lire chaque valeur de la ligne séparée par des point-virgules
        getline(ss, value, ';');
        strcpy_s(o, 4, value.c_str());
        getline(ss, value, ';');
        strcpy_s(d, 4, value.c_str());
        getline(ss, value, ';');

        
        int tarif = stoi(value);
        O_D current(o, d, {});
        
        if (strcmp(o, o_previous)!=0 || strcmp(d, d_previous) != 0) { 
            // Si on change de binome (origine/destination) alors c'est qu'on a parcouru toutes les lignes avec le binome origine/destination précédent donc on peut insérer dans notre set<O_D> l'objet O_D avec origine destination et le set de tarifs complet d'un coup
            tampon_o = new char[4]; // Sinon on aura une copie de pointeur donc on fait strcpy
            tampon_d = new char[4]; // Sinon on aura une copie de pointeur donc on fait strcpy

            strcpy_s(tampon_o, 4, o_previous);
            strcpy_s(tampon_d, 4, d_previous);
            if (strcmp("xyz", tampon_o) != 0 && strcmp("xyz", tampon_d) != 0) { // On ne va pas copier la valeur par défaut des origine_destination
                O_D to_insert = O_D(tampon_o, tampon_d, tarifs);
                o_d.push_back(to_insert);
            }
            tarifs = {};
        }
        else {
            current.setTarifs(tarifs);
        }
        strcpy_s(o_previous, 4, o);
        strcpy_s(d_previous, 4, d);

        tarifs.insert(tarif);

        // Utilisation d'un itérateur non-const
        //std::cout << "ya ca delement = " << o_d.size() << endl;
    }
    tampon_o = new char[4]; // Sinon on aura une copie de pointeur donc on fait strcpy
    tampon_d = new char[4]; // Sinon on aura une copie de pointeur donc on fait strcpy

    strcpy_s(tampon_o, 4, o_previous);
    strcpy_s(tampon_d, 4, d_previous);
    O_D to_insert = O_D(o_previous, d_previous, tarifs);
    o_d.push_back(to_insert);

    // Affichage des valeurs du vecteur pour tester
    //affiche_vecteur_o_d(o_d);

    return o_d;
}

int export_flightnbr(FlightNbr f, string filename) {
    O_D flightnb_od = *f.getO_D();
    std::ofstream file(filename); // pour append le std::ios::app

    if (!file.is_open()) {
        std::cout << "Impossible d'ouvrir le fichier" << std::endl;
        return 1;
    }
    //file << "Origine;Destination;Min tarif;Max tarif;Tarif moyen," << std::endl;
    file << f.getNoVol() << "," << flightnb_od.getOrigine() << "," << flightnb_od.getDestination() << "," << flightnb_od.minTarif() << "," << flightnb_od.maxTarif() << "," << flightnb_od.avgTarif();

    return 0;
}
int main()
{

    // QUESTION 1 :

    set<long> tarifs_test = { 1000, 1500, 2000, 1857, 2364};
    set<long> tarifs_test2 = { 452, 97, 734, 241, 120 };

    char origine[] = "CDG";
    char destination[] = "EWR";
    O_D objet_test = O_D(origine, destination, tarifs_test);

    cout << "QUESTION 1 : \n" << endl;
    cout << "TEST DES GET: " << endl;

    cout << "GET ORIGINE : " << objet_test.getOrigine() << " GET DESTINATION :" << objet_test.getDestination() << endl;

    objet_test.setDestination("ORY");
    objet_test.setOrigine("JFK");
    cout << "TEST DES SET (ON SET LE MEME OBJET AVEC JFK ET ORY): " << endl;

    cout << "GET ORIGINE : " << objet_test.getOrigine() << " GET DESTINATION :" << objet_test.getDestination() << endl;
    
    // QUESTION 2 et 3 (les fonctions de statistiques et le set):
    cout << "\nQUESTION 2 et 3: \n" << endl;

    cout<< "AVANT LE SET : " << objet_test.getInfos() << endl;

    unsigned int setSize = objet_test.getTarifs().size();
    set<long> t  = objet_test.getTarifs();
    std::cout << "RESULTAT DE GET TARIFS ITERE : " << endl;
    for (set<long>::iterator it = t.begin(); it != t.end(); ++it) {
        cout << *it << endl;
    }
    objet_test.setTarifs(tarifs_test2);

    cout << "APRES LE SET : " << objet_test.getInfos() << endl;
    t = objet_test.getTarifs();
    std::cout << "RESULTAT DE GET TARIFS ITERE : " << endl;
    for (set<long>::iterator it = t.begin(); it != t.end(); ++it) {
        cout << *it << endl;
    }
    // QUESTION 4 : On a stocké le contenu du fichier csv dans une structure vector que l'on va afficher

    vector<O_D> o_d = lire_fichier("C:/Users/Mehdi/Downloads/OrigineDestinationTarif.csv");
    cout << "\nQUESTION 4 : \n" << endl;
    affiche_vecteur_o_d(o_d);

    // QUESTION 5 :
    // REMARQUE : pour des raisons d'organisation de mes fichiers personnels, j'utilise des chemin absolus mais on peut imaginer vouloir stocker ces fichiers au sein du projet avec des chemins relatifs
    cout << "\nQUESTION 5 : la fonction write_into_file a bien ecrit dans le fichier renseigne en parametre \n" << endl;
    string data = "C:/Users/Mehdi/data.csv";
    objet_test.write_into_file(data);
   // obj.toString(); // Afficher les données 
    
    set<long> tarifs2 = { 1,9,0 };
   // obj.setTarifs(tarifs2);

    //cout << obj.getInfos();
    
    // QUESTION 6 :
    cout << "\nQUESTION 6 : la fonction big_file a bien ecrit dans le fichier renseigne en paramètre l'ensemble des donnees requises (origine, dest, min, max, avg) \n" << endl;

    big_file(o_d, "C:/Users/Mehdi/data.csv");

    // QUESTION 7 : création de l'objet FlightNbr

    cout << "\nQUESTION 7 : Creation de l'objet FlightNbr \n" << endl;

    char nb[] = "15615661561";

    FlightNbr f = FlightNbr(nb, &objet_test);
    cout <<"FLIGHT No: " << f.getNoVol() << endl;
    cout << "INFOS O&D : " << f.getO_D()->getInfos() << endl;
    // QUESTION 8 : création de 
    export_flightnbr(f, "C:/Users/Mehdi/export_flight.csv");

    return 0;

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
