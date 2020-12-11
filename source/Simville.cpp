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
        //std::cout << "DEFAULT CONSTRUCTOR WAS CALLED IN SIMVILLE - THIS IS BAD - END NOW END NOW" << std::endl;
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
        std::cout << "test 1" << std::endl; 
    }

     //test to see if ignorant becomes an alarmed person
    void Simville::alert_test(Person P){
        std::cout << "testing alert test" << std::endl;
        int x = rand() % 100 + 1;
        if(alarmed_map.size() > 0){
            if(P.get_id() == 1){
                if(x <= ignorant_to_alarmed){ //50% change the ignorant person becomes alarmed from another alarmed person
                    ignorant_map[P]--;
                    P.set_id(2);
                    alarmed_map[P]++;
                }
            }
            //if we want to make ignorant able to change an alarmed person to ignorant, here is where we do it.
            //insert else statement here for bonus code:
        }
        
    }

    //test to see if alarmed or ignorant becomes a zombie
    void Simville::infection_test(Person P){
        std::cout << "testing infection test" << std::endl;
        //first check that the map contains each type of person
        int x = rand() % 100 + 1;
        //first check if there are no zombies. no one gets infected without the presence of zombies
        if(zombie_map.size() > 0){
            if(P.get_id() == 2){
                if(x <= alarmed_to_zombie){
                    alarmed_map[P]--;
                    P.set_id(3); //set id = 3 for zombie
                    zombie_map[P]++;
                }
                //no further statement needed. If the person doesn't get infected, we just continue on with the simulation
            }
            else{
                //if a ignorant person encounters a zombie:
                if(x <= ignorant_to_zombie){
                    ignorant_map[P]--;
                    P.set_id(3); //set id = 3 for zombie
                    zombie_map[P]++;
                }
                else{
                    //Person didn't become a zombie, so they became alarmed!
                    ignorant_map[P]--;
                    P.set_id(2); //set id = 2 for 
                    alarmed_map[P]++;
                }
            }

        }
    }

    void Simville::location_change(Person P){
        std::cout << "testing location change" << std::endl;
        int x = rand() % 100 + 1;
        if(P.get_id() == 1){
            //calculate probability of person moving from one location to the next if they are alarmed, and where they go:
            if(x <= ignorant_move){
                ignorant_map[P]--;
                current_population--;
                ignorant_queue.push(P);
            }
        }
        else if (P.get_id() == 2){
            //if person is a alarmed person
            if(x <= alarmed_move){
                alarmed_map[P]--;
                current_population--;
                alarmed_queue.push(P);
            }
        }
        else{
            //calculate probabilty of zombie moving from one location to next
            if(x <= zombie_move){
                zombie_map[P]--;
                current_population--;
                zombie_queue.push(P); 
                
            }
        }
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
