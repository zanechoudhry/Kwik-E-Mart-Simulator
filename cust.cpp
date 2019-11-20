//Zane Choudhry
//zchoudhry
//cust.cpp
#include<iostream>
#include "cust.h"
#include <string>
#include<assert.h>
using namespace std;

Cust::Cust(){
    m_name = " ";
    m_typecust = " ";
    m_arrivaltime = 0;
    m_numberofitems = 0;
}

Cust::Cust(string name, string typecust, int arrivaltime, int numberofitems){ // assigning each variable
    m_name = name;
    m_typecust=typecust;
    m_arrivaltime =arrivaltime;
    m_numberofitems = numberofitems;
}
string Cust::getTypeCust(){
    return m_typecust;
}
int Cust::getNumberOfItems(){
    return m_numberofitems;
}
int Cust::getArrivalTime(){
    return m_arrivaltime;
}
int Cust::get_done_shopping(){ // calculating the done shopping time
    m_arrivaltime = m_arrivaltime + (m_numberofitems * 2);
    return m_arrivaltime;
}
void Cust::print_entered(ostream &os, int clock) { // no matter the type of customer the entered store message will be the same
   assert(clock == m_arrivaltime); //to make sure everthing is correct and logic error
    os << clock << ": " << m_name << " entered store" << endl;
}
void Cust::print_finish_shopping(ostream &os, int clock){ // no matter the type of customer the done shopping message will be the same
    assert(clock == m_arrivaltime); //to make sure everthing is correct and logic error
    os << clock << ": " << m_name << " done shopping" << endl;
}
void Cust::print_done_checkout(ostream &os, int clock, int checkernum, int stolen_amount){ // print the done checkut message based on the type of cust
    if (m_typecust == "robber") {
        if (m_numberofitems <= 1) {
            os << clock << ": " << m_name << " stole " << "$" << stolen_amount << " and " << m_numberofitems << " item from checker " << checkernum << endl; // printing out the speciified output file
        }
        else{
            os << clock << ": " << m_name << " stole " << "$" << stolen_amount << " and " << m_numberofitems << " items from checker " << checkernum << endl; // printing out the speciified output file
        }
    }
    if(m_typecust == "shopper"){
        if(m_numberofitems <= 1){
            os << clock << ": " << m_name << " paid " << "$" << 3 * m_numberofitems << " for " << m_numberofitems << " item to checker " << checkernum  << endl; // printing out the speciified output file
        }
        else{
            os << clock << ": " << m_name << " paid " << "$" << 3 * m_numberofitems << " for " << m_numberofitems << " items to checker " << checkernum << endl; // printing out the speciified output file
            
        }
    }
}
void Cust::start_checkout(ostream &os, int clock, int checkernum){ // no matter the type of customer the start checkout message will be the same
    os << clock << ": " << m_name << " started checkout" << " with checker " << checkernum << endl;
}



