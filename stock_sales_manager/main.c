/*Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "main.h"

//Entrada programa principal.
int main() {

  //declaração de variàveis a apontadores
  int num_produtos;
  PRODUTO *lista_produtos = NULL;
  int num_vendas = 0;
  VENDA *lista_vendas = NULL;
  int estadoFicheiro = 0;

  printf("---> A carregar ficheiro com os dados dos produtos...\n\n");

  //ler ficheiro dos produtos e carregar para a memória
  lista_produtos = lerCsvProdutos(FICHEIRO_PRODUTOS,&num_produtos);

  printf ("---> A carregar ficheiro com os dados das vendas efetuadas...\n\n");

  //ler ficheiro das vendas e carregar para a memória
  lista_vendas = lerCsvVendas(FICHEIRO_VENDAS,&num_vendas);

  //so apresenta o menu se a leitura dos ficheiros for bem sucedida
  
  if (lista_produtos!=NULL && lista_vendas!=NULL){

     //apresenta o menu e chama as funções de acordo com a opção escolhida
     menu(&lista_produtos,&num_produtos,&lista_vendas,&num_vendas);

  }
  else{
     printf("\nExiste um erro nos ficheiros.\nVerifique se estao de acordo com as especificacoes.\n\n");
     printf("O programa vai encerrar em 5 segundos...");
     sleep(5);
  }

  
  //liberta a memória alocada usada para carregar os ficheiros e sai do programa
  free(lista_produtos);
  free (lista_vendas);

  return 0;
}



