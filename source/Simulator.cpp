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
            
            Downtown downtown(population, X, Y, Z, Q, P, R);
            Soho soho(population, X, Y, Z, Q, P, R);
            Docks docks(population, X, Y, Z, Q, P, R);
            University university(population, X, Y, Z, Q, P, R);
            Medical medical(population, X, Y, Z, Q, P, R);

            //while(zombies != population){
            //    update
            //}
    }

    // This is going to be the core cog in the entirety of this programs operation. 
    // Update will be iterated to keep "updating" each location, it's population and inhabitants
    void Simulator::update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho){
        /////////////////////////////////////////////////////////////////////
        // 
        medical.update();
        docks.update();
        downtown.update();
        university.update();
        soho.update();
        move_update(medical, docks, downtown, university, soho);

        //now move locations for each area
        location_move(medical_zombies, 3, 1, medical, docks, downtown, university, soho);
        location_move(medical_alarmed, 2, 1, medical, docks, downtown, university, soho);
        location_move(medical_ignorant, 1, 1, medical, docks, downtown, university, soho);

        location_move(docks_zombies, 3, 2, medical, docks, downtown, university, soho);
        location_move(docks_alarmed, 2, 2, medical, docks, downtown, university, soho);
        location_move(docks_ignorant, 1, 2, medical, docks, downtown, university, soho);

        location_move(downtown_zombies, 3, 3, medical, docks, downtown, university, soho);
        location_move(downtown_alarmed, 2, 3, medical, docks, downtown, university, soho);
        location_move(downtown_ignorant, 1, 3, medical, docks, downtown, university, soho);

        location_move(university_zombies, 3, 4, medical, docks, downtown, university, soho);
        location_move(university_alarmed, 2, 4, medical, docks, downtown, university, soho);
        location_move(university_ignorant, 1, 4, medical, docks, downtown, university, soho);

        location_move(soho_zombies, 3, 5, medical, docks, downtown, university, soho);
        location_move(soho_alarmed, 2, 5, medical, docks, downtown, university, soho);
        location_move(soho_ignorant, 1, 5, medical, docks, downtown, university, soho);
        // need to have a report feature either here or somewhere within simville
        // probably here though.
        time_click++; //iterator time by 1 each update
    }

    // person_type = one of the three denizens, loc_id = id of the district the person is currently in, 
    // k = number of person's to be transferred out of the queue.
    void Simulator::location_move(int k, int person_type, int loc_id, Medical medical, Docks docks, Downtown downtown, University university, Soho soho){
        int x = rand() % 10 +1;
        if(loc_id == 1){ // current location = MEDICAL
            
        }
        else if(loc_id == 2){ // current location = DOCKS
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
        else if(loc_id == 3){ // current location = DOWNTOWN
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
        else if(loc_id == 4){ // current location = UNIVERSITY

        }
        else{ // current location = SOHO

        }
    
    }

    void Simulator::move_update(Medical medical, Docks docks, Downtown downtown, University university, Soho soho){
        
        // collect medical hill movement information "how many person objects need to move"
        medical_zombies = zombie_move_parse(medical.get_movedata());
        medical_alarmed = alarmed_move_parse(medical.get_movedata());
        medical_ignorant = ignorant_move_parse(medical.get_movedata());
        // collect docks movement information "how many person objects need to move"
        docks_zombies = zombie_move_parse(docks.get_movedata());
        docks_alarmed = alarmed_move_parse(docks.get_movedata());
        docks_ignorant = ignorant_move_parse(docks.get_movedata());
        // collect downtown movement information "how many person objects need to move"
        downtown_zombies = zombie_move_parse(downtown.get_movedata());
        downtown_alarmed = alarmed_move_parse(downtown.get_movedata());
        downtown_ignorant = ignorant_move_parse(downtown.get_movedata());
        // collect university movement information "how many person objects need to move"
        university_zombies = zombie_move_parse(university.get_movedata());
        university_alarmed = alarmed_move_parse(university.get_movedata());
        university_ignorant = ignorant_move_parse(university.get_movedata());       
        // collect soho movement information "how many person objects need to move" 
        soho_zombies = zombie_move_parse(soho.get_movedata());
        soho_alarmed = alarmed_move_parse(soho.get_movedata());
        soho_ignorant = ignorant_move_parse(soho.get_movedata());        

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
