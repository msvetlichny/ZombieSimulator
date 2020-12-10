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
#include "../headers/Simulator.h"

    //main constructor that begins the simulation
    Simulator::Simulator(int population, int X, int Y, int Z,int Q, int P, int R){
        //create all location objects and any other necessary objects
            // while (people aren't zomebies){
            //      update();    
            // }
            Downtown downtown(population, X, Y, Z, Q, P, R);
            // Soho soho(population, X, Y, Z, Q, P, R);
            // Docks docks(population, X, Y, Z, Q, P, R);
            // University university(population, X, Y, Z, Q, P, R);
            // Medicalhill medical(population, X, Y, Z, Q, P, R);

            //while(zombies != population){
            //    update
            //}
    }

    // This is going to be the core cog in the entirety of this programs operation. 
    // Update will be iterated to keep "updating" each location, it's population and inhabitants
    void Simulator::update(Downtown downtown, Soho soho, Docks docks, University university, Medical medical){
        /////////////////////////////////////////////////////////////////////
        //code for downtown
        downtown.update();
        //downtown zombies in move queue, downtown alarmed, downtown ignorant
        int dz = zombie_move_parse(downtown.get_movedata());
        int da = alarmed_move_parse(downtown.get_movedata());
        int di = ignorant_move_parse(downtown.get_movedata());
        location_move(dz, 3, 3, downtown, soho, docks, university, medical);
        location_move(da, 2, 3, downtown, soho, docks, university, medical);
        location_move(di, 1, 3, downtown, soho, docks, university, medical);
        
    }

    //need method for determining where person objects in a queue go
    void Simulator::location_move(int k, int person_type, int loc_id, Downtown downtown, Soho soho, Docks docks, University university, Medical medical){
        int x = rand() % 10 +1;
        for(int i = 0; i < k; i++){
            if(loc_id == 1){ //medicalhill

            }
            else if(loc_id == 2){ //DOCKS
                for(int i = 0; i < k; i++){
                    int y = rand() % 5 + 1; // random chosen path to new location
                    if(y == 3){
                        // off to downtown
                        if(person_type == 1){
                            docks.ignorant_queue.pop();
                            Person P(1);
                            docks.ignorant_map[P]++;
                        }
                        else if(person_type == 2){
                            docks.alarmed_queue.pop();
                            Person P(2);
                            docks.alarmed_map[P]++;
                        }
                        else{
                            docks.zombie_queue.pop();
                            Person P(3);
                            docks.zombie_map[P]++;
                        }
                    }
                    else if(y == 4){
                        // off to the University
                        
                    }
                    else{
                        // off to Soho

                    } 
                }
            }
            else if(loc_id == 3){ //DOWNTOWN
                //now determine where people go
                for(int i = 0; i < k; i++){
                    int y = rand() % 5 + 1; // random chosen path to new location
                    if(y == 1){
                        // off to medical
                    
                    }
                    else if(y == 2 || y == 3){
                        // off to the Docks
            
                    }
                    else{
                        // off to University

                    } 
                }
            }
            else if(loc_id == 4){ //univeristy

            }
            else{ //soho

            }
        }
    }

    int Simulator::zombie_move_parse(std::string str){
        //parse out the zombie movement information
        std::string temp;
        for(int i = str.find("q") + 1; i < str.length(); i++){
            temp += str[i];
        }
        return std::stoi(temp); 
    }

    int Simulator::alarmed_move_parse(std::string str){
        //parse out the alarmed  movement information
        std::string temp;
        for(int i = str.find("p") + 1; i < str.find("q"); i++){
            temp += str[i];
        }
        return std::stoi(temp);
    }

    int Simulator::ignorant_move_parse(std::string str){
        //parse out the alarmed  movement information
        std::string temp;
        for(int i = 0; i < str.find("p"); i++){
            temp += str[i];
        }
        return std::stoi(temp);
    }
