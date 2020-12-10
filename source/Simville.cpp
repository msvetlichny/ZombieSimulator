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

    //getters for counts - used for reporting
    int Simville::get_ignorant_count(){return ignorant_map.size();}
    int Simville::get_alarmed_count(){return alarmed_map.size();}
    int Simville::get_zombie_count(){return zombie_map.size();}

        //method that sends data to simulator in form of a string
    std::string Simville::get_movedata(){
        //this will be returned to the simulator header where this info will be parsed and new objects in other locations will be created
        moving_data = std::to_string(ignorant_queue.size()) + "p" + std::to_string(alarmed_queue.size()) + "q"+
                      std::to_string(zombie_queue.size()); 
        // "temp" is created within this method and should be automatically cleared after the function stack closes
        // thus we don't need to worry about temp.clear();.              
        std::string temp = moving_data;
        moving_data.clear();
        return temp;
    }
