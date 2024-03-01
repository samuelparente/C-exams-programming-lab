/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "operacoesProduto.h"

//função para apresentar ao utilizador a lista de produtos. Não retorna nada.
void mostraProdutos(PRODUTO *lista_produtos, int num_produtos) {

    //variáveis e apontadores
    int i = 0; //variável genérica para as iterações
    
    printf("+---------------------+------------------------------------------------------------+----------------+\n");
    printf("| Codigo              | Descricao                                                  | Preco          |\n");
    printf("+---------------------+------------------------------------------------------------+----------------+\n");

    for (i = 1; i < num_produtos; i++) {
        printf("| %-19d | %-58s | %14.2f |\n", lista_produtos[i].codigo, lista_produtos[i].designacao, lista_produtos[i].preco);
    }

    printf("+---------------------+------------------------------------------------------------+----------------+\n");

}

//função para adicionar um novo produto. Não retorna nada
void adicionaProduto(PRODUTO **lista_produtos, int *num_produtos){

    //variáveis e apontadores
    int i = 0; //variável genérica para as iterações
    int j = 0; //variável genérica
    int len = 0; //variável genérica
    int indiceProduto = 0; //índice do produto
    int codigoLido = 0; //variável para armazenar o código de entrada
    char stringTemp[50]; //variável genérica

    // ler o código do novo produto
    printf("Insira o codigo do novo produto (max. 8 caracteres): ");
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
        printf("Insira o codigo do novo produto (max. 8 caracteres): ");
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

    //foi inserido um numero...
    codigoLido = atoi(stringTemp);

    // verifica se o produto já existe
    indiceProduto = verificaProduto(*lista_produtos, *num_produtos, codigoLido);

    if(indiceProduto != -1){
        printf("O produto com o codigo que inseriu ja se encontra registado.\n\n");
        return;
    }

    //realocar a lista de produtos para acomodar o novo produto se este ainda não existe
    *num_produtos += 1;
    *lista_produtos = (PRODUTO*)realloc(*lista_produtos, *num_produtos * sizeof(PRODUTO));

    //verifica se alocou espaço em memória para carregar os dados lidos do ficheiro
    if (lista_produtos == NULL) {
       
        printf("Erro ao alocar memória para o novo produto.\n");
        return;
    }

    (*lista_produtos)[*num_produtos-1].codigo = codigoLido;

    //pede a descrição do produto
    printf("Insira a descricao do novo produto (max. 49 caracteres): ");
    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 
    //como o limite são 50 caracteres na variável, o utilizador fica limitado a 49 caracteres.
    fgets(stringTemp,50,stdin);
    //ler comprimento da string
    len = strlen(stringTemp);
    // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (len > 0 && stringTemp[len-1] == '\n') {
        stringTemp[len-1] = '\0';
    }
    strcpy((*lista_produtos)[*num_produtos-1].designacao,stringTemp);

    printf("Insira o preco do novo produto (max. 8 caracteres): ");
    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 
    fgets(stringTemp,9,stdin);
    //ler comprimento da string
    len = strlen(stringTemp);
    // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (len > 0 && stringTemp[len-1] == '\n') {
       
        stringTemp[len-1] = '\0';
    }
    //verifica se preço é um número
    j = validaInteiroFloat(stringTemp);

    while(j == 0){

        printf("Entrada invalida.So pode conter numeros e apenas 1 separador decimal \".\" ou \",\"\n\n");
        printf("Insira o preco do novo produto (max. 8 caracteres): ");
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

    // substituir vírgulas por pontos no preço se o utilizador usou virgula e não ponto como separador decimal
    for (i = 0; stringTemp[i] != '\0'; i++) {
        
        if (stringTemp[i] == ',') {
            stringTemp[i] = '.';
        }
    }

    // Armazenar o preço na estrutura produto
    (*lista_produtos)[*num_produtos-1].preco = strtof(stringTemp, NULL);

    printf("Produto adicionado com sucesso!\n\n");
}

