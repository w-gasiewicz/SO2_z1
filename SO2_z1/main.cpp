#include <iostream>
#include <thread>
#include <random>
#include <cstdio>
#include "Philosopher.h"
using namespace std;

static const int numOfPhilosophers=5;
thread t[numOfPhilosophers];
Philosopher philosophersTab[numOfPhilosophers];
bool running=true;
void Run(Philosopher *p)
{
    while(running)
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
    
    int inputChar;
    while(true)
    {
        inputChar=cin.get();
        if(inputChar!=27)//while user dont press esc button
        {
            cout<<"To stop program press ESC button!"<<endl;
        }
        else 
        {
            running=false;
            break;
        }
    }
    
      for(int i=0;i<numOfPhilosophers;i++)
    {
        t[i].join();
    }
    return 0;
}