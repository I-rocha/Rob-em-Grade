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


std::vector<coord> adjList(graph* g, coord pos, int fg) {
    std::vector<coord> aux;
    
    
    if (!(pos.first + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first + 1][pos.second] == white) aux.push_back(std::make_pair(pos.first + 1, pos.second));    
    }

        
    if (!(pos.second + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first][pos.second + 1] == white) aux.push_back(std::make_pair(pos.first, pos.second + 1));
    }
    
    if (fg == 1) {
        if (!(pos.first - 1 < 0)) {
            if ((g->state)[pos.first - 1][pos.second] == white) aux.push_back(std::make_pair(pos.first - 1, pos.second));
        }

        if (!(pos.second - 1 < 0)) {
            if ((g->state)[pos.first][pos.second - 1] == white) aux.push_back(std::make_pair(pos.first, pos.second - 1));
        }
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
int deepSearch(graph* g, coord pos, int flag, unsigned long* result1, unsigned long* result2, int fg) {
    int n = g->state[0].size() - 1; // Ultima posicao

    //pintaG
    g->state[pos.first][pos.second] = gray;

    if (fg == 1 && (*result2) > 0) { return 0; }

    //Se encontrou saida
    if (pos == std::make_pair(n, n)) {
        if (!flag) (*result1)++;
        else (*result2)++;
        g->state[pos.first][pos.second] = white;
        return *result2;
    }


    std::vector<coord> list;
    // Monta lista de adjacencia
    list = adjList(g, pos, fg);

    // x é a nova posicao para se mover
    for (coord x : list) {

        //Se andou para tras ou para cima
        if ((x.first < pos.first) || (x.second < pos.second)) deepSearch(g, x, 1, result1, result2, fg);
        else deepSearch(g, x, flag, result1, result2, fg);
    }

    g->state[pos.first][pos.second] = white;
    return 0;
}

int main()
{
    int n = 0, i = 0, j = 0;
    char aux;
    unsigned long result1 = 0, result2 = 0, max = (pow(2.0, 31.0) - 1);
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

    deepSearch(&g, std::make_pair(0, 0), 0, &result1, &result2, 0);

    if (result1 != 0) {
        normalized_1 = result1 % max;
        std::cout << normalized_1;
    }
    deepSearch(&g, std::make_pair(0, 0), 0, &result1, &result2, 1);
    if ((result1 == 0) && (result2 != 0)) {
        std::cout << "THE GAME IS A LIE";
    }
    else if ((result1 == 0) && (result2 == 0)){
        std::cout << "INCONCEIVABLE";
    }
}