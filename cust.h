//Zane Choudhry
//zchoudhry
//cust.h
#ifndef CUST_H
#define CUST_H
#include <string>
using namespace std;
class Cust{
public:
    Cust();
    Cust(string name,string typecust, int arrivaltime, int numberofitems); //cust constructor
    string getName(); // return the name of the customer
    int getArrivalTime(); // return the arrival time
    int getNumberOfItems(); // return the number of items
    string getTypeCust(); // returns type of customer (shopper or robber)
    void print_entered(ostream &os, int clock); // print entered store
    void print_finish_shopping(ostream &os, int clock);// print done shopping
    void start_checkout(ostream &os, int clock, int checkernum); // print start checkout
    void print_done_checkout(ostream &os, int clock, int checkernum, int stolen_amount); // print done checkout stolen_amount);
    int get_done_shopping(); //returns done shopping time
    
private:
    string m_name;
    string m_typecust;
    int m_arrivaltime;
    int m_numberofitems;
};
#endif

