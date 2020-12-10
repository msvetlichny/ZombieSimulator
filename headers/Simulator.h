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
#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "../headers/Simville.h"
#include "../headers/Downtown.h"
#include "../headers/Docks.h"
#include "../headers/Medical.h"
#include "../headers/Soho.h"
#include "../headers/University.h"
#include "../headers/Person.h"

class Simulator{

    private:

        int zombie_movingdata, ignorant_movingdata, alarmed_movingdata;
        //variables to be modified by location_move method
        int medical_zombies, medical_alarmed, medical_ignorant = 0;
        int docks_zombies, docks_alarmed, docks_ignorant = 0;
        int downtown_zombies, downtown_alarmed, downtown_ignorant = 0;
        int university_zombies, university_alarmed, university_ignorant = 0;
        int soho_zombies, soho_alarmed, soho_ignorant = 0;
        
    public:
        //set to zero for portion of simulation. We can determine what each value of time means.
        //to be used by report header
        int time_click = 0; 

        Simulator(int population, int X, int Y, int Z,int Q, int P, int R);

        // This is going to be the core cog in the entirety of this programs operation. 
        // Update will be iterated to keep "updating" each location, it's population and inhabitants
        void update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho);

        //need method for determining where person objects in a queue go
        void location_move(int k, int person_id, int loc_id, Medical medical, Docks docks, Downtown downtown, University university, Soho soho);

        //method that takes the three move parsers and updates all variables
        void move_update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho);

        int zombie_move_parse(std::string str);
        int alarmed_move_parse(std::string str);
        int ignorant_move_parse(std::string str);

};



#endif