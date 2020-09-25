/* Daniele Pellegrini 285240
 * pasw01101.cpp, ref: Simulazione - Short Time Scheduler
 */
#include <iostream>
#include <vector>
#include "scheduler.h"
#include "process.h"
//include "process.cpp"

using namespace std;

/*Scheduler::Scheduler(int q): quanto(q){}*/

//Costruttore
Scheduler::Scheduler(int a) : quanto(a){
    run = nullptr;
    n_clock = 0;
    counter = 0;
}

//Restituisce il valore di run
Process* Scheduler::getRUN(){
    return run;
}

//Restituisce il valore del numero di clock
int Scheduler::getClock(){
    return n_clock;
}

//Restituisce il valore di quanto
int Scheduler::getQuanto(){
    return quanto;
}

//Restituisce il valore del numero del counter
int Scheduler::getCounter(){
    return counter;
}

//Restituisce il valore di wait
vector<Process*> Scheduler::getWait(){
    return wait;
}

//Restituisce il valore di ready
vector<Process*> Scheduler::getReady(){
    return ready;
}

//Restituisce il valore di completed
vector<Process*> Scheduler::getCompleted(){
    return completed;
}

bool Scheduler::emptyRun() { // Il metodo restituisce il valore "true" se
    if (run == nullptr)     // il puntatore di run è vuoto
        return true;
    else return false;
}

//Visualizza lo stato attuale degli attributi
void Scheduler::printState(){
    cout << "Processo attualmente in esecuzione: ";
    if (run == NULL)
        cout << "None" << endl;
    else cout << run->getPID() << endl;
    cout << "Processi in stato di attesa: ";
    for (Process* i : wait){
        cout << i->getPID();
        if (wait.size() > 1 && i != wait.back())
            cout << ", ";}
    if (wait.empty())
        cout << "None" << endl;
    cout << endl << "Processi in stato di ready: ";
    for (Process* i : ready){
        cout << i->getPID();
        if (ready.size() > 1 && i != ready.back())
            cout << ", ";}
    if (ready.empty())
        cout << "None" << endl;
    cout << endl << "------------" << endl;
}

void Scheduler::executeProcess(){ //Riceve un riferimento a un processo
    run = ready[0];              // che viene posto in stato di run
    ready.erase(ready.begin());
}

void Scheduler::startProcess(Process* p){ //Riceve un riferimento a un processo
    ready.push_back(p);                  // che viene posto in stato di ready
}

void Scheduler::sleepProcess(Process* p){ //Riceve un riferimento a un processo
    wait.push_back(p);                   // che viene posto in stato di attesa
}

//Il metodo elimina un processo dallo stato di wait e lo pone in stato di ready
void Scheduler::awakeProcess(){ //Creo un vector che andrà a contenere i processi che escono
    vector<Process*> ordered;  //dallo stato di wait attraverso un ciclo for al contrario
    int n = wait.size();              //Creo una variabile int n corrispondente all dimensione
    for (int i = n-1; i >= 0; i--){  //della lista wait, che in questo modo viene calcolata una
        Process* p = wait[i];       //sola volta. La variabile viene chiamata nel ciclo, che
        if (p != nullptr){         //scorre al contrario, cambiando così il valore di partenza
            if (p->needAwake()){  //ma non quello finale, per prevenire che due processi che
                p->deleteRes();  //escono nello stesso istante di clock dall'attesa non
                ordered.push_back(p);//interferiscano  l'uno sull'altro
                wait.erase(wait.begin()+i);
            }
        }
    }
    for (int o = ordered.size()-1; (o >= 0); o--){ //Faccio scorrere la lista ordered al
        Process* q = ordered[o]; //contrario, in modo da mettere in stato di ready i processi
        if (q != nullptr)       //in ordine corretto, e alla fine svuoto il vettore.
            startProcess(q);
    }
    ordered.clear();
}

void Scheduler::completeProcess(Process* p){ //Riceve un riferimento a un processo
    completed.push_back(p);                 // che viene messo in una lista che lo definisce completo
}

bool Scheduler::noProcessAlive(){                              //Il metodo restituisce il velore "true"
    if (run == NULL && ready.size() == 0 && wait.size() == 0) // se non ci sono più processi da eseguire
        return false;
    else return true;
}

void Scheduler::waiting(){   //Metodo che gestisce i processi in stato di wait
    for (Process* p : wait){
        if (p != nullptr)
            p->sleeping();
    }
}

void Scheduler::clock(){                         // Avanzamento di un passo -> Gestione del processo in stato di Run
    if (emptyRun()){
        counter = 0;                           // può avanzare, terminare in quanto completato,
        if (ready.empty() == false)
            executeProcess();                //  o essere posto in stato di wait o di ready
    }
    n_clock++;
    counter++;
    if (emptyRun() == false){
        run->progress();
    }
    if (emptyRun() == false && run->needRes() && run->lastRes()){
        completeProcess(run);
        run->finished = n_clock;
        run->~Process();
        run = nullptr;
    }
    if (emptyRun() == false && run->needRes() && run->lastRes() == false){
        sleepProcess(run);
        run = nullptr;
    }
    if (emptyRun() == false && counter == quanto){
        startProcess(run);
        run = nullptr;
    }
    //system("PAUSE"); //Input utente
}

//Visualizza le statistiche relative al tempo di esecuzione di ogni processo
void Scheduler::statistics(){
    cout << "Statisctiche relative al tempo di esecuzione di ogni processo, in ordine di completamento: " <<endl;
    for (Process* p : completed){
        cout << "Processo:  " << p->getPID() << endl;
        cout << "CPU usata: " << p->getCPUused() << endl;
        cout << "Clock al completamento: " << p->finished << endl;
        cout <<"------------" << endl;
    }
}


