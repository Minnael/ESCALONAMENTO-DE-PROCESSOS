<div align="center">


# <strong>PROCESS SCHEDULING</strong></br>
</br>
<strong>TRABALHO DA DISCIPLINA DE SISTEMAS OPERACIONAIS (DCA0108)</br></strong>
GABRIEL GONZAGA DE LUNA FREIRE</br>
IAN ANTONIO FONSECA ARAÚJO</br>
JULIA ALANNE SILVINO DOS SANTOS</br>
MATHEUS ERICK BARROS COSTA DIAS DA SILVA</br>
MINNAEL CAMPELO DE OLIVEIRA </br>
</div>



## 1. PROBLEMÁTICA
<div style="text-align: justify;">
O escalonamento de processos em sistemas operacionais desempenha um papel crucial no gerenciamento eficiente dos recursos de computação, especialmente no contexto das CPUs modernas. Trata-se de um mecanismo fundamental que permite a execução concorrente de múltiplos processos, maximizando o uso da CPU e assegurando que os recursos do sistema sejam alocados de maneira eficaz. O escalonamento é responsável por determinar a ordem e a prioridade com que os processos são atendidos, influenciando diretamente o desempenho geral do sistema.</br></br>
Os algoritmos de escalonamento, desenvolvidos ao longo dos anos, têm como objetivo otimizar diferentes aspectos do desempenho, como o tempo de resposta, a utilização da CPU, e a equidade entre os processos. Tradicionalmente, existem três abordagens principais que guiam o escalonamento de processos. A primeira é o escalonamento baseado na ordem de chegada, onde o processo que primeiro entra na fila de prontos é o primeiro a ser executado, seguindo o princípio FIFO (First In, First Out). A segunda abordagem prioriza os processos com menor tempo de execução estimado, favorecendo aqueles com menores picos de uso de CPU, o que pode minimizar o tempo médio de espera. Por fim, a terceira abordagem, conhecida como escalonamento circular ou Round Robin, implementa uma estratégia de time-sharing, onde cada processo recebe um pequeno intervalo de tempo, ou quantum, para ser executado, antes de ceder a CPU ao próximo processo na fila.
</br></br> 

<strong>FCFS (First Came, First Served):</strong> Nesse algoritmo, os processos são executados na ordem em que chegam à fila de prontos. O processo que chega primeiro é o primeiro a ser atendido, e assim por diante. Não há preempção, ou seja, um processo em execução continua até ser concluído antes que o próximo possa começar.</br></br>
<strong>SJF (Shortest Job First):</strong> O SJF seleciona o processo com o menor tempo de execução estimado para ser executado primeiro. Esse algoritmo pode ser preemptivo ou não preemptivo. No caso não preemptivo, uma vez iniciado, o processo é executado até o fim. No caso preemptivo, um novo processo com menor tempo de execução pode interromper o processo em andamento.</br></br>
<strong>RR (Round Robin):</strong> No RR, cada processo recebe um tempo fixo (chamado de quantum) para ser executado, que, nestes casos, são de 10 e 100 unidades de tempo. Se o processo não for concluído dentro desse tempo, ele é colocado de volta no final da fila, e o próximo processo na fila é executado. Essa abordagem garante que todos os processos recebam atenção regular, promovendo uma melhor distribuição do tempo de CPU.</br></br>

## 2. UTILIZAÇÃO DOS CÓDIGOS
<strong>FCFS:</strong> Para a utilização do seguinte código é de necessidade utilizar as bibliotecas definidas abaixo:</br> - iostream </br> - fstream </br> - vector </br> - algorithm

<strong>SJF:</strong> Para a utilização do seguinte código é de necessidade utilizar as bibliotecas definidas abaixo: </br> - iostream </br> - fstream </br> - vector </br> - algorithm </br> - climits

<strong>RR:</strong> Para a utilização do seguinte código é de necessidade utilizar as bibliotecas definidas abaixo:</br> - iostream </br> - fstream </br> - vector </br> - iomanip



