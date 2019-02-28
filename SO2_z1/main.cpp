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

void Run(Philosopher *p)
{
    //mu.lock();
    while(true)
    {
            if(philosophersTab[p->id].isHungry)
            {
                philosophersTab[p->id].isHungry=false;
                p->Eating(&philosophersTab[p->id]);                
            }
            else
            {
                philosophersTab[p->id].isHungry=true;
                p->Philosophizing(&philosophersTab[p->id]);
           } 
    }
    //mu.unlock();
}
void CreatePhilosophers()
{//function create philosophers objects
     for(int i=0;i<numOfPhilosophers;i++)
    {
        philosophersTab[i] =  Philosopher(i,false);//create new philosopher passing id,isPhilosophizing,isEating,isHungry,
    }
}
int main(int argc, char** argv) 
{       
    CreatePhilosophers();
    cout<<"Philosophers created."<<endl;
  
    for(int i=0;i<numOfPhilosophers;i++)
    {
        t[i]=thread(Run,&philosophersTab[i]);
    }
    
     for(int i=0;i<numOfPhilosophers;i++)
    {
        t[i].join();
    }
    return 0;
}