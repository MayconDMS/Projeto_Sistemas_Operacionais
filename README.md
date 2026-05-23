# 🖥️ Simulador de Sistema Operacional em C

Este projeto é um simulador educacional de um sistema operacional desenvolvido em C, com foco em processos, escalonamento de CPU, gerenciamento de memória e sincronização. O sistema funciona como um Shell interativo em terminal, permitindo ao usuário criar e manipular processos em tempo real.

O objetivo é reproduzir conceitos reais de sistemas operacionais de forma prática, incluindo PCB, memória limitada, escalonamento Round Robin e controle de concorrência.

## ⚙️ Principais características

- Simulação de processos via PCB (Process Control Block)
- Memória RAM limitada usando array estático
- Shell interativo com comandos de sistema
- Escalonamento de CPU com algoritmo Round Robin
- Controle de estados de processo (PRONTO, EXECUTANDO, BLOQUEADO, TERMINADO)
- Comandos para criação, listagem e remoção de processos
- Simulação de sincronização com semáforos/mutex
- Demonstração de deadlock

## 💻 Comandos disponíveis

- `spawn <nome>` → cria um novo processo
- `ps` → lista processos ativos
- `kill <pid>` → finaliza um processo
- `cpu` → executa um ciclo do escalonador
- `lock <pid>` → bloqueia recurso
- `unlock <pid>` → libera recurso
- `exit` → encerra o sistema

## 🧠 Conceitos aplicados

- Gerenciamento de processos
- Escalonamento de CPU (Round Robin)
- Estruturas de dados em C
- Simulação de memória RAM
- Sincronização e concorrência
- Deadlocks e controle de recursos

## 🎯 Objetivo

O projeto tem como finalidade reforçar conceitos fundamentais de sistemas operacionais através de uma simulação prática, aproximando teoria e implementação de baixo nível em C.
