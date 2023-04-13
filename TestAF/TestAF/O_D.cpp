#include "O_D.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <fstream>
#include <iostream>

using std::cout; using std::cin;
using std::endl; using std::vector;
using std::accumulate;
using std::round;

long O_D::minTarif() {
	if (!this->tarifs.empty()) {
		return *(this->tarifs.begin());
	}
	return -1;
}

long O_D::maxTarif() {
	if (!this->tarifs.empty()) {
		return *(this->tarifs.rbegin());
	}
	return -1;
}


float O_D::avgTarif() {

	if (!this->tarifs.empty()) {
		double somme = accumulate(this->tarifs.begin(), this->tarifs.end(), 0);
		double size = this->tarifs.size();
		double avg = somme / size;

		// Pour un contenu plus lisible on arrondit au centième près.
		return round(avg*100)/100;
	}
	return -1;

}

void O_D::toString()  {
	std::cout << "Origine : " << this->getOrigine() << " Destination : " << this->getDestination() << " Min tarif : " << this->minTarif() << " Max tarif : " << this->maxTarif() << " Tarif moyen " << this->avgTarif() << endl;
}

string O_D::getInfos() {
	ostringstream convert;
	convert << this->minTarif();
	string min = convert.str();
	convert.str(""); // Purge
	convert << this->maxTarif();
	string max = convert.str();
	convert.str(""); // Purge
	convert << this->avgTarif();
	string avg = convert.str();
	return "Origine : " + string(this->getOrigine()) + " Destination : " + this->getDestination() + " Min tarif : " + min + " Max tarif : " + max + " Tarif moyen " + avg;

}

int O_D::write_into_file(string filename) {
	std::ofstream file(filename, std::ios::app); // pour append le std::ios::app

	if (!file.is_open()) {
		std::cout << "Impossible d'ouvrir le fichier" << std::endl;
		return 1;
	}

	//file << "Origine;Destination;Min tarif;Max tarif;Tarif moyen," << std::endl;
	file << this->getOrigine() << ";" << this->getDestination() << ";" << this->minTarif() << ";"<< this->maxTarif() << ";" << this->avgTarif()  << std::endl;

	file.close();
	return 0;
}


