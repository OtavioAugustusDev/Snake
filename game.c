#include <stdbool.h> // Definição de valores booleanos
#include <stdlib.h>  // Geração procedural de números
#include <string.h>  // Manipulação de caracteres
#include <stdio.h>   // Entrada e saída de dados
#include <ctype.h>   // Conversão e classificação de entrada
#include <time.h>    // Data e hora

// Inicializa uma constante para carregar o tamanho do mapa
#define CHUNKS 21

// Declara uma matriz com o nº de elementos contidos em CHUNKS
char map[CHUNKS][CHUNKS];

// Agrupa variáveis relacionadas com o jogador
struct Snake {
  int x, y, speed, size;
  bool crashed, ateAll;
  char avatar;
};

// Agrupa variáveis relacionadas com o mundo
struct World {
  int fruits, maxFruits, rounds;
  char path, wall, fruit;
};

// Inicializa as entidades
struct Snake snake;
struct World world;

// Chamado para gerar o mapa
void buildMap() {
  // Itera sobre o valor contido em CHUNKS
  for (int row = 0; row < CHUNKS; row++) {

    // Itera sobre o valor contido em CHUNKS para cada valor de COLUMN
    for (int column = 0; column < CHUNKS; column++) {

      // Constrói o mapa
      // Descobre se as coordenadas atuais são de extremidade
      // comparando seus valores com zero e com o tamanho do mapa
      bool isWorldBoundary =
      column == 0 || row == 0 ||
      column == (CHUNKS - 1) || row == (CHUNKS - 1);
      
      // Representa cada caractere da matriz com 'ladrilhos'
      // a depender das coordenadas do elemento
      map[row][column] = isWorldBoundary ? world.wall : world.path;
    }
  }
}


// Chamado para renderizar o mapa na tela
void renderMap(void) {
  // Apaga o quadro anterior
  system("clear");
  
  for (int column = 0; column < CHUNKS; column++) { // Eixo Y
    for (int row = 0; row < CHUNKS; row++) { // Eixo X

      // Renderiza o mapa em forma de matriz
      printf(" %c ", map[row][column]);
    }

    // Pula uma linha quando o eixo X atinge o valor de CHUNKS
    printf("\n");
  }
}


int main(void) {
  // Configura os parâmetros iniciais do jogador
  snake.x = CHUNKS / 2;
  snake.y = CHUNKS / 2;
  snake.speed = 1;
  snake.avatar = '@';
  snake.size = 0;
  snake.crashed = false;
  snake.ateAll = false;

  // Configura os parâmetros iniciais do mundo
  world.path = ' ';
  world.wall = '#';
  world.fruit = '*';
  world.fruits = 0;
  world.maxFruits = 10;
  world.rounds = 0;

  // Gera o mapa
  buildMap();

  // Define uma semente aleatória baseada na data
  srand(time(NULL));

  // Posiciona o jogador no mundo
  map[snake.x][snake.y] = snake.avatar;
  
  // Gera frutas
  while (world.fruits < world.maxFruits) {
    // Define coordenadas procedurais
    int randomColumn = rand() % CHUNKS;
    int randomRow = rand() % CHUNKS;

    // Descobre se as coordenadas geradas podem ser utilizadas
    bool isEmpty = map[randomColumn][randomRow] == world.path;

    // Gera e atualiza a quantidade de frutas presentes no mapa
    if (isEmpty) {
      map[randomColumn][randomRow] = world.fruit;
      world.fruits++;
    }
  }
  
  bool gameOver = false;
  while (!gameOver) {
    // Atualiza a posição do jogador
    map[snake.x][snake.y] = snake.avatar;
    
    renderMap(); // Renderiza o mapa com as novas entidades inseridas

    // Atua como interface de opções para o jogador
    printf("\n-------- CONTROLES --------\n");
    printf("\n");
    printf("Movimentação -> A W S D\n");
    printf("\n---------------------------\n");
    printf("\n");
    printf("Entrada: ");

    // Coleta a escolha do usuário
    char inputDir;
    scanf(" %c", &inputDir);

    // Normaliza o valor da entrada
    inputDir = tolower(inputDir);

    // Define as possíveis entradas e saídas
    char dir[] = {'a', 'd', 'w', 's'};
    int dx[] = {-1, 1,  0, 0};
    int dy[] = { 0, 0, -1, 1};

    // Descobre qual valor o usuário digitou
    for (int i = 0; i < strlen(dir); i++) {
      if (inputDir == dir[i]) {
        int newX = snake.x + dx[i] * snake.speed;
        int newY = snake.y + dy[i] * snake.speed;

        // Identifica se a posição pretendida é válida
        if (map[newX][newY] == snake.avatar || map[newX][newY] == world.wall)
          // Interrompe a execução
          snake.crashed = true;
        else {
          // Aplica a posição ao jogador
          snake.x = newX;
          snake.y = newY;
        }
        break;
        }
    }

    // Resolve a colisão do jogador com as frutas
    if (map[snake.x][snake.y] == world.fruit) {
      world.fruits--;
      snake.size++;

      snake.ateAll = world.fruits < 1;
    }

    // Incrementa a quantidade de rodadas jogadas
    world.rounds++;

    // Verifica se o jogo deve continuar
    gameOver = snake.crashed || snake.ateAll;
  };

  // Limpa a tela
  printf("\n");
  system("clear");

  // Limpa todas as entidades do mapa
  buildMap();

  // Exibe uma mensagem de fim de jogo
  char txt[] = "FIM";
  int center = CHUNKS / 2;
  for (int i = 0; i < strlen(txt); i++) map[center][center + (i - 1)] = txt[i];

  // Renderiza a mensagem de fim
  renderMap();

  // Exibe estatísticas de jogo
  printf("\n------ ESTATÍSTICAS ------\n");
  printf("\n");
  printf("Rodadas jogadas: %d\n", world.rounds);
  printf("Frutas encontradas: %d\n", snake.size);
  printf("\n---------------------------\n");

  // Finaliza o programa
  exit(EXIT_SUCCESS);
}