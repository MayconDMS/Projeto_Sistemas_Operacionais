#ifndef PCB_H
#define PCB_H

// Definição dos estados que um processo pode ter (Enum)
typedef enum {
    Pronto,
    Executando,
    Bloqueado,
    Executado 
} EstadoProcesso;

// Definição da estrutura do Process Control Block (PCB)
typedef struct {
    int ativo;          
    int PID;             
    int ciclos_restantes;
    EstadoProcesso estado; 
} PCB;

void comando_spawn(int tamanho_memoria, int ciclos);
#endif 