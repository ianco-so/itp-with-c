#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 20

//Enumeração representando itens do jogo
typedef enum item{
  cura = 1,
  dinheiro,
  escudo
}Tesouro;

//Enumeração representando as armadilhas
typedef enum trap{
  espinhos = 1,
  buraco,
  ladrao
}Armadilha;

//Tipo Personagem, contendo vida e ataque. Usado para definir os inimigos e parte do Jogador
typedef struct person{
  int life, attack;
} Personagem;

//Tipo Jogador. Contém um Personagem com informações de vida e ataque, além de uma posição x,y e informações de dinheiro (loot) e se está equipado com escudo ou não.
typedef struct player{
  Personagem person;
  int location[2];
  int escudo, loot;
}Jogador;

//Tipo de dado Sala, representa uma casa do mapa. Pode conter um personagem inimigo, um tesouro e/ou uma armadilha
typedef struct room{
  Personagem person;
  int tesouro;
  int armadilha;
} Sala;

//Verifica a entrada qual tipo de tesouro ou armadilha é
int verifica_tesouro_armadilha(char input[MAX_INPUT_LENGTH]){
  //Armadilha armadilha;
  //Tesouro tesouro;
  if(strcmp(input, "cura") == 0) {
    return cura;
  }
  else if(strcmp(input, "dinheiro") == 0) {
    return dinheiro;
  }
  else if(strcmp(input, "escudo") == 0) {
    return escudo;
  }
  else if(strcmp(input, "buraco") == 0) {
    return buraco;
  }
  else if(strcmp(input, "espinhos") == 0) {
    return espinhos;
  }
  else if(strcmp(input, "ladrao") == 0) {
    return ladrao;
  }
  else {
    return 0;
  }
}

//Função para formatar a entrada no formato "(x y) - L A" para "x y L A"
void formatar_entrada_personagem (char entrada[MAX_INPUT_LENGTH]) {
  char *p = NULL;
  p = strstr(entrada, "(");
  *p = ' ';
  p = strstr(entrada, ")");
  *p = ' ';
  p = strstr(entrada, "-");
  *p = ' ';
}

Personagem criarPersonagem (int life, int attack){
  Personagem person;
  person.life = life;
  person.attack = attack;
  return person;
}

Jogador criarJogador (int location[2], int life, int attack) {
  Jogador player;
  player.location[0] = location[0];
  player.location[1] = location[1];
  player.person = criarPersonagem(life, attack); //O jogador é um tipo de personagem
  player.escudo = 0;
  player.loot = 0;

  return player;
}

//Tipo de dado Mapa, representa o mapa do jogo. Contém um vetor de Salas, que representam as casas do mapa.
Sala ** cria_mapa(int n, int m, Jogador *player) {
  Sala **mapa;
  char input[MAX_INPUT_LENGTH];
  int location[2] = {0, 0}, life, attack;
  int I = 0, T = 0, A = 0; //I = Inimigo, T = Tesouro, A = Armadilha

  //Inicializa o mapa    
  mapa = (Sala **)malloc(n*sizeof(Sala *));
  for (int i = 0; i < n; i++) {
    mapa[i] = (Sala *)malloc(m*sizeof(Sala));
  }
  //Inicializa o mapa com as salas vazias
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      mapa[i][j].person = criarPersonagem(0, 0);
      mapa[i][j].tesouro = 0;
      mapa[i][j].armadilha = 0;
    }
  }

  //Ler os dados do Jogador
  location[0] = 0;
  location[1] = 0;
  fgets(input, MAX_INPUT_LENGTH, stdin);
  input[strlen(input)-1] = '\0';
  formatar_entrada_personagem(input);
  sscanf(input, "%d %d %d %d", &location[0], &location[1], &life, &attack);
  location[0]--;
  location[1]--;
  *player = criarJogador(location, life, attack);
  /*
  Inserir os dados do Jogador no mapa
  //mapa[player->location[0]][player->location[1]].person = player->person;
  */

  //Ler informações do mapa
  scanf("%d %d %d", &I, &T, &A);
  getchar();

  /*Ler informações de todas as salas*/
  //Ler informacoes dos inimigos
  for (int i = 0; i < I; i++) {
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strlen(input)-1] = '\0';
    formatar_entrada_personagem(input);
    sscanf(input, "%d %d %d %d", &location[0], &location[1], &life, &attack);
    mapa[location[0]-1][location[1]-1].person = criarPersonagem(life, attack);
  }

  //Ler informações dos tesouros
  for (int i = 0; i < T; i++) {
    scanf("%s %d %d", input, &location[0], &location[1]);
    getchar();
    mapa[location[0]-1][location[1]-1].tesouro = verifica_tesouro_armadilha(input);
    //printf("Tesuro: %d | %d %d\n", mapa[location[0]-1][location[1]-1].tesouro, location[0]-1, location[1]-1);
  }

  //Ler informações das armadilhas
  for (int i = 0; i < A; i++) {
    scanf("%s %d %d", input, &location[0], &location[1]);
    getchar();
    mapa[location[0]-1][location[1]-1].armadilha = verifica_tesouro_armadilha(input);
    //printf("Armadilha: %d | %d %d\n", mapa[location[0]-1][location[1]-1].armadilha, location[0]-1, location[1]-1);
  }

  return mapa;
}

