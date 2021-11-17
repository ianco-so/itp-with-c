#include <stdio.h>

int main() {
  
  int N, M, z1, z2, z3, z4, maiorX = 0, index = 0;

  scanf("%d %d", &N, &M);

  int pontoX[N], pontoY[N], cliqueX[M], cliqueY[M];
  char cliqueLetra[M];

  for(int i = 0; i < N; i++){
    scanf("%d %d", &pontoX[i], &pontoY[i]);
    if(maiorX < pontoX[i]){
      maiorX = i;
    }
  }

  for(int i = 0; i < M; i++){
    scanf(" %c %d %d", &cliqueLetra[i], &cliqueX[i], &cliqueY[i]);
  }

  for(int j = 0; j < M; j++){
    for(int i = 0; i < N; i ++){
      if(i == N-1){
        z1 = (pontoX[0] - pontoX[N-1])*(cliqueY[j] - pontoY[N-1]) - (pontoY[0] - pontoY[N-1])*(cliqueX[j] - pontoX[N-1]);
        z2 = (pontoX[0] - pontoX[N-1])*(cliqueY[j] - pontoY[N-1]) - (pontoY[0] - pontoY[N-1])*(cliqueX[maiorX] - pontoX[N-1]);
        z3 = (cliqueX[maiorX] - cliqueX[j])*(pontoY[N-1] - cliqueY[j]) - (cliqueY[j] - cliqueY[j])*(pontoX[N-1] - cliqueX[j]);
        z4 = (cliqueX[maiorX] - cliqueX[j])*(pontoY[0] - cliqueY[j]) - (cliqueY[j] - cliqueY[j])*(pontoX[0] - cliqueX[j]);
      } else{
        z1 = (pontoX[i+1] - pontoX[i])*(cliqueY[j] - pontoY[i]) - (pontoY[i+1] - pontoY[i])*(cliqueX[j] - pontoX[i]);
        z2 = (pontoX[i+1] - pontoX[i])*(cliqueY[j] - pontoY[i]) - (pontoY[i+1] - pontoY[i])*(cliqueX[maiorX] - pontoX[i]);
        z3 = (cliqueX[maiorX] - cliqueX[j])*(pontoY[i] - cliqueY[j]) - (cliqueY[j] - cliqueY[j])*(pontoX[i] - cliqueX[j]);
        z4 = (cliqueX[maiorX] - cliqueX[j])*(pontoY[i+1] - cliqueY[j]) - (cliqueY[j] - cliqueY[j])*(pontoX[i+1] - cliqueX[j]);
      }
      if((z1*z2) < 0 && (z3*z4) < 0){
        index++;
      }
    }
    if(index == N){
      printf("%c", cliqueLetra[j]);
    }
  }

  return 0;
}