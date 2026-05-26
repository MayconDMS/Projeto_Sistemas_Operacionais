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

        // Remove a quebra de linha (\n) capturada pelo fgets
        entrada[strcspn(entrada, "\n")] = '\0'; 

        // Captura o primeiro argumento (o comando digitado)
        char *comando = strtok(entrada, " "); 

        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "sair") == 0) {
            printf("Encerrando sistema...\n");
            break;
        }

        else if (strcmp(comando, "listar") == 0) {
            printf("Listando processos...\n");
        }

        else if (strcmp(comando, "spawn") == 0) {
            // Captura os argumentos subsequentes separados por espaço
            char *arg_memoria = strtok(NULL, " ");
            char *arg_ciclos = strtok(NULL, " ");

            if (arg_memoria == NULL || arg_ciclos == NULL) {
                printf("ERRO: Uso correto: spawn [memoria] [ciclos]\n");
                printf("Exemplo: spawn 256 5\n");
            } else {
                int memoria = atoi(arg_memoria);
                int ciclos = atoi(arg_ciclos);
                
                comando_spawn(memoria, ciclos);
            }
        }

        else {
            printf("Comando invalido!\n");
        }
    }

    return 0;
}