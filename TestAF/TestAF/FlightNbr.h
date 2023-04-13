#pragma once
#pragma once
#include<set>
#include<string>
#include <fstream>
#include <iostream>
#include "O_D.h"

class FlightNbr
{
	char* no_vol;
	O_D* o_d;
	public: 
		FlightNbr(char* no_vol, O_D* o_d) : no_vol(no_vol), o_d(o_d) {};
		char* getNoVol() {
			return this->no_vol;
		}
		O_D* getO_D() {
			return this->o_d;
		}
		void o_d_infos() {
			this->o_d->toString();
		}

};

