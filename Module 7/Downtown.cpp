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
#include "Downtown.h"
#include <iostream>
	//Downtown constructor
	////////// BELOW ARE INTIALIZED IN BASE CLASS
	// X = chance of ignorant person becoming a zombie
	// Y = chance of ignorant person becoming alarmed from another alarmed person
	// Z = chance of alarmed becoming a zombie
	// Q = chance of an ignorant person moving to a new district
	////////// ADDITIONAL SPECS //////////
	// P = chance of alarmed person moving to new district
	// R = chance of zombie moving to new district
Downtown::Downtown(int total_population, int X, int Y, int Z, int Q, int P, int R) {
	location_id = 3;
	this->total_population = total_population;
	ignorant_to_zombie = X;
	ignorant_to_alarmed = Y;
	alarmed_to_zombie = Z;
	ignorant_move = Q;
	alarmed_move = P;
	zombie_move = R;
	current_population = (total_population * 0.20); // a percentage of the inputted population

	//for loop to load persons
	for (int i = 0; i < current_population; i++) {
		Person* P = new Person(1);
		ignorant_map[P]++; //increase amount of ignorant people - dereference the person objects
	}
	std::cout << "successfully loaded ignorant persons into downtown" << std::endl;
}


//Biggest location method - everything happens here
void Downtown::update() {
	//establish variables to be used in loops
	zombie_count = zombie_map.size();
	alarmed_count = alarmed_map.size();
	ignorant_count = ignorant_map.size();
	total_count = zombie_map.size() + alarmed_map.size() + ignorant_map.size();
	int tests = 0; //this is a counter variable so that we can accurately test all zombie interactions

	//////////////////////////////////////////////////////////////
	// THE ORDER IN WHICH THESE LOOPS OCCUR IS IMPORANT 
	// AND CAN SIGNIFICANTLY CHANGE THE OUTCOME OF THE SIMULATION
	// - we're going to test alarmed denizens first followed by ignorant
	// need to split amount of tests in the next two for loops.
	if (alarmed_map.size() > 0) { // we have this conditional so that we can potentially skip the for-loop
		for (int i = 0; i < zombie_count; i++) {
			if (alarmed_map.size() > 0) {
				// reassign iterator to be looking at the first element of the map every time, until that person
				// eventually becomes a zombie and is removed from the alarmed map.
				it = alarmed_map.begin();
				infection_test(it); //it->first is = Person P //POTENTIAL ERROR FLAG HERE
				tests++;
			}
		}
	}
	//testing ignorant after alarmed. Need to make sure we aren't doubling up on interactions/tests, hence "zombie_count - tests".
	if (ignorant_map.size() > 0) {
		for (int i = 0; i < zombie_count - tests; i++) {
			if (ignorant_map.size() > 0) {
				// see comment in loop above
				it = ignorant_map.begin();
				infection_test(it); //POTENTIAL ERROR FLAG HERE
				tests++;
			}
		}
		//potential code for testing for bugs:
		// if(tests != zombie_count){
		//      std::cout << "ZOMBIE TESTS DONT ALIGN" << std::endl;   
		// }
	}
	//we want to use a "constant" value "alarmed_count" otherwise this loop could grow in size while it's performing  
	//the set number of tests
	for (int i = 0; i < alarmed_count; i++) {
		if (ignorant_map.size() > 0) {
			// reassign iterator to be looking at the first element of the map every time, until that person
			// eventually becomes alarmed and is removed from the ignorant map.
			it = ignorant_map.begin();
			alert_test(it);
		}
	}
	if (total_count > 0) {
		for (int i = 0; i < ignorant_map.size(); i++) {
			// reassign iterator to be looking at the beginning of the map since
			// everytime location change returns true, there will be a new "first" person
			// in the map since they will have been sent to the queue.
			it = ignorant_map.begin();
			location_change(it);
		}
		for (int i = 0; i < alarmed_map.size(); i++) {
			//see comment for ignorant map above
			it = alarmed_map.begin();
			location_change(it);
		}
		for (int i = 0; i < zombie_map.size(); i++) {
			//see comment for ignorant map above
			it = zombie_map.begin();
			location_change(it);
		}
	}

	//REUPDATE OUR COUNTS FOR EACH PERSON TYPE:
	zombie_count = zombie_map.size();
	alarmed_count = alarmed_map.size();
	ignorant_count = ignorant_map.size();
}