int executa_passo(int n, int m, Sala **mapa, char passo, Jogador *player) {
  switch (passo) {
    case 'W':
      if (player->location[0] > 0) {
        player->location[0]--;
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]+1);
      } else {
        printf("Avancando para %d, %d...\n", player->location[0]-1+1, player->location[1]+1);
        printf("Movimento Ilegal!\n");
      }
      break;
    case 'S':
      if (player->location[0] < n-1) {
        player->location[0]++;
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]+1);
      } else {
        printf("Avancando para %d, %d...\n", player->location[0]+1+1, player->location[1]+1);
        printf("Movimento Ilegal!\n");
      }
      break;
    case 'A':
      if (player->location[1] > 0) {
        player->location[1]--;
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]+1);
      } else {
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]-1+1);
        printf("Movimento Ilegal!\n");
      }
      break;
    case 'D':
      if (player->location[1] < m-1) {
        player->location[1]++;
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]+1);
      } else {
        printf("Avancando para %d, %d...\n", player->location[0]+1, player->location[1]+1+1);
        printf("Movimento Ilegal!\n");
      }
      break;
    default:
      return 1;
      break;
  }

  //Verifica se há inimigos na sala
  if (mapa[player->location[0]][player->location[1]].person.life > 0) printf("Um inimigo!!!\n");
  while(mapa[player->location[0]][player->location[1]].person.life > 0) {
    printf("Jogador ataca!\n");
    printf("Dano de %d\n", player->person.attack);
    mapa[player->location[0]][player->location[1]].person.life -= player->person.attack;
    printf("Vida do inimigo: %d\n", mapa[player->location[0]][player->location[1]].person.life);
    if (mapa[player->location[0]][player->location[1]].person.life <= 0) {
      break;
    } else if (player->escudo == 1) {
      printf("Defendeu o golpe!\n");
      player->escudo = 0;
      continue;
    }
    printf("Inimigo ataca!\n");
    printf("Dano de %d\n", mapa[player->location[0]][player->location[1]].person.attack);
    player->person.life -= mapa[player->location[0]][player->location[1]].person.attack;
    printf("Vida do jogador: %d\n", player->person.life);
    if (player->person.life <= 0) {
      return -1;
    }
  }

  //Verifica se há tesouro na sala	
  if (mapa[player->location[0]][player->location[1]].tesouro > 0) {
    printf("Um tesouro!\n");
    switch (mapa[player->location[0]][player->location[1]].tesouro) {
      case cura:
        player->person.life += 10;
        printf("Jogador coleta: pocao de cura!\n");
        break;
      case dinheiro:
        player->loot += 10;
        printf("Jogador coleta: dinheiro!\n");
        break;
      case escudo:
        player->escudo = 1;
        printf("Jogador coleta: um escudo!\n");
        break;
      default:
        break;
    }
    mapa[player->location[0]][player->location[1]].tesouro = 0;
  }
  //Verifica se há armadilha na sala
  if (mapa[player->location[0]][player->location[1]].armadilha > 0) {
    printf("Armadilha: ");
    switch (mapa[player->location[0]][player->location[1]].armadilha) {
      case espinhos:
        printf("espinhos! Jogador se machuca!\n");
        player->person.life -= 5;
        if (player->person.life <= 0) {
          return -1;
        }
        break;
      case buraco:
        printf("buraco! Jogador se machuca!\n");
        player->person.life -= 10;
        if (player->person.life <= 0) {
          return -1;
        }
        break;
      case ladrao:
        printf("ladrao! Jogador perde dinheiro!\n");
        player->loot -= 10;
        break;
      default:
        break;
    }
    mapa[player->location[0]][player->location[1]].armadilha = 0;
  }
  return 0;
}

void  imprime_status_personagem(Jogador player) {
  int dinheiro = (abs(player.loot) + player.loot) / 2;
  printf("Terminou na posicao (%d, %d)\n", player.location[0]+1, player.location[1]+1);
  printf("Vida: %d\n", player.person.life);
  printf("Dinheiro: %d\n", dinheiro);
}

//Função principal
int main(){
  int n, m, movimentos, res;
  char passo;
  Jogador player;
  Sala** mapa = NULL;

  //Leitura do tamanho do mapa
  scanf("%d %d", &n, &m);
  getchar();
  //Função que cria o mapa e inicializa o Jogador de acordo com os dados da entrada
  mapa = cria_mapa(n, m, &player);
  if (mapa != NULL) {
    printf("Mapa inicializado!\n");
    printf("Jogador na posicao %d,%d\n", player.location[0]+1, player.location[1]+1);
  } else {
    printf("Erro ao inicializar o mapa!\n");
    return 0;
  }

  //Leitura dos movimentos da simulação
  scanf("%d", &movimentos);
  //getchar();
  //Para cada movimento do jogador...
  for(int i=0; i<movimentos; i++){
    //Lê o movimento
    scanf(" %c", &passo);

    //Executa a simulação do passo. Se o retorno for -1, o jogador morreu e encerra a simulação
    res = executa_passo(n, m, mapa, passo, &player);
    if(res == -1) break;
  }
  
 
  //Testa pra ver se o jogador terminou vivo
  res < 0 ? printf("You died...\n"): printf("Vitoria!\n");

  //Imprime as informações finais do jogador
  imprime_status_personagem(player);
  return 0;
}