#include "Philosopher.h"
#include <iostream>
#include <random>
#include <thread>
#include <mutex>
mutex mut;
default_random_engine re;
Philosopher::Philosopher()
{

}

Philosopher::Philosopher(int pID,bool pIsHungry) 
{
     id=pID;
     isHungry=pIsHungry;
}
void Philosopher :: Philosophizing(Philosopher *p)
{
    mut.lock();
    cout<<"Philosopher number: "<<p->id<<" is philosophizing."<<endl; 
    mut.unlock();
    auto start= chrono :: high_resolution_clock::now();
    double time=GenerateRandomTime();
    int timeToWait=round(time*1000.0);
    
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
    
    auto stop = chrono:: high_resolution_clock::now();      
    mut.lock();
    cout<< "Philosophizing of philosopher number "<<p->id<<" taken: "<<chrono :: duration_cast<chrono :: milliseconds>(stop-start).count()/1000.0<<"s"<<endl;
   mut.unlock(); 
}
void Philosopher :: Eating(Philosopher *p)
{   
    mut.lock();
    cout<<"Philosopher number: "<<p->id<<" is eating."<<endl; 
    mut.unlock();
    auto start= chrono :: high_resolution_clock::now();
    
    double time=GenerateRandomTime();
    int timeToWait=round(time*1000.0);
    
    this_thread :: sleep_for(chrono :: milliseconds(timeToWait));
    
    auto stop = chrono:: high_resolution_clock::now();      
    mut.lock();
    cout<< "Eating of philosopher number "<<p->id<<" taken: "<<chrono :: duration_cast<chrono :: milliseconds>(stop-start).count()/1000.0<<"s"<<endl;
    mut.unlock();
}
double Philosopher :: GenerateRandomTime()
{//function generates random time in seconds as double value
    uniform_real_distribution<double> unif(3.5,5);    
    double value=unif(re);
    return value;
}
Philosopher::~Philosopher() {
}