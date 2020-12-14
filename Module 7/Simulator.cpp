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

#include "Simulator.h"


	//main constructor that begins the simulation
Simulator::Simulator(int population, int X, int Y, int Z, int Q, int P, int R) {
	
	std::ofstream fout; //declaring an ofstream object

	// open the file & check incase file doesn't open - fname defined in Simulator.h
	fout.open(fname);
	if (fout.fail()) {
		int x = 0;
		std::cout << "Can't open this file" << std::endl;
		std::cin >> x;
	}

	std::cout << "BEGINNING SIMULATION" << std::endl;
	//create all location objects and any other necessary objects
	Downtown downtown(population, X, Y, Z, Q, P, R);
	Soho soho(population, X, Y, Z, Q, P, R);
	Docks docks(population, X, Y, Z, Q, P, R);
	University university(population, X, Y, Z, Q, P, R);
	Medical medical(population, X, Y, Z, Q, P, R);

	Report report;

	//we need to run report.update one more time since the most recent simville update hasn't been recorded yet
	report.update(1, medical.ignorant_map.size(), medical.alarmed_map.size(), medical.zombie_map.size());
	report.update(2, docks.ignorant_map.size(), docks.alarmed_map.size(), docks.zombie_map.size());
	report.update(3, downtown.ignorant_map.size(), downtown.alarmed_map.size(), downtown.zombie_map.size());
	report.update(4, university.ignorant_map.size(), university.alarmed_map.size(), university.zombie_map.size());
	report.update(5, soho.ignorant_map.size(), soho.alarmed_map.size(), soho.zombie_map.size());
	
	
	// Loading bar
	char c = char(219);
	std::string str;
	str.push_back(c);
	system("CLS");
	std::cout << "Loading..." << std::endl;

	//this is the mechanic that drives the simulation. in pseudocode, this is:
	// while( zombie population != total population){
	//		update;
	// }
	
	int zombies = 1;
	while (zombies != population) {
		update(medical, docks, downtown, university, soho, report);
		
		std::cout << str;

		report.update(1, medical.ignorant_map.size(), medical.alarmed_map.size(), medical.zombie_map.size());
		report.update(2, docks.ignorant_map.size(), docks.alarmed_map.size(), docks.zombie_map.size());
		report.update(3, downtown.ignorant_map.size(), downtown.alarmed_map.size(), downtown.zombie_map.size());
		report.update(4, university.ignorant_map.size(), university.alarmed_map.size(), university.zombie_map.size());
		report.update(5, soho.ignorant_map.size(), soho.alarmed_map.size(), soho.zombie_map.size());
		zombies = downtown.zombie_map.size() + soho.zombie_map.size() + docks.zombie_map.size() + university.zombie_map.size() + medical.zombie_map.size();
	}
	
	

	//calculate total stats for each click
	report.calc_total();

	system("CLS");
	std::cout << "SIMULATION COMPLETE AT: " << std::endl;
	std::cout << time_click << " clicks \n\n" << std::endl;
	std::cout << "To see the stats of the simulation, please open \"" << fname << "\" found in: ../source/repos/Final DS/Final DS" << std::endl;
	//sending the report to the file
	fout << report.toString() << std::endl;
}

// This is going to be the core cog in the entirety of this programs operation. 
// Update will be iterated to keep "updating" each location, it's population and inhabitants
void Simulator::update(Medical & medical, Docks & docks, Downtown & downtown, University & university, Soho & soho, Report & report) {
	
	/////////////////////////////////////////////////////////////////////
	medical.update();
	docks.update();
	downtown.update();
	university.update();
	soho.update();

	move_update(medical, docks, downtown, university, soho);

	//now move locations for each area
	//for some reason, these functions during runtime don't actually get called, but they do when you step in to them during debugging
	// Performing location_move for medical  
	location_move(medical_zombies, 3, 1, medical, docks, downtown, university, soho);
	location_move(medical_alarmed, 2, 1, medical, docks, downtown, university, soho);
	location_move(medical_ignorant, 1, 1, medical, docks, downtown, university, soho);
	// Performing location_move for docks 
	location_move(docks_zombies, 3, 2, medical, docks, downtown, university, soho);
	location_move(docks_alarmed, 2, 2, medical, docks, downtown, university, soho);
	location_move(docks_ignorant, 1, 2, medical, docks, downtown, university, soho);
	// Performing location_move for downtown 
	location_move(downtown_zombies, 3, 3, medical, docks, downtown, university, soho);
	location_move(downtown_alarmed, 2, 3, medical, docks, downtown, university, soho);
	location_move(downtown_ignorant, 1, 3, medical, docks, downtown, university, soho);
	// Performing location_move for university 
	location_move(university_zombies, 3, 4, medical, docks, downtown, university, soho);
	location_move(university_alarmed, 2, 4, medical, docks, downtown, university, soho);
	location_move(university_ignorant, 1, 4, medical, docks, downtown, university, soho);
	// Performing location_move for soho 
	location_move(soho_zombies, 3, 5, medical, docks, downtown, university, soho);
	location_move(soho_alarmed, 2, 5, medical, docks, downtown, university, soho);
	location_move(soho_ignorant, 1, 5, medical, docks, downtown, university, soho);

	// need to have a report feature either here or somewhere within simville
	// probably here though.
	
	
	time_click++; //iterate time by 1 each update
	report.clicks++;
}

