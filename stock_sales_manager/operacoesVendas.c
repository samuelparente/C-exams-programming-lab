/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "operacoesVendas.h"

//função para mostrar as vendas efetuadas de acordo com os dados carregados do ficheiro de vendas.Não retorna nada.
void mostraVendas(VENDA *lista_vendas, int num_vendas) {

    printf("+---------------------+---------------------+---------------------+\n");
    printf("| Codigo              | Quantidade          | Data da venda       |\n");
    printf("+---------------------+---------------------+---------------------+\n");

    for (int i = 1; i < num_vendas; i++) {
        printf("| %-19d | %-19d | %-19s |\n", lista_vendas[i].codigo, lista_vendas[i].quantidade, lista_vendas[i].dataVenda);
    }

    printf("+---------------------+---------------------+---------------------+\n\n");
}

//função para fazer uma venda a cliente. Não retorna nada
void adicionaVenda(VENDA **lista_vendas, int *num_vendas, PRODUTO *lista_produtos, int num_produtos){

    //variáveis e apontadores
    time_t tempoAtual; //variável do tipo time_t
    char date_string[20]; //variável para armazenar a data
    int codigoLido=0; //variável para armazenar código digitado pelo utilizador
    int indiceProduto = -1; // variável para armazenar o retorno da função que procura se produto existe
    char stringTemp[50]; //variavel generica
    int j = 0; //variavel generica
    int len = 0; //variavel generica

    // Obter o tempo atual
    tempoAtual = time(NULL);

    // Formatar a data e armazenar em uma string
    strftime(date_string, sizeof(date_string), "%d/%m/%Y", localtime(&tempoAtual));

    // realocar a lista de vendas para acomodar a nova venda
    *num_vendas += 1;
    *lista_vendas = (VENDA*)realloc(*lista_vendas, *num_vendas * sizeof(VENDA));

    //valida alocação de memoria
    if (lista_vendas == NULL) {
            printf("Erro a criar nova venda.\n");
            return;
        }

    // preencher os campos da nova venda
    printf("Insira o codigo do produto (max. 8 caracteres): ");
    
    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 

    fgets(stringTemp,9,stdin);
    //ler comprimento da string
    len = strlen(stringTemp);
    // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (len > 0 && stringTemp[len-1] == '\n') {
    
        stringTemp[len-1] = '\0';
    }

    //verifica se codigo é um número
    j = validaInteiroFloat(stringTemp);

    while(j != 1){

        printf("Entrada invalida.So pode conter numeros.\n\n");
        printf("Insira o codigo do produto (max. 8 caracteres): ");
        // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
        fflush(stdin); 

        fgets(stringTemp,9,stdin);
        //ler comprimento da string
        len = strlen(stringTemp);
        // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
        if (len > 0 && stringTemp[len-1] == '\n') {
        
            stringTemp[len-1] = '\0';
        }
        j = validaInteiroFloat(stringTemp);
    }

    codigoLido = atoi(stringTemp);


    // verifica se o produto existe
    indiceProduto = verificaProduto(lista_produtos, num_produtos, codigoLido);

    if (indiceProduto == -1) {
            printf("Produto nao encontrado.\n\n");
            *num_vendas -= 1;
            *lista_vendas = (VENDA*)realloc(*lista_vendas, *num_vendas * sizeof(VENDA));

            //valida alocação de memoria
            if (lista_vendas == NULL) {
                    printf("Erro a retornar dados de vendas anteriores.\n");
                    return;
                }
            return;
        }

    printf("Insira a quantidade para venda (max. 8 caracteres): ");
    
    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 

    fgets(stringTemp,9,stdin);
    //ler comprimento da string
    len = strlen(stringTemp);
    // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (len > 0 && stringTemp[len-1] == '\n') {
    
        stringTemp[len-1] = '\0';
    }

    //verifica se codigo é um número
    j = validaInteiroFloat(stringTemp);

    while(j != 1){

        printf("Entrada invalida.So pode conter numeros.\n\n");
        printf("Insira a quantidade para venda (max. 8 caracteres): ");
        // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
        fflush(stdin); 

        fgets(stringTemp,9,stdin);
        //ler comprimento da string
        len = strlen(stringTemp);
        // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
        if (len > 0 && stringTemp[len-1] == '\n') {
        
            stringTemp[len-1] = '\0';
        }
        j = validaInteiroFloat(stringTemp);
    }

    //insere quantidade vendida
    (*lista_vendas)[*num_vendas-1].quantidade = atoi(stringTemp);
    //insere a data da venda
    strcpy((*lista_vendas)[*num_vendas-1].dataVenda,date_string);
    //insere o codigo
    (*lista_vendas)[*num_vendas-1].codigo = codigoLido;

    printf("Venda efetuada com sucesso!\n\n");
}
