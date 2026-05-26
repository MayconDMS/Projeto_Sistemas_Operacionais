#define MAX_PROCESSOS 10 
#define MEMORIA_TOTAL 1024 

#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

PCB tabela_processos[MAX_PROCESSOS];
int memoria_utilizada = 0; 
int proximo_pid = 1;
int ultimo_slot_executado = -1;

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

void comando_spawn(char *nome, int tamanho_memoria, int ciclos) { 
    if (memoria_utilizada + tamanho_memoria > MEMORIA_TOTAL) {
        printf("ERRO: Out of Memory (OOM)! Nao ha memoria suficiente para criar o processo.\n");
        return;
    }

    int slot = encontrar_slot_livre();
    if (slot == -1) {
        printf("ERRO: Tabela de processos cheia! Limite de %d processos atingido.\n", MAX_PROCESSOS);
        return;
    }

    tabela_processos[slot].PID = proximo_pid++;
    tabela_processos[slot].ativo = 1;                  
    strcpy(tabela_processos[slot].nome, nome);
    tabela_processos[slot].memoria_alocada = tamanho_memoria;
    tabela_processos[slot].ciclos_restantes = ciclos;
    tabela_processos[slot].estado = Pronto;            
    
    memoria_utilizada += tamanho_memoria; 

    printf("[SPAWN] Sucesso: Processo '%s' (PID %d) criado no slot %d (%d ciclos, %d MB).\n", 
           tabela_processos[slot].nome, tabela_processos[slot].PID, slot, ciclos, tamanho_memoria);
    printf("[RAM] Memoria utilizada: %d/%d MB\n", memoria_utilizada, MEMORIA_TOTAL);
}

void comando_ps() {
    printf("\n=== TABELA DE PROCESSOS (ps) ===\n");
    printf("%-5s %-15s %-12s %-15s\n", "PID", "NOME", "ESTADO", "CICLOS REST.");
    printf("-----------------------------------------------------\n");

    int total_processos = 0;

    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].ativo == 1) {
            total_processos++;
            
            char str_estado[15];
            switch (tabela_processos[i].estado) {
                case Pronto:     strcpy(str_estado, "PRONTO"); break;
                case Executando: strcpy(str_estado, "EXECUTANDO"); break;
                case Bloqueado:  strcpy(str_estado, "BLOQUEADO"); break;
                case Executado:  strcpy(str_estado, "EXECUTADO"); break;
            }

            printf("%-5d %-15s %-12s %-15d\n", 
                   tabela_processos[i].PID, 
                   tabela_processos[i].nome, 
                   str_estado, 
                   tabela_processos[i].ciclos_restantes);
        }
    }

    if (total_processos == 0) {
        printf("Nenhum processo em execucao no momento.\n");
    }
    printf("-----------------------------------------------------\n\n");
}

void comando_kill(int pid) {
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].ativo == 1 && tabela_processos[i].PID == pid) {
            char nome_removido[20];
            strcpy(nome_removido, tabela_processos[i].nome);
            int memoria_liberada = tabela_processos[i].memoria_alocada;

            tabela_processos[i].ativo = 0; 
            memoria_utilizada -= memoria_liberada;

            printf("[KILL] Processo '%s' (PID %d) encerrado com sucesso.\n", nome_removido, pid);
            printf("[RAM] Memoria liberada: %d MB. Uso atual: %d/%d MB\n", memoria_liberada, memoria_utilizada, MEMORIA_TOTAL);
            return;
        }
    }

    printf("ERRO: Processo com PID %d nao encontrado.\n", pid);
}

void rodar_escalonador_rr() {
    int slot_atual = -1;

    for (int i = 1; i <= MAX_PROCESSOS; i++) {
        int inspecionar_slot = (ultimo_slot_executado + i) % MAX_PROCESSOS;
        
        if (tabela_processos[inspecionar_slot].ativo == 1 && tabela_processos[inspecionar_slot].estado == Pronto) {
            slot_atual = inspecionar_slot;
            break;
        }
    }

    if (slot_atual == -1) {
        printf("[CPU] Nenhum processo no estado PRONTO para executar.\n");
        return;
    }

    ultimo_slot_executado = slot_atual;
    PCB *proc = &tabela_processos[slot_atual];

    proc->estado = Executando;
    printf("[CPU] Executando processo '%s' (PID %d). Ciclos restantes: %d\n", proc->nome, proc->PID, proc->ciclos_restantes);

    proc->ciclos_restantes--;

    if (proc->ciclos_restantes <= 0) {
        proc->estado = Executado;
        proc->ativo = 0; 
        memoria_utilizada -= proc->memoria_alocada; 
        
        printf("[CPU] Processo '%s' (PID %d) CONCLUIDO e removido da memoria.\n", proc->nome, proc->PID);
        printf("[RAM] Memoria liberada. Uso atual: %d/%d MB\n", memoria_utilizada, MEMORIA_TOTAL);
    } else {
        proc->estado = Pronto;
        printf("[CPU] Tempo esgotado (Quantum). Processo '%s' retornou para PRONTO com %d ciclos restantes.\n", proc->nome, proc->PID, proc->ciclos_restantes);
    }
}