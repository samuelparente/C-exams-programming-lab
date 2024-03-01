/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "operacoesCsv.h"

//função para ler o ficheiro dos produtos e carregar dinamicamente os produtos em memória.
//Retorna um apontador para os dados alocados.

PRODUTO *lerCsvProdutos(const char *ficheiro,int *num_produtos){

    //declaração de variáveis e apontadores
    FILE *fp; //apontador para o ficheiro
    char *codigo = NULL; //apontador coluna código no ficheiro
    char *preco = NULL; //apontador coluna preço no ficheiro
    char *designacao = NULL; //apontador coluna descrição no ficheiro
    char linhaFicheiroMax[LINHA_MAX_LENGTH]; //variável para armazenar a linha lida do ficheiro
    int contadorLinhas = 0; //variável para armazenar o total de linhas do ficheiro
    int linhaActual = 0; // variável para armazenar a linha atual para as iterações
    int i = 0;
    int j = 0;
    int len = 0;
    int num_virgulas = 0;
    fp = fopen(ficheiro,"r");
    
    if (fp == NULL) //ficheiro não existe
    {
        printf ("O ficheiro com os dados dos produtos nao existe.\n");
        printf ("Por favor crie um ficheiro \"%s\" na pasta do programa com o cabecalho \"codigo,designacao,preco\".\n\n",FICHEIRO_PRODUTOS);
        return NULL; 
    }
    else{

        //ler quantidade de linhas do ficheiro e verifica se tem as 3 colunas.
        while (fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp)) {
           
           // contar o número de vírgulas na linha
            num_virgulas=0;
            for (i = 0; i<strlen(linhaFicheiroMax); i++) {
                if (linhaFicheiroMax[i] == ',') {
                    num_virgulas++;
                }
            }

            // validar que tem exatamente 3 colunas separadas por vírgulas
            if (num_virgulas != 2) {
                printf("Erro na linha %d: o numero de campos deve ser igual a 3.\n", contadorLinhas+1);
                return NULL;
            }

            contadorLinhas++;
        }

        //retorna ao inicio do ficheiro
        rewind(fp);

        //cria o espaço necessário em memoria para depois adicionar os produtos lidos do ficheiro e
        //um apontador para aceder aos dados
        PRODUTO *lista_produtos = (PRODUTO*)malloc(contadorLinhas*sizeof(PRODUTO));

        //verifica se alocou corretamente espaço em memória para carregar os dados lidos do ficheiro
        if (lista_produtos == NULL) {
            printf("Erro ao alocar memória para carregar a lista de produtos.\n\n");
            return NULL;
        }

        // descarta a primeira linha do arquivo (cabeçalho) - leitura "dummy"
        fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp);
        
        linhaActual++; 
        
        //verifica a integridade do ficheiro e aloca em memória os dados do ficheiro
        while (fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp)) {
            
            codigo = strtok(linhaFicheiroMax,",");
            designacao = strtok(NULL,",");
            preco = strtok(NULL,",");

            //validar se tem campos vazios,tamanho e tipo de dados correctos.
            if(codigo == NULL || designacao == NULL || preco == NULL){
                printf("Erro na linha %d: verifique campos vazios.\n\n", linhaActual+1);
                return NULL;
            }
            else{

                // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
                len = strlen(codigo);
                if (len > 0 && codigo[len-1] == '\n') {
                    codigo[len-1] = '\0';
                }
                len = strlen(designacao);
                if (len > 0 && designacao[len-1] == '\n') {
                    designacao[len-1] = '\0';
                }
                len = strlen(preco);
                if (len > 0 && preco[len-1] == '\n') {
                    preco[len-1] = '\0';
                }
                //verifica tipo correto dos dados.
                i = validaInteiroFloat(codigo);
                j = validaInteiroFloat(preco);

                if(i == 0 || j == 0){
                    printf("Erro na linha %d: verifique os campos \"codigo\" e \"preco\".\n\n", linhaActual+1);
                    return NULL;
                }
                else{
                    //verifica comprimento dos campos
                    if(strlen(codigo)>MAX_CODIGO_LENGTH || strlen(designacao)>MAX_DESIGNACAO_LENGTH || strlen(preco)>MAX_PRECO_LENGTH){
                        printf("Erro na linha %d: verifique o limite de caracteres dos campos.\n\n", linhaActual+1);
                        return NULL;
                    }
                    else{
                        lista_produtos[linhaActual].codigo = atoi(codigo);
                        strcpy(lista_produtos[linhaActual].designacao, designacao);
                        lista_produtos[linhaActual].preco = strtof(preco,NULL);
                    }
                }    
            }
            
            linhaActual++;
        }

    printf( "Ficheiro com os dados dos produtos lido com sucesso.\n\n");
    
    *num_produtos = contadorLinhas;
    return lista_produtos;
    
    }
    
    fclose(fp); 
}

//função para gravar no ficheiro com lista dos produtos os dados alocados na memória. Não retorna nada.
void gravarCsvProdutos(const char *ficheiro, PRODUTO *lista_produtos, int num_produtos) {
    
    //variáveis a apontadores
    FILE *fp; //apontador para o ficheiro
    int i = 0; //variável genérica de apoio

    // abre o ficheiro para escrita
    fp = fopen(ficheiro, "w");

    //verifica se abriu com sucesso
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro para gravar dados.\n\n");
    }
    else{
        //escrever cabeçalho
        fprintf(fp, "codigo,designacao,preco\n");
        
        // escrever produtos
        for (i = 1; i < num_produtos; i++) {
            fprintf(fp,"%d,%s,%.2f\n",
                    lista_produtos[i].codigo,
                    lista_produtos[i].designacao,
                    lista_produtos[i].preco);
        }

    }
    
    fclose(fp);
}

