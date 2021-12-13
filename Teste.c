#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MARVEL UNLIMITED - C EDITION
//Já estou com preguiça de comentar....

//Tipo de dado para a data
typedef struct{
    int mes;
    int ano;
} Data;

//Tipo de dado para o quadrinho
typedef struct{
    char* titulo;
    int num;
    Data date;
    int lido;
    char** personagens;
    int qtd_per;
} Comic;

//Lista de funções.
//Dessa vez vou colocar as assinaturas em cima, e as implementações embaixo, só para mudar um pouco :)

//Funções de impressão
void imprime_Menu();
void imprime_Consultas();
void imprime_quadrinho(Comic* q);

//Funções que mexem no arquivo
Comic* carregar_Base(int* tam);

//Funções que alteram dados
Comic* adiciona_quadrinho(Comic* banco, int* tam);
Comic* remove_quadrinho(Comic* banco, int* tam);
void marcar_leitura(Comic* banco, int tam);

//Funções que realizam apenas consulta aos dados
Comic* recupera_quadrinho(Comic* banco, int tam, char* nome, int num);
void consulta_quadrinho(Comic* banco, int tam);
void filtra_lista(Comic* banco, int tam, int param, void* valor);

//Função principal
int main(){
    //Vetor de quadrinhos que conterá uma copia da base de dados em operação no programa. Inicializado com o valor nulo.
    Comic* quadrinhos = NULL;
    //qtd armazenará a quantidade de quadrinhos existentes na base, op lerá qual a operação digitada pelo usuário no menu
    //subop será usada quando precisar de uma opção do submenu
    int qtd, op, subop;

    //Variáveis auxiliares para armazenar leituras da entrada
    int ano;
    int periodo[4];
    char title[1000];

    quadrinhos = carregar_Base(&qtd);

    if(quadrinhos != NULL)
      printf("Base carregada com sucesso!\n\n");
    else{
      printf("Erro ao carregar\n");
      return -1;
    }

    //Laço principal do programa
    do{
        //Imprime o menu do programa
        imprime_Menu();

        scanf("%d", &op);

        //Verifica a escolha no menu
        switch(op){
           //Adiciona um quadrinho
            case 1: quadrinhos = adiciona_quadrinho(quadrinhos, &qtd); break;
            //Remove o quadrinho
            case 2: quadrinhos = remove_quadrinho(quadrinhos, &qtd); break;
            //Pega as informações de um quadrinho
            case 3: consulta_quadrinho(quadrinhos, qtd); break;
            //Abre os menus para consultas gerais
            case 4:
                //Imprime o menu de subconsultas
                imprime_Consultas();

                scanf("%d", &subop);

                //Verifica a opção de consulta escolhida
                switch(subop){
                    //Listar por ano
                    case 1:
                        printf("Digite o ano desejado: ");
                        scanf("%d", &ano);
                        filtra_lista(quadrinhos, qtd, 1, &ano);
                        break;
                    //Lista por periodo
                    case 2:
                        printf("Digite o intervalo desejado (formato MM/AAAA - MM/AAAA): ");
                        scanf("%d/%d - %d/%d", &periodo[0], &periodo[1], &periodo[2], &periodo[3]);
                        filtra_lista(quadrinhos, qtd, 2, periodo);
                        break;
                    //Lista por titulos dos quadrinhos
                    case 3:
                        printf("Digite o titulo da serie de quadrinhos desejado: ");
                        scanf(" %[^\n]s", title);
                        filtra_lista(quadrinhos, qtd, 3, title);
                        break;
                    //Lista quadrinhos que possuem determinado personagem
                    case 4:
                        printf("Digite o nome do personagem: ");
                        scanf(" %[^\n]s", title);
                        filtra_lista(quadrinhos, qtd, 4, title);
                        break;
                    //Lista os quadrinhos que já foram lidos
                    case 5:
                        ano = 1;
                        filtra_lista(quadrinhos, qtd, 5, &ano);
                        break;
                    default: printf("Opcao invalida!\n");
                }
                break;
            //Marca um quadrinho como lido
            case 5: marcar_leitura(quadrinhos, qtd); break;
            //Se for sair, não precisa fazer nada
            case 6: break;
            //Se for digitada outra coisa
            default:
                printf("Opcao Invalida!\n\n");
                getchar(); getchar();
        }
    }while(op != 6);

    //Ao encerrar o programa, salva a versão mais atual da base

    if(quadrinhos != NULL)
        free(quadrinhos);

    return 0;
}

