#pragma once
#include<set>
#include<string>
#include <fstream>
#include <iostream>
using namespace std;


class O_D
{
	char* origine;
	char* destination; 
	set<long> tarifs; // Observation sur l'utiliation d'un set: très pratique surtout au niveau de l'insertion et du tri automatique qui permet l'accès immédiat aux min et max. Toutefois, il me semble que la petite limite que je peux trouver à cette structure de données est qu'elle n'admet pas de doublon. Or, dans le cadre d'un use case incluant des calculs de moyenne, la pondération des tarifs pourrait permettre d'avoir une moyenne plus précise. Peut être que les prix sont quasiment tous uniques? 
// Aussi pourquoi met-on set<long> alors qu'il y a des val décimales?
public:
	
	O_D(char* o, char* d, set<long> t) : origine(o), destination(d), tarifs(t) {};
	char* getOrigine() { return this->origine; }
	char* getDestination() { return this->destination; }
	void setOrigine(string new_origine) { 
		this->origine = new char[new_origine.length() + 1];
		size_t size = (new_origine.length() + 1) * sizeof(char);
		strcpy_s(this->origine, size, new_origine.c_str());
	}
	void setDestination(string new_destination) { 
		this->destination = new char[new_destination.length() + 1];
		size_t size = (new_destination.length() + 1) * sizeof(char);
		strcpy_s(this->destination, size, new_destination.c_str());
	}

	set<long> getTarifs() { return this->tarifs; }
	void setTarifs(set<long> tarifs) { this->tarifs = tarifs; }
	long minTarif();
	long maxTarif();
	float avgTarif();
	void toString();
	string getInfos();
	int write_into_file(string file);
	// Définir l'opérateur "<" comme une méthode publique
	bool operator<(const O_D& other) const {
		return strcmp(this->origine,other.origine)<0 || strcmp(this->origine, other.origine) == 0 && strcmp(this->destination, other.destination) <0;
	}
	bool operator==(const O_D& other) const {
		return strcmp(this->origine, other.origine) + strcmp(this->destination, other.destination) == 0;
	}
	
};

