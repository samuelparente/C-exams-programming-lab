/*
Programa para gerir vendas e stocks de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "funcoesGenericas.h"

//Função para verificar se a entrada contém apenas dígitos e, no máximo, um ponto decimal.
//A função retorna 1 se não há ponto decimal ou 2 se houver um ponto decimal. 
//Caso contrário, retorna 0 indicando uma entrada inválida.
int validaInteiroFloat(char *entrada) {
    int i, ponto = 0;
    for (i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] == '.' || entrada[i] == ',') {
            if (ponto == 1) return 0;
            ponto = 1;
        }
        else if (!isdigit(entrada[i])) {
            return 0;
        }
    }
    if (ponto == 1) {
        return 2;
    }
    else {
        return 1;
    }
}