//Função para impressão dos textos do menu principal
void imprime_Menu(){
    printf("\n\nMarvel Unlimited!\n");
    printf("MENU\n");
    printf("1 - Adicionar Quadrinho\n");
    printf("2 - Remover Quadrinho\n");
    printf("3 - Conultar um quadrinho\n");
    printf("4 - Consultas Gerais\n");
    printf("5 - Marcar quadrinho como lido\n");
    printf("6 - Sair\n\n");
    printf("Digite a opcao: ");
}

//Função para impressão dos textos do submenu
void imprime_Consultas(){
    printf("\n\nMenu de Consultas Gerais\n");
    printf("4.1 - Listar Quadrinhos por ano\n");
    printf("4.2 - Listar Quadrinhos por Periodo\n");
    printf("4.3 - Listar Quadrinhos por Serie/Titulo\n");
    printf("4.4 - Listar aparicoes de Personagem em ordem cronologica\n");
    printf("4.5 - Listar quadrinhos lidos\n");
    printf("Digite a opcao (de 1 a 5): ");
}

//Imprime as informacoes de um quadrinho
void imprime_quadrinho(Comic* q){
    int i;

    printf("Titulo: %s\n", q->titulo);
    printf("Numero: %d\n", q->num);
    printf("Data de lancamento: %02d/%d\n", q->date.mes, q->date.ano);

    printf("Status da leitura: ");
    q->lido == 0 ? printf("Nao lido\n"):printf("Lido\n");

    printf("Personagens:\n");

    for(i=0; i < q->qtd_per; i++)
        printf("--> %s\n", q->personagens[i]);
}

char* aloca_e_copia(char* string){
  char* copy = malloc(sizeof(char) * strlen(string) + 1);
  strcpy(copy, string);
  return copy;
}

//Cria um vetor de Comics e retorna para a função principal, bem como atualiza a variável tam com a quantidade de quadrinhos na base (tamanho do vetor)
Comic* carregar_Base(int* tam){
    Comic* vetor;
    char linha[1000];
    char* parte;
    char* perso;
    int i, cont;

    i = cont = *tam = 0;

    scanf("%d\n", tam);

    vetor = malloc(sizeof(Comic) * *tam);
        
    for(int i=0; i<*tam; i++){
      fgets(linha, 1000, stdin);

      //Pega o título
      parte = strtok(linha, "|");
      vetor[i].titulo = aloca_e_copia(parte);

      //Pega o número
      parte = strtok(NULL, "|");
      sscanf(parte, "%d", &vetor[i].num);

      //Pega a data
      parte = strtok(NULL, "|");
      sscanf(parte, "%d/%d", &vetor[i].date.mes, &vetor[i].date.ano);

      //Marca não lido
      vetor[i].lido = 0;

      //Pega os personagens. Aqui será usado um strtok no pedaço dos personagens, separando por "," para ir pegando de nome em nome e armazenando no vetor de strings do registro
      parte = strtok(NULL, ";");
      perso = strtok(parte, ",");
      vetor[i].personagens = NULL;

      while(perso != NULL){
        vetor[i].personagens = realloc(vetor[i].personagens, sizeof(char*) * cont + 1);
        vetor[i].personagens[cont] = aloca_e_copia(perso);
        cont++;
        perso = strtok(NULL, ",");
      }

      vetor[i].qtd_per = cont;
      cont=0;
    }
    //Retorna o vetor
    return vetor;
}

