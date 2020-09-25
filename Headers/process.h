/* Daniele Pellegrini 285240
 * pasw01101.cpp, ref: Simulazione - Short Time Scheduler
 */
#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <iostream>

using namespace std;

struct Resource{
    int ciclo; //Dopo n cicli il processo necessita di una risorsa
    int disponibilita; //che sarà disponibile dopo m disponibilità
};

class Process
{
public:
    Process(int a, int b);
    ~Process();
    void addResource(Resource c);
    int getPID() const;
    int getTotCPUtime();
    int getCPUused();
    int expectedTime();
    vector<Resource> getResource();
    bool needRes();
    bool needAwake();
    bool lastRes();
    void deleteRes();
    void progress();
    void sleeping();
    void showProcess() ;
    int finished; //Numero che tiene in memoria l'istante di clock al completamento (variabile pubblica)
private:
    int PID; //Process Identifier
    int totCPUtime; //Numero di passi di esecuzione per portare a termine il processo
    int CPUused = 0; //Numero di passi già eseguiti
    vector<Resource> resNeed; //Vettore contenente le Risorse
};

#endif // PROCESS_H
