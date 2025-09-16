# Snake Game em C
<img width="1233" height="733" alt="Captura de tela 2025-09-16 181429" src="https://github.com/user-attachments/assets/2517670d-24e7-4e42-8fe7-67e6d517ec5b" />

Um jogo clássico Snake implementado em C, onde o objetivo é coletar todas as frutas espalhadas pelo mapa sem colidir com as paredes ou com o próprio corpo.

## Características

- **Mapa**: Grade 21x21 com bordas delimitadas
- **Objetivo**: Coletar todas as 10 frutas (`*`) espespalhadas aleatoriamente
- **Controles**: Movimentação com as teclas W, A, S, D
- **Fim de jogo**: Colisão com paredes (`#`) ou com o próprio corpo
- **Estatísticas**: Contador de rodadas e frutas coletadas

## Como Jogar

### Controles
- **W** - Mover para cima
- **A** - Mover para esquerda  
- **S** - Mover para baixo
- **D** - Mover para direita

### Elementos do Jogo
- `@` - Jogador (Snake)
- `*` - Fruta
- `#` - Parede
- ` ` - Espaço vazio

### Objetivo
Colete todas as 10 frutas espalhadas pelo mapa para vencer o jogo!

## Compilação e Execução

### Pré-requisitos
- Compilador GCC ou similar
- Sistema Unix/Linux (devido ao comando `system("clear")`)

### Compilar o jogo
```bash
gcc -o snake game.c
```

### Executar o jogo
```bash
./snake
```

## Estrutura do Código

### Principais Componentes

#### Estruturas de Dados
```c
struct Snake {
    int x, y;           // Posição no mapa
    int speed, size;    // Velocidade e tamanho
    bool crashed;       // Status de colisão
    bool ateAll;       // Coletou todas as frutas
    char avatar;       // Caractere de representação
};

struct World {
    int fruits;        // Frutas restantes
    int maxFruits;     // Total de frutas
    int rounds;        // Rodadas jogadas
    char path, wall, fruit; // Caracteres do mundo
};
```

#### Funções Principais
- `buildMap()` - Constrói o mapa com paredes nas bordas
- `renderMap()` - Renderiza o mapa na tela
- `main()` - Loop principal do jogo

### Configurações Padrão
- **Tamanho do mapa**: 21x21 (`CHUNKS`)
- **Frutas totais**: 10
- **Posição inicial**: Centro do mapa
- **Velocidade**: 1 célula por movimento

## Sistema de Estatísticas

Ao final do jogo, são exibidas:
- **Rodadas jogadas**: Número total de movimentos realizados
- **Frutas encontradas**: Quantidade de frutas coletadas

## Detalhes Técnicos

### Dependências
```c
#include <stdbool.h>  // Valores booleanos
#include <stdlib.h>   // Geração de números aleatórios
#include <string.h>   // Manipulação de strings
#include <stdio.h>    // Entrada/saída
#include <ctype.h>    // Conversão de caracteres
#include <time.h>     // Semente aleatória
```

### Geração de Frutas
- Utiliza `srand(time(NULL))` para semente aleatória
- Posiciona frutas apenas em espaços vazios
- Garante que todas as 10 frutas sejam colocadas

### Sistema de Colisão
- Detecta colisão com paredes (`#`)
- Detecta colisão com o próprio corpo (`@`)
- Interrompe o jogo imediatamente em caso de colisão

## Condições de Vitória/Derrota

### Vitória
- Coletar todas as 10 frutas do mapa

### Derrota
- Colidir com uma parede
- Colidir com o próprio corpo

## Limitações Conhecidas

**Compatibilidade**: Utiliza `system("clear")`, específico para sistemas Unix/Linux