//Função para adicionar um quadrinho
Comic* adiciona_quadrinho(Comic* banco, int* tam){
    char title[500], personagem[100];
    int number;
    int j;
    Comic* aux;

    //Pega as informações necessárias
    printf("\nInsira o titulo do quadrinho: ");
    scanf(" %[^\n]", title);

    printf("\nInsira o numero do quadrinho: ");
    scanf("%d", &number);

    //Verifica se o quadrinho a ser inserido já existe
    aux = recupera_quadrinho(banco, *tam, title, number);

    //Se o quadrinho não existe...
    if(aux == NULL){
        //Aumenta o tamanho do vetor de quadrinhos em um, para caber o novo
        banco = realloc(banco, sizeof(Comic) * (*tam + 1));
        banco[*tam].titulo = aloca_e_copia(title);
        banco[*tam].num = number;
        banco[*tam].lido = 0;

        //Pede as novas informações
        printf("\nInsira a data de publicaocao (MM/AAAA): ");
        scanf("%d/%d", &banco[*tam].date.mes, &banco[*tam].date.ano);

        printf("\nQuantos personagens estao na revista? ");
        scanf("%d", &banco[*tam].qtd_per);
        banco[*tam].personagens = malloc(sizeof(char*) * banco[*tam].qtd_per);

        printf("Digite os personagens (um por linha):\n");
        for(j=0; j<banco[*tam].qtd_per; j++){
            scanf(" %[^\n]", personagem);
            banco[*tam].personagens[j] = aloca_e_copia(personagem);
        }

        //Ajusta o tamanho
        (*tam)++;
    }
    //Se já existe...
    else{
        printf("Quadrinho ja existe na base de dados!\n");
    }

    return banco;
}

//Função que recupera um quadrinho específico do vetor, verificando nome e titulo
Comic* recupera_quadrinho(Comic* banco, int tam, char* nome, int num){
    int i;
    Comic *temp = NULL;

    for(i=0; i<tam; i++){
        if(banco[i].num == num && strcmp(banco[i].titulo, nome) == 0){
          temp = &banco[i];
          break;
        }
    }

    return temp;
}

//Função que remove o quadrinho
Comic* remove_quadrinho(Comic* banco, int* tam){
    Comic* novo;
    //Variável achou marcará se o quadrinho foi encontrado na base ou não
    int i,j, ins, number, achou = 0;
    char title[100];

    //Cria um novo vetor de quadrinhos. A lógica que vamos usar é copiar todos os valores do vetor antigo para o novo, menos o quadrinho selecionado para remoção.
    novo = malloc(sizeof(Comic) * (*tam-1));

    //pega as informações
    printf("Digite o titulo do quadrinho a ser removido: ");
    scanf(" %[^\n]s", title);

    printf("Digite o numero do quadirnho a ser removido: ");
    scanf("%d", &number);

    //Procura o quadrinho
    for(i=0, ins=0; i<*tam; i++){
        //Se encontrar, marca na variável achou
        if(banco[i].num == number && strcmp(banco[i].titulo, title) == 0){
            achou = 1;
            free(banco[i].titulo);
            for(j=0; j<banco[i].qtd_per; j++)
                free(banco[i].personagens[j]);
        }
        //Se não for igual, copia para o novo vetor
        else{
            novo[ins].titulo = aloca_e_copia(banco[i].titulo);
            free(banco[i].titulo);

            novo[ins].num = banco[i].num;
            novo[ins].lido = banco[i].lido;
            novo[ins].date = banco[i].date;
            novo[ins].qtd_per = banco[i].qtd_per;
            novo[ins].personagens = malloc(sizeof(char *) * banco[i].qtd_per);

            for(j=0; j<banco[i].qtd_per; j++){
                novo[ins].personagens[j] = aloca_e_copia(banco[i].personagens[j]);
                free(banco[i].personagens[j]);
            }

            ins++;
        }
    }

    //Impressão de mensagem para o usuário
    if(achou == 0)
        printf("Quadrinho nao encontrado na base!\n");
    else
        printf("Remocao realizada com sucesso\n");

    //Libera memória do vetor antigo
    free(banco);
    //Atualiza para o novo tamanho
    *tam = ins;

    return novo;
}

