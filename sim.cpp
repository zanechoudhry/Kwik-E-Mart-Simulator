//Zane Choudhry
//zchoudhry
//sim.cpp

#include<iostream>
#include<fstream>
#include<string>
#include"cust.h"
#include <cstdlib>
#include"pqueue.h"
using namespace std;

void legal_checker_and_break(char *str1, char *str2){ // function to check if the amount of checkers and the break duraiton are valid integers if they arent then throw an integer so the catch block can print out message to stderr
    int value1;
    int value2;
    value1 = atoi(str1); // convert the str to int
    while(*str1 != 0){
        if(!isdigit(*str1)){ //if the char is not a digit throw integer 1 so it can print out error message to stderr
            throw 1;
            break; // stop the loop since the char isnt a digit
        }
        str1++;
    }
    if (value1 <= 0) {
        throw 1;
    }
    
    value2 = atoi(str2); // convert the str to int
    while(*str2 != 0){
        if(!isdigit(*str2)){ //if the char is not a digit throw integer 2 so it can print out error message to stderr
            throw 2;
            break; // stop the loop since the char isnt a digit
        }
        str2++;
    }
    if (value2 < 0) {
        throw 2;
    }
}

Pqueue open_ifile(char *str, int num){
    if(num != 5){ // if the number of arguments read from the command line then throw the int 3 to print out error message
        throw 3;
    }
    Pqueue arrival_q;
    string buffer;
    string cust_name = " ";
    string cust_type = " ";
    int arrival;
    int items;
    
    ifstream readFile(str, ios::in);
    if (!readFile) {
        throw 4;
    }
    else{
        while (readFile >> cust_name){ // while there is a customer name to read keep reading in from the file
            readFile >> cust_type; // reading in customer type
            readFile >> arrival; // reading in the arrival time of the customer
            readFile >> items; // reading in the amount of items the customer bought
            arrival_q.enqueue (new Cust (cust_name, cust_type, arrival, items), arrival); // once all the variable are read in put the customer onto the arrival queue with arrival time as the priority
        }
    }
    return arrival_q; // return the arrival_q
    readFile.close();
}
struct Checker{ // creating a struct with all the details related to the checkers information
    int register_bank;
    int employee_done;
    Cust *ptr; // pointer to a customer so it can keep trck of who they are serving
};

