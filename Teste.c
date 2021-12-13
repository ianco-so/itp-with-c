//Função auxiliar que aloca o espaço para uma string copy e copia o valor de str para ela
char* aloca_e_copia(char* str){
  char* copy = malloc(sizeof(char) * strlen(str) + 1);
  strcpy(copy, str);
  return copy;
}

//Cria um vetor de Comics e retorna para a função principal, bem como atualiza a variável tam com a quantidade de quadrinhos na base (tamanho do vetor)
Comic* carregar_Base(int* tam){
    Comic* vetor;

    //Conjunto de variáveis auxiliares
    char linha[1000];
    char* parte;
    char* perso;
    int i, cont;

    //Inicializa o tamanho e cont com 0
    cont = *tam = 0;

   //Lê a quantidade de revistas da entrada
    scanf("%d\n", tam);

    //Aloca o vetor de revistinhas de tamanho tam
    vetor = malloc(sizeof(Comic) * *tam);
    
    //Para cada linha da entrada...    
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

      //Pega os personagens. Aqui será usado um strtok no pedaço dos personagens, 
      //separando por "," para ir pegando de nome em nome e armazenando no vetor de strings do registro
      parte = strtok(NULL, "\n");
      perso = strtok(parte, ",");
      vetor[i].personagens = NULL;

      while(perso != NULL){
        //Como ainda não sabemos o tamanho, vamos alocando uma linha por vez no vetor dos personagens
        vetor[i].personagens = realloc(vetor[i].personagens, sizeof(char*) * cont + 1);
        //Copia o valor do personagem na posição do vetor
        vetor[i].personagens[cont] = aloca_e_copia(perso);
        //Aumenta em um o contador do vetor de personagens
        cont++;
        //Pega o próximo personagem
        perso = strtok(NULL, ",");
      }

      //Atualiza a quantidade de personagens no registro
      vetor[i].qtd_per = cont;
      //Zera cont antes de ir para a próxima linha da entrada
      cont=0;
    }
    //Retorna o vetor
    return vetor;
}
```c
//Função que recupera um quadrinho específico do vetor, verificando nome e titulo
Comic* recupera_quadrinho(Comic* banco, int tam, char* nome, int num){
    int i;
    Comic *temp = NULL;

    //Se achar o quadrinho, armazena o endereço dele na variável temp
    for(i=0; i<tam; i++){
        if(banco[i].num == num && strcmp(banco[i].titulo, nome) == 0){
          temp = &banco[i];
          break;
        }
    }
    //Retorna o endereço do quadrinho ou NULL se não achar
    return temp;
}

//Função para adicionar um quadrinho
Comic* adiciona_quadrinho(Comic* banco, int* tam){
    //Variáveis auxiliares para ler dados necessários da entrada
    char title[500], personagem[100];
    int number;
    int j;
    Comic aux;

    //Pega as informações necessárias para procurar o quadrinho
    printf("\nInsira o titulo do quadrinho: ");
    scanf(" %[^\n]", title);
    printf("\nInsira o numero do quadrinho: ");
    scanf("%d", &number);

    //Verifica se o quadrinho a ser inserido já existe
    aux = recupera_quadrinho(banco, *tam, title, number);

    //Se o quadrinho não existe...
    if(aux == NULL){
        //Aumenta o tamanho do vetor de quadrinhos em um, para caber o novo quadrinho
        banco = realloc(banco, sizeof(Comic) * (*tam + 1));

        //Inicia a copiar os valores do quadrinho para o vetor
        banco[*tam].titulo = aloca_e_copia(title);
        banco[*tam].num = number;
        banco[*tam].lido = 0;

        //Pede as novas informações para completar o registro do quadrinho
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

    //Retorna o endereço do vetor de quadrinhos
    return banco;
}
```

int main(){
    Comic* quadrinhos = NULL;
    int qtd, op, subop;

    //Variáveis auxiliares para armazenar leituras da entrada
    int ano;
    int periodo[4];
    char title[500];

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

	//Lê a opção escolhida
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
	
		//Lê a opção de consulta do usuário
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
        }
    }while(op != 6);

    if(quadrinhos != NULL)
        free(quadrinhos);

    return 0;
}