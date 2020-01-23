/*

* Programa: Jogo Resta Um em linguagem C
* Autores: Gabriele Jandres, Maria Carolina Esteves e Victor Cardoso
* Universidade Federal do Rio de Janeiro
* Descrição: *********
* Data de criação: novembro de 2019
* Arquivo principal

*/

#include "Molde.h"
#include "Defs.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h> //essa linha deverá ser comentada para rodar no linux

int main(void){
        int linha1, coluna1, linha2, coluna2;
        int verificacao;
        char nome[60], **pointer, resp;
        int option, *opcao;
        double tempo;
        clock_t start, end;
        Jogador player;
        Jogador *ranking;
        FILE *pa;

        //ponteiro que será parâmetro da função menu_inicial
        opcao = (int *) malloc(sizeof(int));

        if(!opcao){
          printf("Erro ao alocar memoria. \n");
          return 1;
        }

        //ponteiro para o vetor de estruturas
        ranking = (Jogador *) malloc(5 * sizeof(Jogador));

        if(!ranking){
          printf("Erro ao alocar memoria. \n");
          return 1;
        }

        //ponteiro para ponteiro (tabuleiro)
        pointer = (char **) malloc(sizeof(char *));

        if(!pointer){
          printf("Erro ao alocar memoria. \n");
          return 1;
        }

        menu_inicial(nome, opcao);
        strcpy(player.nome, nome);

        INICIO:
        switch(*opcao){
            case 1:
                  start = clock();
                  option = menu(nome);
                  player.op = option;

                  //análise das opções do menu secundario
                  switch(option){
                    case 1:
                        pointer = piramide();
                        imprime_tabuleiro(pointer);
                        break;
                    case 2:
                        pointer = flecha();
                        imprime_tabuleiro(pointer);
                        break;
                    default:
                        pointer = tradicional();
                        imprime_tabuleiro(pointer);
                  }

                  //verificação se a área para o tabuleiro foi de fato alocada
                  if(!pointer){
                    return 1; //interrompe porque a alocação não ocorreu
                  }

                  //realizar um movimento de acordo com o tabuleiro escolhido e com as coordenadas indicadas

                  while(1){
                    printf("\n");
                    printf("Digite as coordenadas da peca que voce deseja mover: \n");
                    printf("\n");
                    printf("Digite a linha de origem: \n");
                    scanf("%d", &linha1); setbuf(stdin, NULL);
                    printf("Digite a coluna de origem: \n");
                    scanf("%d", &coluna1); setbuf(stdin, NULL);

                    printf("\n");
                    printf("Digite as coordenadas de onde voce deseja colocar a peca: \n");
                    printf("\n");
                    printf("Digite a linha de destino: \n");
                    scanf("%d", &linha2); setbuf(stdin, NULL);
                    printf("Digite a coluna de destino: \n");
                    scanf("%d", &coluna2); setbuf(stdin, NULL);

                    verificacao = verifica_movimento(pointer, linha1, coluna1, linha2, coluna2);
                    realiza_movimento(pointer, linha1, coluna1, linha2, coluna2, verificacao);
                    printf("\n");
                    imprime_tabuleiro(pointer);
                    //printf("Movimentos: %d\n", movimentos);

                    if(verifica_fim(pointer) == 0) {
                      if((option == 3 && movimentos == 31) || (option == 2 && movimentos == 16) || (option == 1 && movimentos == 15) ){
                          //se o usuário ganhar o jogo, guardo as informações no arquivo
                          printf("\n");
                          
                          end = clock();
                          tempo = ((float) 1000 * (end - start) / (double) (CLOCKS_PER_SEC)) / 60000;
                          player.tempo = tempo;
                          printf("\033[32mParabens %s , voce ganhou o jogo! \033[0m\n", nome);
                          pa = fopen("pontuacoes.txt", "a");

                          if(!pa) {
                            printf("Lamentamos mas ocorreu um erro ao abrir o arquivo.\n");
                            return 1;
                          }

                          fprintf(pa, "%s %.2f %d \n", player.nome, player.tempo, player.op);
                          printf("Foram gastos \033[32m %.2f \033[0m minutos para acabar o jogo \n", tempo);
                          fclose(pa);
                          break; //paro porque o jogo acabou     
                      }
                      else{
                        printf("\n");
                        printf("Infelizmente, nao ha mais movimentos. Voce quer tentar novamente? (S ou N) \n");
                        do{
                          scanf("%c", &resp);
                          if(toupper(resp) != 'S' && toupper(resp) != 'N'){
                            printf("\033[31mResposta invalida. Por favor, digite novamente. \033[0m\n");
                          }
                          else break;
                        } while(1);

                        if(toupper(resp) == 'S'){
                          goto INICIO;
                        }
                        else return 0;
                      }
                    }
                  }
                      break; //break do primeiro case 1

          case 2: //ranking
                      pa = fopen("pontuacoes.txt", "r");
                      char n2[60];
                      float f;
                      int opc;

                      if(!pa) {
                          printf("Lamentamos mas ocorreu um erro ao abrir o arquivo do ranking\n");
                          return 1;
                      }
                      else{ //leio do arquivo enquanto ainda houverem dados
  
                        int i = 0;

                        while(fscanf(pa, "%s %f %d", n2, &f, &opc) != EOF && i < 5){
                          strcpy((ranking + i)->nome, n2);
                          (ranking + i)->tempo = f;
                          (ranking + i)->op = opc;
                          i++;
                        }

                        printf("\n");
                        printf("\033[94m Confira o ranking dos %d melhores jogadores: \033[0m\n", i);
                        printf("\n");

                        if(i == 0)
                          printf("Ainda não existem records. \n");
                        else mostra_ranking(ranking, i);
                        fclose(pa);
                      }
                      break;

          default: //sair
              return 0; //encerro o programa
        }

        free(pointer);
        free(opcao);
        return 0;
    }
