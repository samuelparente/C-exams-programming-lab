/*
Programa para gerir vendas e stocks de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "menu.h"

void menu(PRODUTO **lista_produtos, int *num_produtos,VENDA **lista_vendas, int *num_vendas) {
    
    //declaração de variáveis e apontadores
    int opcao;

    //apresenta o menu
    do {
        
        printf("+-------------------------------------------------------------------------------+\n");
        printf("| GESTAO DE LOJA - PRODUTOS E VENDAS                                            |\n");
        printf("+--------------------------+-------------------------+--------------------------+\n");
        printf("|         PRODUTOS         |         VENDAS          |        RELATORIOS        |\n");
        printf("+--------------------------+-------------------------+--------------------------+\n");
        printf("| 1 - Listar produtos      | 6 - Venda a cliente     | 8 - Faturacao            |\n");
        printf("| 2 - Inserir produto      | 7 - Listar vendas       |                          |\n");
        printf("| 3 - Alterar produto      |                         |                          |\n");
        printf("| 4 - Remover produto      |                         |                          |\n");
        printf("| 5 - Pesquisar produto    |                         |                          |\n");
        printf("+--------------------------+-------------------------+--------------------------+\n");
        printf("|                             0 - SAIR DO PROGRAMA                              |\n");
        printf("+-------------------------------------------------------------------------------+\n\n");
        printf("Escolha uma opcao: ");
        
       // lê opção escolhida pelo utilizador e verifica se a entrada contém apenas um número válido
        if (scanf("%d", &opcao) != 1) {

            // Limpa o buffer de entrada de caracteres adicionais
            while (getchar() != '\n');
            
            opcao=9; //opcao dummy para forçar o salto para o default por entrada inválida
        }
        //seleciona a opcão escolhido pelo utilizador
        switch (opcao) {
            case 1:
                mostraProdutos(*lista_produtos, *num_produtos);
                break;

            case 2:
                adicionaProduto(lista_produtos, num_produtos);
                gravarCsvProdutos(FICHEIRO_PRODUTOS, *lista_produtos, *num_produtos);
                break;

            case 3:
                atualizaProduto(*lista_produtos, *num_produtos);
                gravarCsvProdutos(FICHEIRO_PRODUTOS, *lista_produtos, *num_produtos);
                break;

            case 4:
                removeProduto(lista_produtos, num_produtos);
                gravarCsvProdutos(FICHEIRO_PRODUTOS, *lista_produtos, *num_produtos);
                break;

            case 5:
                pesquisaProduto(*lista_produtos,*num_produtos);
                break;

            case 6:
                adicionaVenda(lista_vendas, num_vendas, *lista_produtos, *num_produtos);
                gravarCsvVendas(FICHEIRO_VENDAS, *lista_vendas, *num_vendas);
                break;

            case 7:
                mostraVendas(*lista_vendas, *num_vendas);
                break;

            case 8:
                geraRelatorioVendas(*lista_vendas, *num_vendas, *lista_produtos, *num_produtos);
                break;

            case 0:
                printf("Programa terminado\n");
                break;


            default:
                printf("Opcao incorrecta. Tente novamente.\n");
                break;
        }
    }
     
    while (opcao != 0);
    
}