void run_simulation (Pqueue & arrival_q, int num_checkers, int break_duration, ostream &os){
    Checker *checker_array = (Checker*) malloc(num_checkers * sizeof(Checker)); // allocating checker array
    
    Cust cust; // calling the cust constructor
    
    int num_customers = arrival_q.length(); // to get the num of customers we ask for the size of the arrival q which is how many customers are in the store
    Pqueue shopping_q, checkers_q; // creating a checker and shopping queue
    int time;

    for (int i = 0; i < num_checkers; i++) { // intialize the values in  the checker struct to the starting values
        checker_array[i].register_bank=250; // all register banks are equal to 250 startng the day
        checker_array[i].ptr = NULL; // the checker isnt helping anyone so it is set NULL
        checker_array[i].employee_done = 0; // just to fill the void set the employee done time = 0 since they arent helping anyone
    }
    
    for (int clock = 1; num_customers > 0; clock++){ // outermost for loop to keep track of the clock
        int stolen_amount = 0;
        
        
            while (arrival_q.first_priority() == clock){ // while the first customers arrival time is equal to the clock dequeue them and print out the entered message and then put them onto the shopping queue with the priority of the tie they get done shopping
                Cust *tmp = arrival_q.dequeue(); //top customer is assigned to tmp
                tmp->print_entered(os, clock);
                shopping_q.enqueue (tmp, tmp->get_done_shopping()); // put the customer onto the shopping queue with the priority of the get done shopping time
            }
        
        
        while (shopping_q.first_priority() != -1 && shopping_q.first_priority() == clock){ // while the first customers shopping done time is equal to the clock dequeue them and print out the entered message and then put them onto the checker queue with the priority of 0
            Cust *tmp =shopping_q.dequeue();
            tmp->print_finish_shopping(os, clock); // print out the finished shopping message
            checkers_q.enqueue (tmp, 0); // enqueue then onto the checker q with  0 since the enqueue will put them in the order they are in line
        }
        
        for (int p = 0; p < num_checkers; p++){
            if (checker_array[p].ptr != NULL && checker_array[p].employee_done == clock){ // if the checker is helping someone and the checkers employee done time is equal to the clock then print out the correct output
                stolen_amount = checker_array[p].register_bank;
                if (checker_array[p].ptr->getTypeCust () == "shopper"){
                    checker_array[p].ptr->print_done_checkout(os,clock, p,stolen_amount);
                    checker_array[p].register_bank += (3 * checker_array[p].ptr->getNumberOfItems()); // add to the register the amount the shopper spent
                   
                }
                else{
                    checker_array[p].ptr->print_done_checkout(os,clock, p, stolen_amount);
                    checker_array[p].employee_done = clock + break_duration; // put the employee on break whenever they are robbed
                     checker_array[p].register_bank = 0; // set the register to 0 since the robber stole everything
                }
                delete checker_array[p].ptr;
                checker_array[p].ptr = NULL; // assign the pointer to NULL since they are not serving a customer
                num_customers--; //decrement the number of customers
            }
        }
        
        for (int p = 0; p < num_checkers; p++){
            while(checker_array[p].ptr == NULL && checkers_q.first_priority() != -1 && checker_array[p].employee_done <= clock){ // while the checker isnt helping anyone and the shopping isnt empty anf the employee done time is equal to less than or equal to the clock then assign them to a customer
                    Cust *tmp = checkers_q.dequeue();
                    if(tmp->getTypeCust() == "robber"){
                        tmp->start_checkout(os, clock, p);//print out the start checkout message
                        checker_array[p].ptr = tmp; // assigning the checker to the customer
                        checker_array[p].employee_done = clock + 7; // set the employee done time equal to the done checkout time
                        
                    }
                    else if (tmp->getTypeCust () == "shopper"){
                        tmp->start_checkout(os, clock, p); // call the start checkout message from the cust function
                        checker_array[p].ptr = tmp; // assigning the checker to the customer that is being checked out
                        checker_array[p].employee_done = clock + tmp->getNumberOfItems(); // set the employee done time equal to the done checkout time
                    }
                }
            }
        time = clock;
        }
    for (int k = 0; k < num_checkers; k++) { // print out the register totals
        os << "registers[" << k << "] = $" << checker_array[k].register_bank << endl;
    }
    os << "time = " << time + 1 << endl;
  
    free(checker_array); // deallocate the memory (checker_arrauy) on the heap
}

int main(int argc, char* argv[]){ // try and catch block to see if the command line arguments arent valid
    Pqueue arrival_q;
    ofstream writeFile(argv[4], ios::out); // declare the outputfile
    try{ // see if everything provided in the command line were valid and if they werent then hit the catch block and print out the appropriate message to stderr
    arrival_q = open_ifile(argv[3],argc);
    if (!writeFile){throw 5;}
    legal_checker_and_break(argv[1],argv[2]);
    }catch(int i){ // based on the throw if the correct if statement
        if(i == 3){cerr << "Error: invalid number of command line arguments." << endl;}
        if(i == 4){cerr << "Error: could not open input file <" << argv[3] << ">."<< endl;}
        if(i == 5){cerr << "Error: could not open output file <" << argv[4] << ">."<< endl;}
        if(i == 1){cerr << "Error: invalid number of checkers specified." << endl;}
        if(i == 2){cerr << "Error: invalid checker break duration specified." << endl;}
        return 1; // halt the program if any of the errors are found
    }
    int checkers = atoi(argv[1]), break_duration = atoi(argv[2]);
    run_simulation (arrival_q, checkers, break_duration, writeFile); // calling the run simulation function to start the program
    writeFile.close();
}


