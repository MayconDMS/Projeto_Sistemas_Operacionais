#include "cmake-build-debug/pcb.h"
#include <stdio.h>
#include <string.h>

int main() {
    inicializar_sistema();

    char entrada[100]; // Cria um buffer para armazenar a entrada

    while (1) {

        printf("shell> ");

        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = '\0'; // O fgets lê o enter e guarda como "\n", essa linha exclui isso

        char *comando = strtok(entrada, " "); // Divide a string usando espaço como delimitador

        // Evita processar entrada vazia
        if (comando == NULL) {
            continue;
        }

        // Comando para encerrar o sistema
        if (strcmp(comando, "sair") == 0) {
            printf("Encerrando sistema...\n");
            break;
        }

        // Comando para listar processos
        else if (strcmp(comando, "listar") == 0) {
            printf("Listando processos...\n");
        }

        // Comando para criar processo
        else if (strcmp(comando, "criar") == 0) {
            printf("Criando processo...\n");
        }

        // Caso o comando não exista
        else {
            printf("Comando invalido!\n");
        }
    }

    return 0;
}
