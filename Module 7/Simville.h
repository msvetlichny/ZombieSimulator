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
#ifndef SIMVILLE_H_
#define SIMVILLE_H_

#include "Person.h"
#include <iostream>
#include <vector>
#include <map>
#include <queue>

////////////////////////
// - Medical Hill (First case starts here) == 1 
// - The Docks == 2
// - Downtown == 3
// - The University == 4
// - Soho (Safest District) == 5

class Simville {

protected:

	///////////// All below are variables defined per specifications of project ////////////////
	// total_population = population for all, location_id = id number assigned to each location, 
	// ignorant_to_zombie = X, ignorant_to_alarmed = Y, alarmed_to_zombie = Z, ignorant_move = Q, 
	// alarmed_move = P: BONUS, not included in specs, zombie_move = R: BONUS, not included in specs
	int current_population = 0, total_population = 0, location_id = 0, ignorant_to_zombie = 0, ignorant_to_alarmed = 0, alarmed_to_zombie = 0,
		ignorant_move = 0, alarmed_move = 0, zombie_move = 0;

	// Used for communicating information to the Simulator class.
	std::string moving_data;



public:

	// To be used for reporting information
	int ignorant_count = 0;
	int alarmed_count = 0;
	int zombie_count = 0;
	int total_count = 0; // Total number of persons in a city

	// Simulator needs full access to these. In fact, the existence of these are almost entirely   
	// for simulator to be able to modify populations within each location of Simville
	std::queue<Person*> zombie_queue;
	std::queue<Person*> ignorant_queue;
	std::queue<Person*> alarmed_queue;
	std::map<Person*, int> alarmed_map; //
	std::map<Person*, int> ignorant_map;
	std::map<Person*, int> zombie_map;
	std::map<Person*, int>::iterator it; //iterator used to point to objects in a map

//default constructor
	Simville();
	//main constructor accepting all required arguments
	//Simville(int total_population, int X, int Y, int Z, int Q, int P, int R);

	//test to see if ignorant becomes an alarmed person
	void alert_test(std::map<Person*, int>::iterator it);
	// test to see if alarmed or ignorant becomes a zombie
	void infection_test(std::map<Person*, int>::iterator it);
	// perform test and determine where a person object moves to
	void location_change(std::map<Person*, int>::iterator it);

	//getters for counts - used for reporting
	int get_ignorant_count();
	int get_alarmed_count();
	int get_zombie_count();

	//virtual bool probability_check() = 0;
	virtual void update() = 0;

	//method that sends data to simulator in form of a string
	std::string get_movedata();




};


#endif
