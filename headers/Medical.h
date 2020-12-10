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

#ifndef MEDICAL_H
#define MEDICAL_H

#include "../headers/Simville.h"

class Medical : public Simville{

    public:

        //Medical constructor 
        // X = chance of ignorant person becoming a zombie
        // Y = chance of ignorant person becoming alarmed from another alarmed person
        // Z = chance of alarmed becoming a zombie
        // Q = chance of an ignorant person moving to a new district
        ////////// ADDITIONAL SPECS //////////
        // P = chance of alarmed person moving to new district
        // R = chance of zombie moving to new district
        Medical(int total_population, int X, int Y, int Z,int Q, int P, int R);

        //test to see if ignorant becomes an alarmed person
        void alert_test(Person P);
        // test to see if alarmed or ignorant becomes a zombie
        void infection_test(Person P);
        // perform test and determine where a person object moves to
        void location_change(Person P);
        // main driving method for each location object. Performs all methods defined in class and creates a string called 
        // moving_data for simulator.h to make use of.
        void update();

        //method that sends data to simulator in form of a string
        std::string get_movedata();
};

#endif