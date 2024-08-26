#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;              // ID DO PROCESSO
    int burst_time;       // TEMPO DE BURST (PICO DE CPU)
    int completion_time;  // TEMPO DE CONCLUSÃO DO PROCESSO
    int waiting_time;     // TEMPO DE ESPERA DO PROCESSO
    int turnaround_time;  // TEMPO DE TURNAROUND (TEMPO TOTAL NO SISTEMA)
};

void fcfs(vector<Process>& processes) {
    int current_time = 0;  // TEMPO ATUAL NO SISTEMA
    int n = processes.size();  // NÚMERO DE PROCESSOS
    int avg_time = 0;  // ACUMULADOR PARA O TEMPO MÉDIO

    // ITERA SOBRE CADA PROCESSO
    for (auto& process : processes) {
        process.completion_time = current_time + process.burst_time;  // CALCULA O TEMPO DE CONCLUSÃO
        process.turnaround_time = process.completion_time;  // CALCULA O TEMPO DE TURNAROUND
        process.waiting_time = process.turnaround_time - process.burst_time;  // CALCULA O TEMPO DE ESPERA

        current_time += process.burst_time;  // ATUALIZA O TEMPO ATUAL
        avg_time += current_time;  // ACUMULA O TEMPO TOTAL
    }
    avg_time = avg_time / n;  // CALCULA O TEMPO MÉDIO DE ESPERA
    cout << "TEMPO DE ESPERA MEDIO: " << avg_time << "\n";
}

int main() {
    vector<Process> processes;
    ifstream file("picos_cpu.dat");

    if (!file) {
        cerr << "ERRO AO ABRIR O ARQUIVO." << endl;  // MENSAGEM DE ERRO SE O ARQUIVO NÃO FOR ABERTO
        return 1;
    }

    Process process;

    // LEITURA DOS DADOS DOS PROCESSOS DO ARQUIVO
    while (file >> process.pid >> process.burst_time) {
        processes.push_back(process);  // ADICIONA CADA PROCESSO AO VETOR
    }

    file.close();

    // NÃO HÁ NECESSIDADE DE ORDENAR OS PROCESSOS, JÁ QUE ELES SÃO EXECUTADOS NA ORDEM QUE CHEGAM (FIFO).

    fcfs(processes);  // CHAMA A FUNÇÃO PARA EXECUTAR O ALGORITMO FCFS

    cout << "PID\tBurst\tWaiting\n";
    // EXIBE OS RESULTADOS DETALHADOS
    for (const auto& process : processes) {
        cout << process.pid << "\t" 
             << process.burst_time << "\t"               
             << process.waiting_time << "\n";
    }

    return 0;
}
