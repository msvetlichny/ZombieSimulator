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
//		   Michael's LM18 from CS-172-2
//////////////////////////////////////////////////
#ifndef REPORT_H_
#define REPORT_H_

#include "Simulator.h"

// Even though Simlator.h has both vector and string included, Visual Studio was taking way too long to figure this out.
// You would essentially have to rebuild like 6 times for all the errors to slowly disappear, thus finally recognizing 
// that string and vector are part of std:: ...
#include <vector> 
#include <string> 

class Report {

private:

	
	std::vector<int> medical_ignorant_click, medical_alarmed_click, medical_zombie_click; // loc_id == 1
	std::vector<int> docks_ignorant_click, docks_alarmed_click, docks_zombie_click; // loc_id == 2
	std::vector<int> downtown_ignorant_click, downtown_alarmed_click, downtown_zombie_click; // loc_id == 3
	std::vector<int> university_ignorant_click, university_alarmed_click, university_zombie_click; // loc_id == 4
	std::vector<int> soho_ignorant_click, soho_alarmed_click, soho_zombie_click; // loc_id == 5
	std::vector<int> total_ignorant_click, total_alarmed_click, total_zombie_click; // all locations

public:
	//use simulator to iterate this
	int clicks = 0;
	//default constructor for report
	Report() {

	}

	void update(int loc_id ,int ignorant_count, int alarmed_count, int zombie_count) {
		
		if (loc_id == 1) {
			medical_ignorant_click.push_back(ignorant_count);
			medical_alarmed_click.push_back(alarmed_count);
			medical_zombie_click.push_back(zombie_count);
		}
		else if (loc_id == 2) {
			docks_ignorant_click.push_back(ignorant_count);
			docks_alarmed_click.push_back(alarmed_count);
			docks_zombie_click.push_back(zombie_count);
		}
		else if (loc_id == 3) {
			downtown_ignorant_click.push_back(ignorant_count);
			downtown_alarmed_click.push_back(alarmed_count);
			downtown_zombie_click.push_back(zombie_count);
		}
		else if (loc_id == 4) {
			university_ignorant_click.push_back(ignorant_count);
			university_alarmed_click.push_back(alarmed_count);
			university_zombie_click.push_back(zombie_count);
		}
		else {
			soho_ignorant_click.push_back(ignorant_count);
			soho_alarmed_click.push_back(alarmed_count);
			soho_zombie_click.push_back(zombie_count);
		}
	}

	//void set_zombie_count();

	void calc_total() {
		//fill in totals for each
		for (int i = 0; i < medical_zombie_click.size(); i++) {
			total_ignorant_click.push_back(medical_ignorant_click[i] + docks_ignorant_click[i] + downtown_ignorant_click[i] + university_ignorant_click[i] + soho_ignorant_click[i]);
		}
		for (int i = 0; i < medical_zombie_click.size(); i++) {
			total_alarmed_click.push_back(medical_alarmed_click[i] + docks_alarmed_click[i] + downtown_alarmed_click[i] + university_alarmed_click[i] + soho_alarmed_click[i]);
		}
		for (int i = 0; i < medical_zombie_click.size(); i++) {
			total_zombie_click.push_back(medical_zombie_click[i] + docks_zombie_click[i] + downtown_zombie_click[i] + university_zombie_click[i] + soho_zombie_click[i]);
		}
	}

	std::string toString() {

		// collect all data and output in a neat form for a .csv file
		std::string str;
		str = "Medical Ignorant,Medical Alarmed,Medical Zombie,Docks Ignorant,Docks Alarmed,Docks Zombie,Downtown Ignorant,Downtown Alarmed,Downtown Zombie,";
		str.append("University Ignorant,University Alarmed,University Zombie,Soho Ignorant,Soho Alarmed,Soho Zombie,Total Ignorant,Total Alarme,Total Zombie \n");
		for (int i = 0; i < total_zombie_click.size(); i++) {

			str.append(std::to_string(medical_ignorant_click[i]) + "," + std::to_string(medical_alarmed_click[i]) + "," + std::to_string(medical_zombie_click[i]) + ",");
			str.append(std::to_string(docks_ignorant_click[i]) + "," + std::to_string(docks_alarmed_click[i]) + "," + std::to_string(docks_zombie_click[i]) + ",");
			str.append(std::to_string(downtown_ignorant_click[i]) + "," + std::to_string(downtown_alarmed_click[i]) + "," + std::to_string(downtown_zombie_click[i]) + ",");
			str.append(std::to_string(university_ignorant_click[i]) + "," + std::to_string(university_alarmed_click[i]) + "," + std::to_string(university_zombie_click[i]) + ",");
			str.append(std::to_string(soho_ignorant_click[i]) + "," + std::to_string(soho_alarmed_click[i]) + "," + std::to_string(soho_zombie_click[i]) + ",");
			str.append(std::to_string(total_ignorant_click[i]) + "," + std::to_string(total_alarmed_click[i]) + "," + std::to_string(total_zombie_click[i]) + "\n");
		}
		return str;
	}
};

#endif