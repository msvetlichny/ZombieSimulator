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
#ifndef PERSON_H
#define PERSON_H

// There isn't a whole lot to this class. By the specifications 
// it doesn't appear there is a good reason to have a polymorphic person class.
class Person{

    private:
    
        //class that assigns 0 for "Person", 1 for "Ignorant", 2 for "Alarmed", and 3 for "Zombie"
        int idNum; 

    public:

        //default constructor
        Person(int id){
            idNum = id;
        }
        //getter method for idNum
        int get_id(){
            return idNum;
        }
        //setter method for idNum
        void set_id(int n){
            idNum = n;
        }

        //Prof. Matt assisted in this:
        bool operator<(const Person p) const {
            return this->idNum < p.idNum;
        }
};



#endif