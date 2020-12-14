//////////////////////////////////////////////////
// Name: Michael Svetlichny, Jonathan Hamstra, Shane Modena
// Date: 12/9/2020
// Course Code: CS-273-1
// Copyright (C) Whitworth University 2020 - 2021
// Purpose: Create a Zombie Apocalypse 
// Source: http://www.cplusplus.com/reference/queue/queue/
//         http://www.cplusplus.com/reference/map/map/
//		   http://www.cplusplus.com/reference/string/string/
//         Module 5 assignment
//////////////////////////////////////////////////
#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "Report.h"
#include "Simville.h"
#include "Downtown.h"
#include "Docks.h"
#include "Medical.h"
#include "Soho.h"
#include "University.h"
#include "Person.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ios>
#include <fstream>


class Simulator {

private:

	//int zombie_movingdata, ignorant_movingdata, alarmed_movingdata;
	//variables to be modified by location_move method
	int medical_zombies = 0, medical_alarmed = 0, medical_ignorant = 0;
	int docks_zombies = 0, docks_alarmed = 0, docks_ignorant = 0;
	int downtown_zombies = 0, downtown_alarmed = 0, downtown_ignorant = 0;
	int university_zombies = 0, university_alarmed = 0, university_ignorant = 0;
	int soho_zombies = 0, soho_alarmed = 0, soho_ignorant = 0;
	//define the name of our ofstream object
	std::string fname = "apocalypse_stats.csv";

public:
	//set to zero for portion of simulation. We can determine what each value of time means.
	//to be used by report header
	int time_click = 0;

	Simulator(int population, int X, int Y, int Z, int Q, int P, int R);

	// This is going to be the core cog in the entirety of this programs operation. 
	// Update will be iterated to keep "updating" each location, it's population and inhabitants
	void update(Medical & medical, Docks & docks, Downtown & downtown, University & university, Soho & soho, Report & report);

	//need method for determining where person objects in a queue go
	void location_move(int k, int person_id, int loc_id, Medical & medical, Docks & docks, Downtown & downtown, University & university, Soho & soho);

	//method that takes the three move parsers and updates all variables
	void move_update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho);

	int zombie_move_parse(std::string str);
	int alarmed_move_parse(std::string str);
	int ignorant_move_parse(std::string str);

};



#endif
