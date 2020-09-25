/* Daniele Pellegrini 285240
 * pasw01101.cpp, ref: Simulazione - Short Time Scheduler
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include "process.h"
#include "scheduler.h"

using namespace std;

int main(){
    vector<Process*> process;
    int t, q;
    cout << "Inserire il Quanto di Tempo: ";
    cin >> q; cout << endl;

    //Creazione di 6 Processi
    Process p1{01, 19}, p2{02, 23}, p3{03,16}, p4{04,18}, p5{05,24}, p6{06,19};

    //Creazione di 3 risorse per ciascun processo e aggiunte ai relativi attributi resNeed
    Resource r1; r1.ciclo = 8; r1.disponibilita = 30;
    Resource s1; s1.ciclo = 5; s1.disponibilita = 25;
    Resource t1; t1.ciclo = 6; t1.disponibilita = 30;
    Resource r2; r2.ciclo = 7; r2.disponibilita = 26;
    Resource s2; s2.ciclo = 8; s2.disponibilita = 24;
    Resource t2; t2.ciclo = 8; t2.disponibilita = 28;
    Resource r3; r3.ciclo = 3; r3.disponibilita = 18;
    Resource s3; s3.ciclo = 5; s3.disponibilita = 22;
    Resource t3; t3.ciclo = 8; t3.disponibilita = 25;
    Resource r4; r4.ciclo = 7; r4.disponibilita = 21;
    Resource s4; s4.ciclo = 5; s4.disponibilita = 24;
    Resource t4; t4.ciclo = 6; t4.disponibilita = 20;
    Resource r5; r5.ciclo = 9; r5.disponibilita = 28;
    Resource s5; s5.ciclo = 7; s5.disponibilita = 21;
    Resource t5; t5.ciclo = 8; t5.disponibilita = 25;
    Resource r6; r6.ciclo = 6; r6.disponibilita = 21;
    Resource s6; s6.ciclo = 7; s6.disponibilita = 24;
    Resource t6; t6.ciclo = 6; t6.disponibilita = 20;
    p1.addResource(r1);
    p1.addResource(s1);
    p1.addResource(t1);
    p2.addResource(r2);
    p2.addResource(s2);
    p2.addResource(t2);
    p3.addResource(r3);
    p3.addResource(s3);
    p3.addResource(t3);
    p4.addResource(r4);
    p4.addResource(s4);
    p4.addResource(t4);
    p5.addResource(r5);
    p5.addResource(s5);
    p5.addResource(t5);
    p6.addResource(r6);
    p6.addResource(s6);
    p6.addResource(t6);

    //Inserimento dei Processi in una Lista
    process.push_back(&p1);
    process.push_back(&p2);
    process.push_back(&p3);
    process.push_back(&p4);
    process.push_back(&p5);
    process.push_back(&p6);

    //Visualizzazione di ogni Processo
    for (Process* i : process){
        i->showProcess();
        t = i->expectedTime();
    }
    cout << "Sono stati creati 6 Processi. " << endl;
    cout << "Premere un tasto per iniziare la Simulazione dello Scheduler: " << endl;
    system("PAUSE");
    cout << "------------------------" << endl;

    //Creazione Scheduler e relativa esecuzione
    Scheduler s{q};
    for (Process* p : process)
        s.startProcess(p);
    do{
        s.clock();
        s.awakeProcess();
        s.waiting();
        cout << "Numero di Clock: " << s.getClock() << endl;
        cout << "Counter: " << s.getCounter() << endl;
        s.printState();
    }while (s.noProcessAlive());

    //Statistiche relative al tempo di Esecuzione:
    cout << "------------------------" << endl;
    cout << "Statistiche: (tempo indicato in clock)" << endl;
    cout << "Tempo previsto:  " << t << " clock" << endl;
    cout << "Tempo impiegato: " << s.getClock() << "  clock" << endl;
    cout << "------------------------" << endl;
    s.statistics();
    system("PAUSE");
}
