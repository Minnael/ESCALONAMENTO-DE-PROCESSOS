#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
   int pid;              // ID DO PROCESSO
   int burst_time;       // TEMPO DE BURST (PICO DE CPUT)

   int completion_time;  // TEMPO DE CONCLUSÃO DO PROCESSO
   int tempo_espera;     // TEMPO DE ESPERA DO PROCESSO
   bool completed;       // INDICA SE O PROCESSO FOI COMPLETADO
};

void RR(vector<Process> & processes, int quantum) {
   int tempo = 0; 
   int numero_processos = processes.size();
   int completed_processes = 0;

   while (completed_processes < numero_processos){
      for (auto& processo : processes) {
         if (!processo.completed == true) {
            int execution_time = min(quantum, processo.burst_time);

            tempo += execution_time;
            processo.burst_time -= execution_time;

            //cout << "PID: " << processo.pid << " ANTES: " << processo.burst_time << " DEPOIS: " << processo.burst_time - quantum << endl;

            if (processo.burst_time < quantum){
               processo.burst_time = processo.burst_time - processo.burst_time;
               processo.completion_time = processo.completion_time + processo.burst_time;
            }
            else {
               processo.burst_time = processo.burst_time - quantum;
               processo.completion_time = processo.completion_time + quantum;
            }

            

            if (processo.burst_time <= 0){
               processo.completed = true;
               completed_processes++;
               processo.completion_time = tempo;
               processo.tempo_espera = processo.completion_time - (processo.burst_time + execution_time);
            }
         }  
      }
   }
   
    // Configurações de formatação para a tabela
    const int width_pid = 5;
    const int width_burst_time = 12;
    const int width_completion = 12;
    const int width_waiting_time = 12;
    const int width_status = 8;

    // Cabeçalhos
    cout << left
         << setw(width_pid) << "PID"
         << setw(width_burst_time) << "BURST-TIME"
         << setw(width_completion) << "CONCLUSAO"
         << setw(width_waiting_time) << "ESPERA"
         << setw(width_status) << "STATUS" << endl;

    // Linha de separação
    cout << string(width_pid, '-') 
         << string(width_burst_time, '-') 
         << string(width_completion, '-') 
         << string(width_waiting_time, '-') 
         << string(width_status, '-') << endl;

    // Dados dos processos
    for (const auto& processo : processes) {
        cout << setw(width_pid) << processo.pid
             << setw(width_burst_time) << processo.burst_time
             << setw(width_completion) << processo.completion_time
             << setw(width_waiting_time) << processo.tempo_espera
             << setw(width_status) << (processo.completed ? "COMPLETO" : "PENDENTE") << endl;
    }
} 

int main() {
   vector<Process> processes;
   ifstream file("picos_cpu.dat");

   Process process;

   while (file >> process.pid >> process.burst_time) {
      process.completed = false;
      process.completion_time = 0;
      process.tempo_espera = 0;

      processes.push_back(process);
   }

   file.close();
    
   int quantum = 10;
   RR(processes, quantum);

   return 0;
}