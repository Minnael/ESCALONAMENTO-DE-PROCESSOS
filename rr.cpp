#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
   int pid;              // ID DO PROCESSO
   int burst_time;       // TEMPO DE BURST (PICO DE CPU)
   int original_burst_time; // TEMPO DE BURST ORIGINAL
   int completion_time;  // TEMPO DE CONCLUSÃO DO PROCESSO
   int tempo_espera;     // TEMPO DE ESPERA DO PROCESSO
   bool completed;       // INDICA SE O PROCESSO FOI COMPLETADO
};

void RR(vector<Process> &processes, int quantum) {
   int tempo = 0;
   int numero_processos = processes.size();
   int completed_processes = 0;

   while (completed_processes < numero_processos) {
      for (auto &processo : processes) {
         if (!processo.completed) {
            int execution_time = min(quantum, processo.burst_time);

            tempo += execution_time;
            processo.burst_time -= execution_time;

            if (processo.burst_time <= 0) {
               processo.completed = true;
               completed_processes++;
               processo.completion_time = tempo;
               processo.tempo_espera = processo.completion_time - processo.original_burst_time;
            }
         }
      }
   }

   //CONFIGURAÇÕES PARA A FORMATAÇÃO DA TABELA
   const int width_pid = 5;
   const int width_burst_time = 20;
   const int width_completion = 12;
   const int width_waiting_time = 12;
   const int width_status = 8;

   //CABEÇALHOS
   cout << left
      << setw(width_pid) << "PID"
      << setw(width_burst_time) << "BURST-TIME-FINAL"
      << setw(width_completion) << "CONCLUSAO"
      << setw(width_waiting_time) << "ESPERA"
      << setw(width_status) << "STATUS" << endl;

   //LINHA DE SEPARAÇÃO INICIAL
    cout << string(width_pid, '-')
      << string(width_burst_time, '-')
      << string(width_completion, '-')
      << string(width_waiting_time, '-')
      << string(width_status, '-') << endl;

   //DADOS DOS PROCESSOS
   for (const auto &processo : processes) {
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
      process.original_burst_time = process.burst_time; //SALVA O TEMPO ORIGINAL DE BURST

      processes.push_back(process);
   }

   file.close();

   int quantum = 100;
   RR(processes, quantum);

   return 0;
}
