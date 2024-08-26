#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;              // ID DO PROCESSO
    int burst_time;       // TEMPO DE BURST (PICO DE CPU)
    int completion_time;  // TEMPO DE CONCLUSÃO DO PROCESSO
    int waiting_time;     // TEMPO DE ESPERA DO PROCESSO
    int turnaround_time;  // TEMPO DE TURNAROUND (TEMPO TOTAL NO SISTEMA)
    bool completed;       // INDICA SE O PROCESSO FOI COMPLETADO
};

void sjf(vector<Process>& processes, vector<int>& execution_order) {
    int n = processes.size();
    int current_time = 0;
    int completed_processes = 0;
    int avg_time=0;

    while (completed_processes < n) {
        int min_burst_time = INT_MAX;
        int index = -1;
        // ENCONTRAR O PRÓXIMO PROCESSO COM O MENOR BURST TIME E QUE AINDA NÃO FOI COMPLETADO
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].burst_time < min_burst_time) {
                min_burst_time = processes[i].burst_time;
                index = i;
            }
        }

        if (index != -1) {
            // ATUALIZAR TEMPOS PARA O PROCESSO SELECIONADO
            current_time += processes[index].burst_time;
            processes[index].completion_time = current_time;
            processes[index].turnaround_time = processes[index].completion_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
            processes[index].completed = true;
            completed_processes++;
            avg_time=avg_time+current_time;
            // ADICIONAR O PROCESSO À ORDEM DE EXECUÇÃO
            execution_order.push_back(processes[index].pid);
        }
    }
    avg_time=avg_time/n;
    cout<< "TEMPO DE ESPERA MÉDIO: "<< avg_time<< "\n";

}

int main() {
    vector<Process> processes;
    ifstream file("picos_cpu.dat");

    if (!file) {
        cerr << "ERRO AO ABRIR O ARQUIVO." << endl;
        return 1;
    }

    Process process;
    while (file >> process.pid >> process.burst_time) {
        process.completed = false;  // INICIALMENTE, NENHUM PROCESSO FOI COMPLETADO
        processes.push_back(process);
    }

    file.close();

    // VETOR PARA ARMAZENAR A ORDEM DE EXECUÇÃO DOS PROCESSOS
    vector<int> execution_order;

    // EXECUTA O ESCALONAMENTO SJF
    sjf(processes, execution_order);

    // EXIBE A ORDEM DE EXECUÇÃO
    cout << "ORDEM DE EXECUÇÃO DOS PROCESSOS: ";
    for (int pid : execution_order) {
        cout << pid << " ";
    }
    cout << endl;

    // EXIBE OS RESULTADOS DETALHADOS
    cout << "PID\tPICO_ DE_CPU\tWAITING\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" 
             << process.burst_time << "  \t" 
             << process.waiting_time << "\n";
    }
    return 0;
}
