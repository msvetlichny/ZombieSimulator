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

#include "../headers/Simville.h"
#include <iostream>

    //default constructor - this shouldn't be called
    Simville::Simville(){
        std::cout << "DEFAULT CONSTRUCTOR WAS CALLED IN SIMVILLE - THIS IS BAD - END NOW END NOW" << std::endl;
    }
    //main constructor - all subclasses have these traits
    Simville::Simville(int total_population, int X, int Y, int Z, int Q, int P, int R){
        this->total_population = total_population;
        ignorant_to_zombie = X;
        ignorant_to_alarmed = Y;
        alarmed_to_zombie = Z;
        ignorant_move = Q;
        alarmed_move = P;
        zombie_move = R;
    }
