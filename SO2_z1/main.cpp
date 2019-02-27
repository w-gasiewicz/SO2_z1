#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include "Philosopher.h"
using namespace std;

static const int numOfPhilosophers=5;
mutex mu;
thread t[numOfPhilosophers];
Philosopher philosophersTab[numOfPhilosophers];

int GenerateRandomPhilosopher()
{//function generates random philosopher number    
    int value=rand() % 4+0;
    return value;
}
void Run(Philosopher *p)
{
    mu.lock();
            if(philosophersTab[p->id].isHungry)
            {
                philosophersTab[p->id].isHungry=false;
                //tutaj musi jesc                
                p->Eating(&philosophersTab[p->id]);                
            }
            else
            {
                philosophersTab[p->id].isHungry=true;
                //tutaj filozofuje
                p->Philosophizing(&philosophersTab[p->id]);
           }  
    mu.unlock();
}
void CreatePhilosophers()
{//function create philosophers objects
     for(int i=0;i<numOfPhilosophers;i++)
    {
        philosophersTab[i] =  Philosopher(i,true);//create new philosopher passing id,isPhilosophizing,isEating,isHungry,
    }
}
int main(int argc, char** argv) 
{       
    CreatePhilosophers();
    cout<<"Philosophers created."<<endl;
  
    while(true)
    {
        int index=GenerateRandomPhilosopher();
        t[index]=thread(Run,&philosophersTab[index]);
        t[index].join();
    }
    return 0;
}