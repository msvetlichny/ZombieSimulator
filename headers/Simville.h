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
#ifndef SIMVILLE_H
#define SIMVILLE_H

#include "../headers/Person.h"
#include <vector>
#include <map>
#include <queue>

////////////////////////
//      - Downtown == 3
//      - Soho (Safest District) == 5
//      - The Docks == 2
//      - Medical Hill (First case starts here) == 1
//      - The University == 4

class Simville{

    protected:

        //All below are variables defined per specifications of project
        int current_population; // population unique to locations
        int total_population; // population for all
        int location_id; // id number assigned to each location
        int ignorant_to_zombie; // = X
        int ignorant_to_alarmed; // = Y
        int alarmed_to_zombie; // = Z
        int ignorant_move; // = Q 
        int alarmed_move; // = P: BONUS, not included in specs
        int zombie_move; // = R: BONUS, not included in specs
        std::string moving_data;

        int ignorant_count;
        int alarmed_count;
        int zombie_count;
        int total_count; // Total number of persons in a city

    public:

        //these are public so that the simulator header can modify and manage these easily
        std::queue<Person> zombie_queue;
        std::queue<Person> ignorant_queue;
        std::queue<Person> alarmed_queue;
        std::map<Person, int> alarmed_map;
        std::map<Person, int> ignorant_map;
        std::map<Person, int> zombie_map;
        std::map<Person , int>::iterator it; //iterator used to point to objects in a map


    Simville();
    Simville(int total_population, int X, int Y, int Z, int Q, int P, int R){
        //this->total_population = total_population;

    }

    //virtual bool probability_check() = 0;
    virtual void update() = 0;


};


#endif