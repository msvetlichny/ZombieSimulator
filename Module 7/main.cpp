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
//		   Airport Simulator uploaded by Prof. Matt - Whitworth CS department
//////////////////////////////////////////////////
// X = chance of ignorant person becoming a zombie
// Y = chance of ignorant person becoming alarmed from another alarmed person
// Z = chance of alarmed becoming a zombie
// Q = chance of an ignorant person moving to a new district
////////// ADDITIONAL (BONUS) SPECS //////////
// P = chance of alarmed person moving to new district
// R = chance of zombie moving to new district

#include "Simulator.h"


//function from airport simulator 
int read_int(const std::string& prompt);

int main() {
	// define our random number generator and seed with time null.
	srand(time(NULL));

	// Initialize variables for user to specify
	// Collect information from the user
	int user_population = read_int("Please enter the population size (recommended 2000 per project specification): ");
	int ignorant_to_zombie = read_int("Please enter the probability of an ignorant person becoming a zombie per time click: ");
	int ignorant_to_alarmed = read_int("Please enter the probability that an alarmed person makes an ignorant person alarmed: ");
	int alarmed_to_zombie = read_int("Please enter the probability of an alarmed person becoming a zombie per time click: ");
	int ignorant_move = read_int("Please enter the probability that an ignorant person will move districts per time click: ");
	int alarmed_move = read_int("Please enter the probability that an alarmed person will move districts per time click: ");
	int zombie_move = read_int("Please enter the probability that a zombie will move distrcts per time click: ");

	// Perform the simulation by passing in user information into simulator object
	Simulator sim(user_population, ignorant_to_zombie, ignorant_to_alarmed, alarmed_to_zombie, ignorant_move, alarmed_move, zombie_move);
	
	return 0;
}


// THIS FUNCTION WAS COPIED FROM THE AIRPORT SIMULATOR PROVIDED BY PROFESSOR MATT
int read_int(const std::string& prompt) {
		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				std::cout << prompt;
				std::cin >> num;
				std::cout << std::endl;
				return num;
			}
			catch (std::ios_base::failure& ex) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

