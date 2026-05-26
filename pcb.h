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
    char nome[20]; 
    int memoria_alocada;
    int ciclos_restantes;
    EstadoProcesso estado; 
} PCB;

void inicializar_sistema();                         
void comando_spawn(char *nome, int tamanho_memoria, int ciclos);
void comando_ps();
void comando_kill(int pid);
void rodar_escalonador_rr();

#endif