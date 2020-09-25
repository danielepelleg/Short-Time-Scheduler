/* Daniele Pellegrini 285240
 * pasw01101.cpp, ref: Simulazione - Short Time Scheduler
 */
#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <iostream>
#include <vector>
#include "process.h"

using namespace std;

class Scheduler
{
public:
    Scheduler(int a);
    //virtual ~Scheduler();
    Process* getRUN();
    int getClock();
    int getQuanto();
    int getCounter();
    vector<Process*> getWait();
    vector<Process*> getReady();
    vector<Process*> getCompleted();
    bool emptyRun();
    void printState();
    void executeProcess();
    void startProcess(Process*);
    void sleepProcess(Process*);
    void awakeProcess();
    void completeProcess(Process*);
    bool noProcessAlive();
    void waiting();
    void clock ();
    void statistics();
private:
    Process* run; //Riferimento al processo in esecuzione
    int n_clock = 0; //Numero di clock
    int quanto = 5; //Quanto di Tempo (numero di cicli di clock)
    int counter = 0; //Contatore che conta i clock di ogni processo
    vector<Process*> wait;  //Lista di riferimenti a processi in stato di attesa per una risorsa
    vector<Process*> ready; //lista di riferimenti a processi in stato di attesa
    vector<Process*> completed; //Definisco un vettore contenente i Processi Completati
};

#endif // SCHEDULER_H
