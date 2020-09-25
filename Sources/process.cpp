/* Daniele Pellegrini 285240
 * pasw01101.cpp, ref: Simulazione - Short Time Scheduler
 */
#include <iostream>
#include "process.h"

using namespace std;

//Costruttore
Process::Process(int a, int b): PID(a), totCPUtime(b) {
    CPUused = 0;
}

//Aggiungi Risorse a resNeed
void Process::addResource(Resource r){
    resNeed.push_back(r);
}

vector<Resource> Process::getResource(){
    return resNeed;
}

int Process::getPID() const{
    return PID;
}

int Process::getTotCPUtime(){
    return totCPUtime;
}

int Process::getCPUused(){
    return CPUused;
}

int Process::expectedTime(){   //Restituisce il tempo di esecuzione previsto del processo
    int a = 0;                // Tempo = Numero disponibilita risorse + Tempo totale CPU
    for (Resource r : resNeed)
        a += r.disponibilita;
    return totCPUtime + a;
}

bool Process::lastRes(){      //Il metodo restituisce il valore "true" se il processo
    if (resNeed.size() == 1) // ha una sola risorsa all'interno di resNeed
        return true;
    else return false;
}

bool Process::needRes(){             // Il metodo restituisce il valore "true"
    if (resNeed.front().ciclo == 0) // se il processo necessita di una risorsa
        return true;
    else return false;
}

bool Process::needAwake(){                   // Il metodo restituisce il valore "true"
    if (resNeed.front().disponibilita == 0) // se il processo ha bisogno di uscire dallo
        return true;                       // stato di attesa
    else return false;
}

void Process::deleteRes(){           //Metodo per eliminare una risorsa
    resNeed.erase(resNeed.begin()); // all'interno di resNeed
}

void Process::sleeping(){              //Metodo che decrementa la disponibilità di una risorsa
    resNeed.front().disponibilita --; // di un processo in stato di wait
}

void Process::progress(){ // Progresso attivato ad ogni passo
    CPUused ++;          // di esecuzione
    resNeed.front().ciclo --;
}

//Visualizza il processo creato
void Process::showProcess() {
    cout << "PID: " << PID << endl;
    for (auto r: resNeed){
        cout << "(" << r.ciclo << "," << r.disponibilita << ") ";
    }
    cout << endl << "CPU Time: "
         << totCPUtime << endl;
    cout << "------------" << endl;
}

//Distruttore
Process::~Process(){
    delete &PID;
    delete &totCPUtime;
    delete &CPUused;
    delete &resNeed;
}