void Simulator::move_update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho) {

	// collect medical hill movement information "how many person objects need to move"
	medical_zombies = zombie_move_parse(medical.get_movedata());
	medical_alarmed = alarmed_move_parse(medical.get_movedata());
	medical_ignorant = ignorant_move_parse(medical.get_movedata());
	// collect docks movement information "how many person objects need to move"
	docks_zombies = zombie_move_parse(docks.get_movedata());
	docks_alarmed = alarmed_move_parse(docks.get_movedata());
	docks_ignorant = ignorant_move_parse(docks.get_movedata());
	// collect downtown movement information "how many person objects need to move"
	downtown_zombies = zombie_move_parse(downtown.get_movedata());
	downtown_alarmed = alarmed_move_parse(downtown.get_movedata());
	downtown_ignorant = ignorant_move_parse(downtown.get_movedata());
	// collect university movement information "how many person objects need to move"
	university_zombies = zombie_move_parse(university.get_movedata());
	university_alarmed = alarmed_move_parse(university.get_movedata());
	university_ignorant = ignorant_move_parse(university.get_movedata());
	// collect soho movement information "how many person objects need to move" 
	soho_zombies = zombie_move_parse(soho.get_movedata());
	soho_alarmed = alarmed_move_parse(soho.get_movedata());
	soho_ignorant = ignorant_move_parse(soho.get_movedata());

}