//função para ler o ficheiro das vendas e carregar dinamicamente as vendas em memória.
//Retorna um apontador para os dados alocados.
VENDA *lerCsvVendas(const char *ficheiro,int *num_vendas){

    //declaração de variáveis e apontadores
    FILE *fp; //apontador para o ficheiro
    char *codigo; //apontador coluna código no ficheiro
    char *quantidade; //apontador coluna quantidade no ficheiro
    char *dataVenda; //apontador coluna data de venda no ficheiro
    char linhaFicheiroMax[LINHA_MAX_LENGTH]; //variável para armazenar a linha lida do ficheiro
    int contadorLinhas = 0; //variável para armazenar total de linhas
    int linhaActual = 0; //variável para armazenar a linha atual para as iterações
    int i = 0; //variavel generica
    int j = 0;  //variavel generica
    int len = 0;  //variavel generica
    int num_virgulas = 0; //variável para armazenar a quantidade de separadores de campo
    
    //abre o ficheiro para leitura
    fp = fopen(ficheiro,"r");
    
    if (fp == NULL) //ficheiro não existe
    {
        printf ("O ficheiro com os dados das vendas efetuadas nao existe.\n");
        printf ("Por favor crie um ficheiro \"%s\" na pasta do programa com o cabecalho \"codigo,quantidade,data\".\n\n",FICHEIRO_VENDAS);

    }
    else{

        //ler quantidade de linhas do ficheiro
        while (fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp)) {
        
             // contar o número de vírgulas na linha
            num_virgulas=0;
            for (i = 0; i<strlen(linhaFicheiroMax); i++) {
                if (linhaFicheiroMax[i] == ',') {
                    num_virgulas++;
                }
            }

            // validar que tem exatamente 3 colunas separadas por vírgulas
            if (num_virgulas != 2) {
                printf("Erro na linha %d: o numero de campos deve ser igual a 3.\n", contadorLinhas+1);
                return NULL;
            }

            contadorLinhas++;

        }

        //retorna ao inicio do ficheiro
        rewind(fp);

        //cria o espaço necessário em memoria para carregar os dados das vendas
        VENDA *lista_vendas = (VENDA*)malloc(contadorLinhas*sizeof(VENDA));

        // descarta a primeira linha do arquivo (cabeçalho) - leitura dummy
        fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp);
        linhaActual++; 
        
        //aloca em memória os dados do ficheiro
        while (fgets(linhaFicheiroMax, sizeof(linhaFicheiroMax), fp)) {
            
            codigo = strtok(linhaFicheiroMax,",");
            quantidade = strtok(NULL,",");
            dataVenda = strtok(NULL,",");

            //validar se tem campos vazios,tamanho e tipo de dados correctos.
            if(codigo == NULL || quantidade == NULL || dataVenda == NULL){
                printf("Erro na linha %d: verifique campos vazios.\n\n", linhaActual+1);
                return NULL;
            }
            else{

                // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
                len = strlen(codigo);
                if (len > 0 && codigo[len-1] == '\n') {
                    codigo[len-1] = '\0';
                }
                len = strlen(quantidade);
                if (len > 0 && quantidade[len-1] == '\n') {
                    quantidade[len-1] = '\0';
                }
                len = strlen(dataVenda);
                if (len > 0 && dataVenda[len-1] == '\n') {
                    dataVenda[len-1] = '\0';
                }
                //verifica tipo correto dos dados.
                i = validaInteiroFloat(codigo);
                j = validaInteiroFloat(quantidade);

                if(i == 0 || j == 0){
                    printf("Erro na linha %d: verifique os campos \"codigo\" e \"quantidade\".\n\n", linhaActual+1);
                    return NULL;
                }
                else{
                    //verifica comprimento dos campos
                    if(strlen(codigo)>MAX_CODIGO_LENGTH || strlen(quantidade)>MAX_QUANTIDADE_LENGTH || strlen(dataVenda)>MAX_DATAVENDA_LENGTH){
                        printf("Erro na linha %d: verifique o limite de caracteres dos campos.\n\n", linhaActual+1);
                        return NULL;
                    }
                    else{
                        lista_vendas[linhaActual].codigo = atoi(codigo);
                        lista_vendas[linhaActual].quantidade = atoi(quantidade);
                        strcpy(lista_vendas[linhaActual].dataVenda, dataVenda);
                    }
                }    
            }
            
            linhaActual++;
        }

    printf( "Ficheiro com os dados das vendas lido com sucesso.\n\n");
   
    *num_vendas = contadorLinhas;
    return lista_vendas;
    }
    
    fclose(fp);

}

//função para gravar no ficheiro com dados das vendas os dados alocados na memória. Não retorna nada.
void gravarCsvVendas(const char *ficheiro, VENDA *lista_vendas, int num_vendas) {
    
    //variàveis e apontadores
    int i = 0; //variável genérica de apoio
    FILE *fp; //apontador do tipo ficheiro

    // abrir arquivo para escrita
    fp = fopen(ficheiro, "w");

    //verifica se abriu o ficheiro
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro para gravar a venda a cliente.\n");
        return;
    }
    
    // escrever cabeçalho
    fprintf(fp, "codigo,quantidade,data\n");
    
    // escrever produtos
    for (i = 1; i < num_vendas; i++) {
        fprintf(fp,"%d,%d,%s\n",
                lista_vendas[i].codigo,
                 lista_vendas[i].quantidade,
                 lista_vendas[i].dataVenda);
    }
    
    // fechar arquivo
    fclose(fp);
}
