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

    public:

    Simulator(int population, int X, int Y, int Z,int Q, int P, int R);

    // This is going to be the core cog in the entirety of this programs operation. 
    // Update will be iterated to keep "updating" each location, it's population and inhabitants
    void update(Downtown downtown, Soho soho, Docks docks, University university, Medical medical);

    //need method for determining where person objects in a queue go
    void location_move(int k, int person_id, int loc_id, Downtown downtown, Soho soho, Docks docks, University university, Medical medical);
    int zombie_move_parse(std::string str);
    int alarmed_move_parse(std::string str);
    int ignorant_move_parse(std::string str);

};



#endif