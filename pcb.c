#define MAX_PROCESSOS 10 //10 slots
#define MEMORIA_TOTAL 1024 //1GB

#include "pcb.h"
#include <stdio.h>

PCB tabela_processos[MAX_PROCESSOS];
int memoria_utilizada = 0; 
int proximo_pid = 1;

int encontrar_slot_livre() {
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].ativo == 0) {
            return i;
            }
    }
    return -1;
}
void inicializar_sistema() {
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        tabela_processos[i].ativo = 0;
        tabela_processos[i].PID = 0;
        tabela_processos[i].ciclos_restantes = 0;
        tabela_processos[i].estado = Executado;
    }
}

// COMANDO SPAWN 
void comando_spawn(int tamanho_memoria, int ciclos) {
    // 1. Verificar Erro OOM (Out of Memory)
    if (memoria_utilizada + tamanho_memoria > MEMORIA_TOTAL) {
        printf("ERRO: Out of Memory (OOM)! Nao ha memoria suficiente para criar o processo.\n");
        return;
    }

    // 2. Procurar um slot livre na tabela de processos
    int slot = encontrar_slot_livre();
    if (slot == -1) {
        printf("ERRO: Tabela de processos cheia! Limite de %d processos atingido.\n", MAX_PROCESSOS);
        return;
    }

    // 3. Preencher dados do PCB e Inserir o processo na RAM
    tabela_processos[slot].PID = proximo_pid++;
    tabela_processos[slot].ativo = 1;                  // Ocupa o slot
    tabela_processos[slot].ciclos_restantes = ciclos;
    tabela_processos[slot].estado = Pronto;            // Estado inicial como PRONTO
    
    // Simula a alocação somando a memória gasta
    memoria_utilizada += tamanho_memoria; 

    // 4. Feedback visual no terminal
    printf("[SPAWN] Sucesso: Processo PID %d criado no slot %d (%d ciclos, %d MB).\n", 
           tabela_processos[slot].PID, slot, ciclos, tamanho_memoria);
    printf("[RAM] Memoria utilizada: %d/%d MB\n", memoria_utilizada, MEMORIA_TOTAL);
}