#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

#define white -1
#define gray 0
#define black 1


typedef struct {
    std::vector<std::vector<char>> area;
    std::vector<std::vector<int>> state; //Se foi ou nao visitado
}graph;

typedef struct std::pair<int, int> coord;


std::vector<coord> adjList(graph* g, coord pos) {
    std::vector<coord> aux;
    
    if (!(pos.first + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first + 1][pos.second] == white) aux.push_back(std::make_pair(pos.first + 1, pos.second));    
    }
  
    if (!(pos.second + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first][pos.second + 1] == white) aux.push_back(std::make_pair(pos.first, pos.second + 1));
    }
    
    return aux;
}

std::vector<coord> adjListLargeSearch(graph* g, coord pos) {
    std::vector<coord> aux;


    if (!(pos.first + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first + 1][pos.second] == white) {
            aux.push_back(std::make_pair(pos.first + 1, pos.second));
            (g->state)[pos.first + 1][pos.second] = gray;
        }
    }


    if (!(pos.second + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first][pos.second + 1] == white) {
            aux.push_back(std::make_pair(pos.first, pos.second + 1));
            (g->state)[pos.first][pos.second + 1] = gray;
        }
    }

 
    if (!(pos.first - 1 < 0)) {
        if ((g->state)[pos.first - 1][pos.second] == white) {
            aux.push_back(std::make_pair(pos.first - 1, pos.second));
            (g->state)[pos.first - 1][pos.second] = gray;
        }    
    }

        
    if (!(pos.second - 1 < 0)) {
        if ((g->state)[pos.first][pos.second - 1] == white) {
            aux.push_back(std::make_pair(pos.first, pos.second - 1));
            (g->state)[pos.first][pos.second - 1] = gray;   
        }    
    }
    return aux;
}

int largeSearch(graph* g, coord pos) {
    // n == posicao final
    int n = g->state[0].size() - 1;
    std::vector<coord> adj;
    
    // Pinta estado
    g->state[pos.first][pos.second] = black;

    // Verifica se está na ultima posicao
    if (pos == std::make_pair(n, n)) return 1;

    // Cria lista de adjacencia
    adj = adjListLargeSearch(g, pos);

    // Percorre toda a vizinhança
    for (coord x : adj) {

        // Se encontrar um caminho retorna
        if (largeSearch(g, x)) return 1;
    }


    return 0;
}

/*
 *
 * flag => diz qual tipo de percurso é (1 = andar para cima e esquerda, 0 = andar somente para baixo e direita)
 * pos => posicao do vertice no grafo (linha == x, coluna == y)
 */
int deepSearch(graph* g, coord pos, int flag, unsigned long* result) {
    int n = g->state[0].size() - 1; // n == posicao final

    //pintaG
    g->state[pos.first][pos.second] = gray;

    //Se encontrou saida
    if (pos == std::make_pair(n, n)) {
       (*result)++;
    }

    std::vector<coord> list;
    // Monta lista de adjacencia
    list = adjList(g, pos);

    // x é a nova posicao para se mover
    for (coord x : list) {

        deepSearch(g, x, flag, result);
    
    }

    g->state[pos.first][pos.second] = white;
    return 0;
}

int main()
{
    int n = 0, i = 0, j = 0;
    char aux;
    unsigned long result = 0, max = (pow(2.0, 31.0) - 1);
    int normalized_1 = 0, normalized_2 = 0;

    std::cin >> n;
    std::vector<std::vector<char>> map(n); // mapa
    std::vector<std::vector<int>> col(n); // cores dos vertices


    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cin >> aux;
            map[i].push_back(aux);
            if (aux == '#')col[i].push_back(black);
            else col[i].push_back(white);

        }
    }
    graph g;
    g.area = map;
    g.state = col;

    deepSearch(&g, std::make_pair(0, 0), 0, &result);

    if (result != 0) {
        normalized_1 = result % max;
        std::cout << normalized_1;
    } else if(largeSearch(&g, std::make_pair(0,0)))
        std::cout << "THE GAME IS A LIE";
    else{
        std::cout << "INCONCEIVABLE";
    }
}