int Simulator::zombie_move_parse(std::string str) {
	//parse out the zombie movement information
	std::string temp;
	for (int i = str.find("q") + 1; i < str.length(); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}

int Simulator::alarmed_move_parse(std::string str) {
	//parse out the alarmed  movement information
	std::string temp;
	for (int i = str.find("p") + 1; i < str.find("q"); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}

int Simulator::ignorant_move_parse(std::string str) {
	//parse out the alarmed  movement information
	std::string temp;
	for (int i = 0; i < str.find("p"); i++) {
		temp += str[i];
	}
	return std::stoi(temp);
}

// person_type = one of the three denizens, loc_id = id of the district the person is currently in, 
// k = number of person's to be transferred out of the queue.
void Simulator::location_move(int k, int person_type, int loc_id, Medical & medical, Docks & docks, Downtown & downtown, University & university, Soho & soho) {
	int x = rand() % 10 + 1;
	if (loc_id == 1) { // current location = MEDICAL
		for (int i = 0; i < k; i++) {
			int y = rand() % 5 + 1;
			if (y == 4) {
				//off to university
				if (person_type == 1) {
					delete medical.ignorant_queue.front();
					medical.ignorant_queue.pop();
					Person* P = new Person(1);
					university.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete medical.alarmed_queue.front();
					medical.alarmed_queue.pop();
					Person* P = new Person(2);
					university.alarmed_map[P]++;
				}
				else {
					delete medical.zombie_queue.front();
					medical.zombie_queue.pop();
					Person* P = new Person(3);
					university.zombie_map[P]++;
				}
			}
			else {
				//off to downtown
				if (person_type == 1) {
					delete medical.ignorant_queue.front();
					medical.ignorant_queue.pop();
					Person* P = new Person(1);
					downtown.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete medical.alarmed_queue.front();
					medical.alarmed_queue.pop();
					Person* P = new Person(2);
					downtown.alarmed_map[P]++;
				}
				else {
					delete medical.zombie_queue.front();
					medical.zombie_queue.pop();
					Person* P = new Person(3);
					downtown.zombie_map[P]++;
				}
			}
		}
	}
	else if (loc_id == 2) { // current location = DOCKS
		for (int i = 0; i < k; i++) {
			int y = rand() % 5 + 1; // random chosen path to new location
			if (y == 3) {
				// off to downtown
				if (person_type == 1) {
					delete docks.ignorant_queue.front();
					docks.ignorant_queue.pop();
					Person* P = new Person(1);
					downtown.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete docks.alarmed_queue.front();
					docks.alarmed_queue.pop();
					Person* P = new Person(2);
					downtown.alarmed_map[P]++;
				}
				else {
					delete docks.zombie_queue.front();
					docks.zombie_queue.pop();
					Person* P = new Person(3);
					downtown.zombie_map[P]++;
				}
			}
			else if (y == 4) {
				// off to the University
				if (person_type == 1) {
					delete docks.ignorant_queue.front();
					docks.ignorant_queue.pop();
					Person* P = new Person(1);
					university.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete docks.alarmed_queue.front();
					docks.alarmed_queue.pop();
					Person* P = new Person(2);
					university.alarmed_map[P]++;
				}
				else {
					delete docks.zombie_queue.front();
					docks.zombie_queue.pop();
					Person* P = new Person(3);
					university.zombie_map[P]++;
				}
			}
			else {
				// off to Soho
				if (person_type == 1) {
					delete docks.ignorant_queue.front();
					docks.ignorant_queue.pop();
					Person* P = new Person(1);
					soho.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete docks.alarmed_queue.front();
					docks.alarmed_queue.pop();
					Person* P = new Person(2);
					soho.alarmed_map[P]++;
				}
				else {
					delete docks.zombie_queue.front();
					docks.zombie_queue.pop();
					Person* P = new Person(3);
					soho.zombie_map[P]++;
				}
			}
		}
	}
	else if (loc_id == 3) { // current location = DOWNTOWN
		//now determine where people go
		for (int i = 0; i < k; i++) {
			int y = rand() % 5 + 1; // random chosen path to new location
			if (y == 1) { //medical
				if (person_type == 1) {
					delete downtown.ignorant_queue.front();
					downtown.ignorant_queue.pop();
					Person* P = new Person(1);
					medical.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete downtown.alarmed_queue.front();
					downtown.alarmed_queue.pop();
					Person* P = new Person(2);
					medical.alarmed_map[P]++;
				}
				else {
					delete downtown.zombie_queue.front();
					downtown.zombie_queue.pop();
					Person* P = new Person(3);
					medical.zombie_map[P]++;
				}
			}
			else if (y == 2 || y == 3) {
				// off to the Docks
				if (person_type == 1) {
					delete downtown.ignorant_queue.front();
					downtown.ignorant_queue.pop();
					Person* P = new Person(1);
					docks.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete downtown.alarmed_queue.front();
					downtown.alarmed_queue.pop();
					Person* P = new Person(2);
					docks.alarmed_map[P]++;
				}
				else {
					delete downtown.zombie_queue.front();
					downtown.zombie_queue.pop();
					Person* P = new Person(3);
					docks.zombie_map[P]++;
				}

			}
			else {
				// off to University
				if (person_type == 1) {
					delete downtown.ignorant_queue.front();
					downtown.ignorant_queue.pop();
					Person* P = new Person(1);
					university.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete downtown.alarmed_queue.front();
					downtown.alarmed_queue.pop();
					Person* P = new Person(2);
					university.alarmed_map[P]++;
				}
				else {
					delete downtown.zombie_queue.front();
					downtown.zombie_queue.pop();
					Person* P = new Person(3);
					university.zombie_map[P]++;
				}

			}
		}
	}
	else if (loc_id == 4) { // current location = UNIVERSITY
		//now determine where people go
		for (int i = 0; i < k; i++) {
			int y = rand() % 5 + 1; // random chosen path to new location
			if (y == 1) { //medical
				if (person_type == 1) {
					delete university.ignorant_queue.front();
					university.ignorant_queue.pop();
					Person* P = new Person(1);
					medical.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete university.alarmed_queue.front();
					university.alarmed_queue.pop();
					Person* P = new Person(2);
					medical.alarmed_map[P]++;
				}
				else {
					delete university.zombie_queue.front();
					university.zombie_queue.pop();
					Person* P = new Person(3);
					medical.zombie_map[P]++;
				}
			}
			else if (y == 2) { //docks
				if (person_type == 1) {
					delete university.ignorant_queue.front();
					university.ignorant_queue.pop();
					Person* P = new Person(1);
					docks.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete university.alarmed_queue.front();
					university.alarmed_queue.pop();
					Person* P = new Person(2);
					docks.alarmed_map[P]++;
				}
				else {
					delete university.zombie_queue.front();
					university.zombie_queue.pop();
					Person* P = new Person(3);
					docks.zombie_map[P]++;
				}
			}
			else {  //downtown
				if (person_type == 1) {
					delete university.ignorant_queue.front();
					university.ignorant_queue.pop();
					Person* P = new Person(1);
					downtown.ignorant_map[P]++;
				}
				else if (person_type == 2) {
					delete university.alarmed_queue.front();
					university.alarmed_queue.pop();
					Person* P = new Person(2);
					downtown.alarmed_map[P]++;
				}
				else {
					delete university.zombie_queue.front();
					university.zombie_queue.pop();
					Person* P = new Person(3);
					downtown.zombie_map[P]++;
				}

			}
		}
	}
	else { // current location = SOHO
		for (int i = 0; i < k; i++) {
			int y = rand() % 5 + 1; // random chosen path to new location
			if (person_type == 1) {
				delete soho.ignorant_queue.front();
				soho.ignorant_queue.pop();
				Person* P = new Person(1);
				docks.ignorant_map[P]++;
			}
			else if (person_type == 2) {
				delete soho.alarmed_queue.front();
				soho.alarmed_queue.pop();
				Person* P = new Person(2);
				docks.alarmed_map[P]++;
			}
			else {
				delete soho.zombie_queue.front();
				soho.zombie_queue.pop();
				Person* P = new Person(3);
				docks.zombie_map[P]++;
			}
		}
	}
}
