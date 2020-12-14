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

#include "Simville.h"
#include <iostream>
#include <string>

	//default constructor - this shouldn't be called
Simville::Simville() {
	//We let each district constructor handle this

}


 //test to see if ignorant becomes an alarmed person
void Simville::alert_test(std::map<Person*, int>::iterator it) {
	
	int x = rand() % 101;
	if (alarmed_map.size() > 0) {
		if (it->first->get_id() == 1) {
			if (x <= ignorant_to_alarmed) { //50% change the ignorant person becomes alarmed from another alarmed person
				delete it->first;
				ignorant_map.erase(it);
				ignorant_count--;
				Person* P = new Person(2);
				alarmed_map[P]++;
				alarmed_count++;
			}
		}
		//if we want to make ignorant able to change an alarmed person to ignorant, here is where we do it.
		//insert else statement here for bonus code:
	}

}

//test to see if alarmed or ignorant becomes a zombie
void Simville::infection_test(std::map<Person*, int>::iterator it) {

	//first check that the map contains each type of person
	int x = rand() % 101; //between 1% and 100%
	//first check if there are no zombies. no one gets infected without the presence of zombies
	if (zombie_map.size() > 0) {
		if (it->first->get_id() == 2) {
			if (x <= alarmed_to_zombie) {
				delete it->first;
				alarmed_map.erase(it);
				alarmed_count--;
				Person* P = new Person(3);
				zombie_map[P]++;
				zombie_count++;
			}
			//no further statement needed. If the person doesn't get infected, we just continue on with the simulation
		}
		else {
			//if a ignorant person encounters a zombie:
			if (x <= ignorant_to_zombie) {
				delete it->first;
				ignorant_map.erase(it);
				ignorant_count--;
				Person* P = new Person(3);
				zombie_map[P]++;
				zombie_count++;
			}
			else {
				//Person didn't become a zombie, so they became alarmed!
				delete it->first;
				ignorant_map.erase(it);
				ignorant_count--; 
				Person* P = new Person(2);
				alarmed_map[P]++;
				alarmed_count++;
			}
		}

	}
}

void Simville::location_change(std::map<Person*, int>::iterator it) {

	int x = rand() % 101;
	if (it->first->get_id() == 1) {
		//calculate probability of person moving from one location to the next if they are alarmed, and where they go:
		if (x <= ignorant_move) {
			delete it->first;
			ignorant_map.erase(it);
			current_population--;
			Person * P = new Person(1);
			ignorant_queue.push(P);
		}
	}
	else if (it->first->get_id() == 2) {
		//if person is a alarmed person
		if (x <= alarmed_move) {
			delete it->first;
			alarmed_map.erase(it);
			current_population--;
			Person* P = new Person(2);
			alarmed_queue.push(P);
		}
	}
	else {
		//calculate probabilty of zombie moving from one location to next
		if (x <= zombie_move) {
			delete it->first;
			zombie_map.erase(it);
			current_population--;
			Person* P = new Person(3);
			zombie_queue.push(P);

		}
	}
}

//getters for counts - used for reporting
int Simville::get_ignorant_count() { return ignorant_map.size(); }
int Simville::get_alarmed_count() { return alarmed_map.size(); }
int Simville::get_zombie_count() { return zombie_map.size(); }


//method that sends data to simulator in form of a string
std::string Simville::get_movedata() {
	//this will be returned to the simulator header where this info will be parsed and new objects in other locations will be created
	moving_data = std::to_string(ignorant_queue.size()) + "p" + std::to_string(alarmed_queue.size()) + "q" +
		std::to_string(zombie_queue.size());
	// "temp" is created within this method and should be automatically cleared after the function stack closes
	// thus we don't need to worry about temp.clear();.              
	std::string temp = moving_data;
	moving_data.clear();
	return temp;
}
