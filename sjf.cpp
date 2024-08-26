#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;              // ID do processo
    int burst_time;       // Tempo de burst (pico de CPU)
    int completion_time;  // Tempo de conclusão do processo
    int waiting_time;     // Tempo de espera do processo
    int turnaround_time;  // Tempo de turnaround (tempo total no sistema)
    bool completed;       // Indica se o processo foi completado
};

void sjf(vector<Process>& processes, vector<int>& execution_order) {
    int n = processes.size();
    int current_time = 0;
    int completed_processes = 0;
    int avg_time=0;

    while (completed_processes < n) {
        int min_burst_time = INT_MAX;
        int index = -1;
        // Encontrar o próximo processo com o menor burst time e que ainda não foi completado
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                index = i;
            }
        }

        if (index != -1) {
            // Atualizar tempos para o processo selecionado
            current_time += processes[index].burst_time;
            processes[index].completion_time = current_time;
            processes[index].turnaround_time = processes[index].completion_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
            processes[index].completed = true;
            completed_processes++;
            avg_time=avg_time+current_time;
            // Adicionar o processo à ordem de execução
            execution_order.push_back(processes[index].pid);
        }
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
    while (file >> process.pid >> process.burst_time) {
        process.completed = false;  // Inicialmente, nenhum processo foi completado
        processes.push_back(process);
    }

    file.close();

    // Vetor para armazenar a ordem de execução dos processos
    vector<int> execution_order;

    // Executa o escalonamento SJF
    sjf(processes, execution_order);

    // Exibe a ordem de execução
    cout << "Ordem de Execução dos Processos: ";
    for (int pid : execution_order) {
        cout << pid << " ";
    }
    cout << endl;

    // Exibe os resultados detalhados
    cout << "PID\tPico_ de_cpu\tWaiting\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" 
             << process.burst_time << "  \t" 
             << process.waiting_time << "\n";
    }
    return 0;
}
