#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;              // ID do processo
    int burst_time;       // Tempo de burst (pico de CPU)
    int completion_time;  // Tempo de conclusão do processo
    int waiting_time;     // Tempo de espera do processo
    int turnaround_time;  // Tempo de turnaround (tempo total no sistema)
};

void fcfs(vector<Process>& processes) {
    int current_time = 0;
    int n=processes.size();
    int avg_time=0;
    for (auto& process : processes) {
        process.completion_time = current_time + process.burst_time;
        process.turnaround_time = process.completion_time;
        process.waiting_time = process.turnaround_time - process.burst_time;

        current_time += process.burst_time;
        avg_time+=current_time;
    }
    avg_time=avg_time/n;
    cout<< "Tempo de espera médio: "<< avg_time<< "\n";
}

int main() {
    vector<Process> processes;
    ifstream file("picos_cpu.dat");

    if (!file) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    Process process;
    int arrival_time = 0; 

    while (file >> process.pid >> process.burst_time) {
        processes.push_back(process);
    }

    file.close();

    // Não há necessidade de ordenar os processos, já que eles são executados na ordem que chegam (FIFO).

    fcfs(processes);

    cout << "PID\ tBurst\ tWaiting\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" 
             << process.burst_time << "\t"               
             << process.waiting_time << "\n";
    }

    return 0;
}
