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
#include "../headers/Downtown.h"
 
    //Downtown constructor
    ////////// BELOW ARE SET IN BASE CLASS
    // X = chance of ignorant person becoming a zombie
    // Y = chance of ignorant person becoming alarmed from another alarmed person
    // Z = chance of alarmed becoming a zombie
    // Q = chance of an ignorant person moving to a new district
    ////////// ADDITIONAL SPECS //////////
    // P = chance of alarmed person moving to new district
    // R = chance of zombie moving to new district
    Downtown::Downtown(int total_population, int X, int Y, int Z, int Q, int P, int R){
        location_id == 3;
        current_population = total_population * (5/20); //a percentage of the inputted population
        
        for(int i = 0; i < current_population; i++){
            Person P(1); 
            ignorant_map[P]++; //increase amount of ignorant people - dereference the person objects
        }
    }

    //test to see if ignorant becomes an alarmed person
    void Downtown::alert_test(Person P){
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
    void Downtown::infection_test(Person P){
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

    void Downtown::location_change(Person P){
        int x = rand() % 10 + 1;
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

    //Biggest location method - everything happens here
    void Downtown::update(){
        //establish variables to be used in loops
        zombie_count = zombie_map.size();
        alarmed_count = alarmed_map.size();
        ignorant_count = ignorant_map.size();
        total_count = zombie_map.size() + alarmed_map.size() + ignorant_map.size();
        int tests = 0; //this is a counter variable so that we can accurately test all zombie interactions

        //////////////////////////////////////////////////////////////
        // THE ORDER IN WHICH THESE LOOPS OCCUR IS IMPORANT 
        // AND CAN SIGNIFICANTLY CHANGE THE OUTCOME OF THE SIMULATION
        // - we're going to test alarmed denizens first followed by ignorant
        // need to split amount of tests in the next two for loops.
        if(alarmed_map.size() > 0){ // we have this conditional so that we can potentially skip the for-loop
            for(int i = 0; i < zombie_count; i++){
                if(alarmed_map.size() > 0){
                    // reassign iterator to be looking at the first element of the map every time, until that person
                    // eventually becomes a zombie and is removed from the alarmed map.
                    it = alarmed_map.begin(); 
                    infection_test(it->first); //it->first is = Person P
                    tests++;
                }
            }
        }
        //testing ignorant after alarmed. Need to make sure we aren't doubling up on interactions/tests, hence "zombie_count - tests".
        if(ignorant_map.size() > 0){  
            for(int i = 0; i < zombie_count - tests; i++){
                if(ignorant_map.size() > 0){
                    // see comment in loop above
                    it = ignorant_map.begin(); 
                    infection_test(it->first);
                    tests++;
                }
            }
            //potential code for testing for bugs:
            // if(tests != zombie_count){
            //      std::cout << "ZOMBIE TESTS DONT ALIGN" << std::endl;   
            // }
        }
        //we want to use a "constant" value "alarmed_count" otherwise this loop could grow in size while it's performing  
        //the set number of tests
        for(int i = 0; i < alarmed_count; i++){
            if(ignorant_map.size() > 0){
                // reassign iterator to be looking at the first element of the map every time, until that person
                // eventually becomes alarmed and is removed from the ignorant map.
                it = ignorant_map.begin(); 
                alert_test(it->first);
            }
        }
        if(total_count > 0){
            for(int i = 0; i < ignorant_map.size(); i++){
                // reassign iterator to be looking at the beginning of the map since
                // everytime location change returns true, there will be a new "first" person
                // in the map since they will have been sent to the queue.
                it = ignorant_map.begin(); 
                location_change(it->first);
            }
            for(int i = 0; i < alarmed_map.size(); i++){
                //see comment for ignorant map above
                it = alarmed_map.begin(); 
                location_change(it->first);
            }
            for(int i = 0; i < zombie_map.size(); i++){
                //see comment for ignorant map above
                it = zombie_map.begin(); 
                location_change(it->first);
            }
        }

        //REUPDATE OUR COUNTS FOR EACH PERSON TYPE:
        zombie_count = zombie_map.size();
        alarmed_count = alarmed_map.size();
        ignorant_count = ignorant_map.size();
        
    }



