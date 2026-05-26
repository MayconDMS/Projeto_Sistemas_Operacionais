#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    inicializar_sistema();

    char entrada[100];

    while (1) {
        printf("shell> ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            break;
        }

        entrada[strcspn(entrada, "\n")] = '\0'; 

        char *comando = strtok(entrada, " "); 

        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "sair") == 0) {
            printf("Encerrando sistema...\n");
            break;
        }

        else if (strcmp(comando, "listar") == 0 || strcmp(comando, "ps") == 0) {
            comando_ps();
        }

        else if (strcmp(comando, "spawn") == 0) {
            char *arg_nome = strtok(NULL, " ");
            char *arg_memoria = strtok(NULL, " ");
            char *arg_ciclos = strtok(NULL, " ");

            if (arg_nome == NULL || arg_memoria == NULL || arg_ciclos == NULL) {
                printf("ERRO: Uso correto: spawn [nome] [memoria] [ciclos]\n");
                printf("Exemplo: spawn Firefox 256 5\n");
            } else {
                int memoria = atoi(arg_memoria);
                int ciclos = atoi(arg_ciclos);
                comando_spawn(arg_nome, memoria, ciclos);
            }
        }

        else if (strcmp(comando, "kill") == 0) {
            char *arg_pid = strtok(NULL, " ");

            if (arg_pid == NULL) {
                printf("ERRO: Uso correto: kill [PID]\n");
                printf("Exemplo: kill 2\n");
            } else {
                int pid = atoi(arg_pid);
                comando_kill(pid);
            }
        }

        else if (strcmp(comando, "cpu") == 0) {
            rodar_escalonador_rr();
        }

        else {
            printf("Comando invalido!\n");
        }
    }

    return 0;
}