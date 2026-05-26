#define MAX_PROCESSOS 10 
#define MEMORIA_TOTAL 1024 

#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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

// COMANDO SPAWN (Ajustado char *nome)
void comando_spawn(char *nome, int tamanho_memoria, int ciclos) { 
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
    tabela_processos[slot].ativo = 1;                  
    strcpy(tabela_processos[slot].nome, nome);
    tabela_processos[slot].memoria_alocada = tamanho_memoria;
    tabela_processos[slot].ciclos_restantes = ciclos;
    tabela_processos[slot].estado = Pronto;            
    
    // Simula a alocação somando a memória gasta
    memoria_utilizada += tamanho_memoria; 

    // 4. Feedback visual no terminal
    printf("[SPAWN] Sucesso: Processo '%s' (PID %d) criado no slot %d (%d ciclos, %d MB).\n", 
           tabela_processos[slot].nome, tabela_processos[slot].PID, slot, ciclos, tamanho_memoria);
    printf("[RAM] Memoria utilizada: %d/%d MB\n", memoria_utilizada, MEMORIA_TOTAL);
}

// COMANDO PS (Listar Processos)
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

// === COMANDO KILL (Encerrar Processo) ===
void comando_kill(int pid) {
    // Busca o processo pelo PID recebido
    for (int i = 0; i < MAX_PROCESSOS; i++) {
        if (tabela_processos[i].ativo == 1 && tabela_processos[i].PID == pid) {
            
            // Guarda o nome e a memória para o feedback visual
            char nome_removido[20];
            strcpy(nome_removido, tabela_processos[i].nome);
            int memoria_liberada = tabela_processos[i].memoria_alocada;

            // Remoção Lógica e Liberação de RAM
            tabela_processos[i].ativo = 0; 
            memoria_utilizada -= memoria_liberada;

            printf("[KILL] Processo '%s' (PID %d) encerrado com sucesso.\n", nome_removido, pid);
            printf("[RAM] Memoria liberada: %d MB. Uso atual: %d/%d MB\n", memoria_liberada, memoria_utilizada, MEMORIA_TOTAL);
            return; // Sai da função imediatamente pois já encontrou e resolveu
        }
    }

    // Se o loop terminar e não der o return, significa que o PID não existe ou não está ativo
    printf("ERRO: Processo com PID %d nao encontrado.\n", pid);
}