# 💻 Estudos de Sistemas Operacionais

Repositório dedicado às implementações e testes práticos desenvolvidos durante as práticas de Ciência da Computação na Estácio. O objetivo é demonstrar conceitos fundamentais do núcleo de sistemas operacionais utilizando a linguagem C e scripts Shell em ambiente Linux (Ubuntu 22.04 LTS).

## 📚 Tópicos Abordados

*   **Escalonamento e Prioridade de CPU:** Execução de processos concorrentes em segundo plano (background) e manipulação da prioridade de alocação do processador pelo sistema operacional utilizando o utilitário `nice`. O teste de estresse da CPU é feito através do cálculo pesado de $\pi$ utilizando a Fórmula de Leibniz $$\pi = 4 \sum_{k=0}^{\infty} \frac{(-1)^k}{2k+1}$$.
*   **Gerência de Processos e Threads:** Criação de fluxos de execução concorrentes utilizando a chamada de sistema `clone()` e sincronização de encerramento com `waitpid()`.
*   **Condição de Corrida (Race Condition):** Simulação de inconsistência de dados gerada quando múltiplas threads acessam e modificam variáveis globais simultaneamente sem o devido controle.
*   **Sincronização com Semáforos (Mutex):** Resolução da condição de corrida através do bloqueio de região crítica utilizando a biblioteca padrão `<semaphore.h>`.
*   **Tratamento de Sinais (Signal Handling):** Interceptação e customização de respostas a eventos assíncronos (`SIGINT`, `SIGTERM`) utilizando a chamada `signal()`.

## 🛠️ Tecnologias e Ferramentas

*   Linguagens: **C** e **Shell Script**
*   Ambiente: **Linux / Ubuntu VM**
*   Compilador: **GCC**

## 🚀 Como Compilar e Executar

Clone este repositório para a sua máquina local:
```bash
git clone [https://github.com/ricardovalehrio/estudos-sistemas-operacionais.git](https://github.com/ricardovalehrio/estudos-sistemas-operacionais.git)
cd estudos-sistemas-operacionais
