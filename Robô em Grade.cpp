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
    std::vector<std::vector<unsigned long>> paths;
}graph;

typedef struct std::pair<int, int> coord;

std::vector<coord> stack;

std::vector<coord> adjList(graph* g, coord pos) {
    std::vector<coord> aux;
    
    if (!(pos.first + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first + 1][pos.second] != black) aux.push_back(std::make_pair(pos.first + 1, pos.second));    
    }
  
    if (!(pos.second + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first][pos.second + 1] != black) aux.push_back(std::make_pair(pos.first, pos.second + 1));
    }
    
    return aux;
}

int adjListLargeSearch(graph* g, coord pos) {

    if (!(pos.first + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first + 1][pos.second] != black) {
            stack.push_back(std::make_pair(pos.first + 1, pos.second));
            (g->state)[pos.first + 1][pos.second] = black;
        }
    }


    if (!(pos.second + 1 >= g->state[0].size())) {
        if ((g->state)[pos.first][pos.second + 1] != black) {
            stack.push_back(std::make_pair(pos.first, pos.second + 1));
            (g->state)[pos.first][pos.second + 1] = black;
        }
    }

 
    if (!(pos.first - 1 < 0)) {
        if ((g->state)[pos.first - 1][pos.second] != black) {
            stack.push_back(std::make_pair(pos.first - 1, pos.second));
            (g->state)[pos.first - 1][pos.second] = black;
        }    
    }

        
    if (!(pos.second - 1 < 0)) {
        if ((g->state)[pos.first][pos.second - 1] != black) {
            stack.push_back(std::make_pair(pos.first, pos.second - 1));
            (g->state)[pos.first][pos.second - 1] = black;
        }    
    }
    return 1;
}

int largeSearch(graph* g, coord pos) {
    // n == posicao final
    int n = g->state[0].size() - 1;
    
    // Remove ultima posicao da pilha
    stack.pop_back();
    // Pinta estado
    g->state[pos.first][pos.second] = black;

    // Verifica se está na ultima posicao
    if (pos == std::make_pair(n, n)) return 1;

    // Cria lista de adjacencia
    adjListLargeSearch(g, pos);

    if (stack.size() > 0) {
        return largeSearch(g, stack[stack.size() - 1]);
    }

    return 0;
}

/*
 *
 * flag => diz qual tipo de percurso é (1 = andar para cima e esquerda, 0 = andar somente para baixo e direita)
 * pos => posicao do vertice no grafo (linha == x, coluna == y)
 */
int deepSearch(graph* g, coord pos) {
    int n = g->state[0].size() - 1; // n == posicao final
    unsigned long result = 0, normalized = 0, max = (pow(2.0, 31.0) - 1);

    // pintaG
    g->state[pos.first][pos.second] = gray;

    std::vector<coord> list;
    // Monta lista de adjacencia
    list = adjList(g, pos);

    // x é a nova posicao para se mover
    for (coord x : list) {
        if (g->state[x.first][x.second] == gray) {
            result += g->paths[x.first][x.second];
        }
        else {
            result += deepSearch(g, x);
        }
    }
    normalized = result % max;
    g->paths[pos.first][pos.second] = normalized;
    return normalized;
}

int main()
{
    int n = 0, i = 0, j = 0;
    char aux;
    unsigned long result = 0, max = (pow(2.0, 31.0) - 1), normalized = 0;

    std::cin >> n;
    std::vector<std::vector<char>> map(n); // mapa
    std::vector<std::vector<int>> col(n); // cores dos vertices
    std::vector<std::vector<unsigned long>> paths(n, std::vector<unsigned long>(n,0)); // Caminhos possíveis até a saída

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
    g.paths = paths;
    g.paths[(unsigned long)n - 1][(unsigned long)n - 1] = 1; // Ultima posicao tem 1 caminho até ela mesma
    g.state[(unsigned long)n - 1][(unsigned long)n - 1] = gray; // Ultimo estado ja foi visitado
    
    
    stack.push_back(std::make_pair(0, 0));
    result = deepSearch(&g, std::make_pair(0, 0));
    /*  std::cout << g.state[4][4] << std::endl;
    std::cout << g.paths[4][4] << std::endl;*/
    if (result != 0) {
        normalized = result % max;
        std::cout << normalized << "\n";
    } else if(largeSearch(&g, std::make_pair(0,0)))
        std::cout << "THE GAME IS A LIE\n";
    else{
        std::cout << "INCONCEIVABLE\n";
    }
}