//Função para consultar as informações de um quadrinho
void consulta_quadrinho(Comic* banco, int tam){
    Comic* aux;
    char title[1000];
    int number;

    //Pega as informações
    printf("Informe o titulo do quadrinho: ");
    scanf(" %[^\n]", title);

    printf("Informe o numero do quadrinho: ");
    scanf("%d", &number);

    //Busca o quadrinho
    aux = recupera_quadrinho(banco, tam, title, number);

    //Se não existir, imprime mensagem de erro
    if(aux == NULL){
        printf("Quadrinho nao encontrado na base de dados!\n");
    }
    //Se existir, imprime as informações do quadrinho
    else{
        printf("Informacoes do quadrinho:\n");
        imprime_quadrinho(aux);
    }
}

//Função para impressão de listas baseadas em um parâmetro e valor selecionados
//Perceba que o penúltimo parâmetro é void* para que possamos passar valores de tipos diferentes
//Dessa forma, essa função será usada para todas as listagens
void filtra_lista(Comic* banco, int tam, int param, void* valor){
    //Imprime verificará se algum quadrinho foi impresso
    int i, j, imprime = 0;
    int aux;
    int* vetor;
    char* texto;

    printf("\nLista de quadrinhos:\n");

    //Verifica qual foi o tipo de listagem solicitado
    switch(param){
        //Por ano
        case 1:
            //Converte o valor para inteiro
            aux = *((int*)valor);

            //Procura os quadrinhos que foram lançados naquele ano
            for(i=0; i<tam; i++)
                if(banco[i].date.ano == aux){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }

            break;
        //Por período
        case 2:
            //Converte o valor para um vetor
            vetor = (int*) valor;

            //Verifica os quadrinhos que foram lançados dentro do intervalo solicitado
            for(i=0; i<tam; i++){
                //Ano entre o intervalo
                if(banco[i].date.ano > vetor[1] && banco[i].date.ano < vetor[3]){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }
                //Se o ano é igual ao inicial
                else if(banco[i].date.ano == vetor[1]){
                    //Verifica se o mês é igual ou maior
                    if(banco[i].date.mes >= vetor[0]){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }
                //Se o ano é igual ao final
                else if(banco[i].date.ano == vetor[3]){
                    //Verifica se o mês é menor ou igual
                    if(banco[i].date.mes <= vetor[2]){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }
            }

            break;
        //Por título
        case 3:
            //Converte para string
            texto = (char*)valor;

            for(i=0; i<tam; i++){
                if(strcmp(banco[i].titulo, texto) == 0){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }
            }

            break;
        //Por personagem
        case 4:
            texto = (char*)valor;

            for(i=0; i<tam; i++)
                for(j=0; j<banco[i].qtd_per; j++){
                    if(strcmp(banco[i].personagens[j], texto) == 0){
                        imprime_quadrinho(&banco[i]);
                        imprime = 1;
                        printf("\n\n");
                    }
                }

            break;
        //Por status da leitura
        case 5:
            aux = *((int*)valor);

            for(i=0; i<tam; i++)
                if(banco[i].lido == aux){
                    imprime_quadrinho(&banco[i]);
                    imprime = 1;
                    printf("\n\n");
                }

            break;
    }

    //Se não houver nenhuma impressão, avisa que nenhum quadrinho foi encontrado de acordo com os parâmetros solicitados
    if(imprime == 0)
        printf("Nenhum quadrinho encontrado com os parametros de busca!\n\n");
}

//Função para marcar que um quadrinho foi lido
void marcar_leitura(Comic* banco, int tam){
    int i, number, achou = 0;
    char title[1000];
    Comic* quad;

    //Solicita as informações
    printf("Informe o titulo do quadrinho: ");
    scanf(" %[^\n]s", title);

    printf("Informa o numero do quadrinho: ");
    scanf("%d", &number);

    //Busca pelo quadrinho
    quad = recupera_quadrinho(banco, tam, title, number);

    if(quad != NULL){ 
      quad->lido = 1;
      printf("Marcacao feita com sucesso\n\n");
    }
    else printf("Quadrinho nao encontrado na base\n\n");
}