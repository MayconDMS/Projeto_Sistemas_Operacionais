#define MAX_PROCESSOS 10 //10 slots
#define MEMORIA_TOTAL 1024 //1GB

#include "cmake-build-debug/pcb.h"
PCB tabela_processos[MAX_PROCESSOS];

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