//função para atualizar os campos de um produto já existente. Não retorna nada
void atualizaProduto(PRODUTO *lista_produtos, int num_produtos) {
    
    //variáveis e apontadores
    int codigo = 0; //variável para armazenar a entrada do código do produto
    int i = 0; // variável genérica de apoio para as iterações
    int j = 0; //variável genérica
    char escolha; //variável para armazenar a opção escolhida
    int len = 0; //variável genérica
    char stringTemp[50]; //string temporária

    printf("Insira o codigo do produto a ser atualizado (max. 8 caracteres): ");
    
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
        printf("Insira o codigo do novo produto (max. 8 caracteres): ");
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

    //foi inserido um numero...
    codigo = atoi(stringTemp);

    // Procura o produto pelo código
    for (i = 0; i < num_produtos; i++) {
        if (lista_produtos[i].codigo == codigo) {
            break;
        }
    }

    // Caso não encontre o produto
    if (i == num_produtos) {
        printf("O produto nao se encontra registado.\n\n");
        return;
    }

    // Caso encontre o produto
    printf("+---------------------------------------------------------------------------------------------------+\n");
    printf("|                                        PRODUTO ENCONTRADO                                         |\n");      
    printf("+----------------+-------------------------------------------------------------------+--------------+\n");
    printf("| Codigo         | Descricao                                                         | Preco        |\n");
    printf("+----------------+-------------------------------------------------------------------+--------------+\n");
    printf("| %-14d | %-65s | %12.2f |\n", lista_produtos[i].codigo, lista_produtos[i].designacao, lista_produtos[i].preco);
    printf("+--------------------+---------------------------------------------------------------+--------------+\n");
    printf("| C - Alterar codigo     |\n");
    printf("| D - Alterar designacao |\n");
    printf("| P - Alterar preco      |\n");
    printf("| S - Nao alterar        |\n");
    printf("+------------------------+\n\n");
    printf("Escolha uma opcao: ");
    
    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 
    
    scanf(" %c", &escolha);

    switch (escolha) {
        
        case 'C':

            printf("Insira o novo codigo (max. 8 caracteres): ");
            
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
                printf("Insira o novo codigo: (max. 8 caracteres): ");
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

            //foi inserido um numero...
            lista_produtos[i].codigo = atoi(stringTemp);

            printf("Codigo atualizado com sucesso.\n\n");
            break;
        
        case 'D':
        
            printf("Insira a nova designacao (max. 49 caracteres): ");
            // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
            fflush(stdin); 
            //como o limite são 50 caracteres na variável, o utilizador fica limitado a 49 caracteres.
            fgets(stringTemp,50,stdin);
            //ler comprimento da string
            len = strlen(stringTemp);
            // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
            if (len > 0 && stringTemp[len-1] == '\n') {
                stringTemp[len-1] = '\0';
            }
            strcpy(lista_produtos[i].designacao,stringTemp);
            printf("Designacao atualizada com sucesso.\n\n");
            break;

        case 'P':
            
            printf("Insira o novo preco (max. 8 caracteres): ");
            // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
            fflush(stdin); 
            fgets(stringTemp,9,stdin);
            //ler comprimento da string
            len = strlen(stringTemp);
            // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
            if (len > 0 && stringTemp[len-1] == '\n') {
            
                stringTemp[len-1] = '\0';
            }
            //verifica se preço é um número
            j = validaInteiroFloat(stringTemp);

            while(j == 0){

                printf("Entrada invalida.So pode conter numeros e apenas 1 separador decimal \".\" ou \",\"\n\n");
                printf("Insira o novo preco (max. 8 caracteres): ");
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

            // substituir vírgulas por pontos no preço se o utilizador usou virgula e não ponto como separador decimal
            for (j = 0; stringTemp[j] != '\0'; j++) {
                
                if (stringTemp[j] == ',') {
                    stringTemp[j] = '.';
                }
            }
            // Armazenar o preço na estrutura produto
            lista_produtos[i].preco = strtof(stringTemp, NULL);
            printf("Preco atualizado com sucesso.\n\n");
            break;

        case 'S':
            break;
        
        default:

            printf("Opcao incorrecta.\n\n");
            break;
    }
}    

//função para remover um produto da lista. Não retorna nada.
void removeProduto(PRODUTO **lista_produtos, int *num_produtos) {

    //variáveis e apontadores
    int codigo = 0;
    int indice = -1;
    int i = 0;
    int j = 0;
    int len = 0;
    char stringTemp[50];

    //Solicita ao utilizador o código do produto a remover
    printf("Insira o codigo do produto a ser removido (max. 8 caracteres): ");
 
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
        printf("Insira o codigo do produto a ser removido (max. 8 caracteres): ");
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

    codigo = atoi(stringTemp);
    
    // Procura o índice do produto com o código fornecido
    for (i= 0; i < *num_produtos; i++) {
        if ((*lista_produtos)[i].codigo == codigo) {
            indice = i;
            break;
        }
    }
    
    // Se o índice do produto foi encontrado, remove o produto e reorganiza a lista
    if (indice != -1) {
      
        for (i = indice; i < *num_produtos - 1; i++) {
            (*lista_produtos)[i] = (*lista_produtos)[i+1];
        }

        (*num_produtos)--;
        
        *lista_produtos = (PRODUTO*)realloc((*lista_produtos), (*num_produtos)*sizeof(PRODUTO));

        if (lista_produtos == NULL) {
            printf("Erro ao remover o produto.\n");
            return;
        }

        printf("O produto com o codigo %d foi removido com sucesso.\n\n", codigo);
    } 
    
    else {
       
        printf("O produto com o codigo %d nao existe.\n", codigo);
    
    }
    
}

//função para procurar produtos. Por código encontra apenas 1 produto pois cada código é único. Por palavra
//procura todos os produtos que tenham o termo de pesquisa na designacao. Não retorna nada.
void pesquisaProduto(PRODUTO *lista_produtos, int num_produtos) {
    
    int encontrado = 0; // variável de contagem dos produtos encontrados
    int i = 0; // variável genérica para a iteração
    int len = 0;
    char pesquisa[128]; //variável para armazenar o código ou termo de pesquisa

    printf("Insira o codigo do produto ou termo a pesquisar: ");

    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin); 
    
    //ler entrada.limite são 127 caracteres na variável
    fgets(pesquisa,127,stdin);
    //ler comprimento da string
    len = strlen(pesquisa);
    // Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (len > 0 && pesquisa[len-1] == '\n') {
        pesquisa[len-1] = '\0';
    }

    printf("+---------------------------------------------------------------------------------------------------+\n");
    printf("|                                      RESULTADO DA PESQUISA                                        |\n");      
    printf("+----------------+-------------------------------------------------------------------+--------------+\n");
    printf("| Codigo         | Descricao                                                         | Preco        |\n");
    printf("+----------------+-------------------------------------------------------------------+--------------+\n");
    
    for (i = 1; i < num_produtos; i++) {
       
        if (lista_produtos[i].codigo == atoi(pesquisa) || strstr(lista_produtos[i].designacao, pesquisa) != NULL) {
            
            printf("| %-14d | %-65s | %12.2f |\n", lista_produtos[i].codigo, lista_produtos[i].designacao, lista_produtos[i].preco);
           
            encontrado++;
        }
    }
    
    printf("+--------------------+---------------------------------------------------------------+--------------+\n");
    printf("Produto(s) encontrado(s): %d\n\n", encontrado);
    
}

//função para verificar se um produto existe. Retorna o índice do produto se encontrar ou -1 se não existir.
int verificaProduto(struct produto *lista_produtos, int num_produtos, int codigoLido){

    //variáveis e apontadores
    int i = 0; //variável genérica para as iterações

    for (i = 0; i < num_produtos; i++) {
        if (lista_produtos[i].codigo == codigoLido) {
            return i; // retorna o índice do produto na lista
        }
    }
    return -1; // retorna -1 se o produto não for encontrado
}

