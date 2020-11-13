#include "maze.h"
using namespace std;

/**
 * Construct the maze object.
 * The maze has n by n cells.
 */
Maze::Maze(int n) {
    this->n = n;
    int m = 2 * n + 1;
    initWall(wall, n);
    DisjSets sets(n * n);    // initialiaze disjoint sets
    int count = n * n - 1;    // n * n - 1 times union
    process = new int*[count];
    srand(time(NULL));
    while (count) {    // loop until one set lefts
        int x = rand() % (m - 2) + 1;    // randomly generate x and y
        int y = rand() % (m - 2) + 1;    // from 1 to 2 * n - 1
        if ((x + y) % 2 == 1) {    // wall (not vertex)
            int p = (x - 1) / 2 * n + (y - 1) / 2;
            int q = p + (x % 2 == 1? 1 : n);
            if (sets.find(p) != sets.find(q)) {
                sets.unionSets(p, q);
                wall[x][y] = 0;
                count--;
                process[count] = new int[2];
                process[count][0] = x;
                process[count][1] = y;
            }
        }
    }
    bool ma[m][m];    // temporary copy to save wall
    for(int i = 0; i < m; i++) {
        memcpy(ma[i], wall[i], m);
    }
    dfs(1, 1);
    for(int i = 0; i < m; i++) {
        memcpy(wall[i], ma[i], m);
    }
    std::cout << n << '*' << n <<
                 " maze initialized" << std::endl;
    /*
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (wall[i][j]) cout << 1;
            else cout << 0;
        }
        std::cout << endl;
    }
    */
}

/**
 * Destruct the maze object.
 */
Maze::~Maze()
{
    delete *wall;
    delete *process;
}

/**
 * Initialize a bool matrix to a grid.
 */
void Maze::initWall(bool** &wall, int n) {
    int m = 2 * n + 1;
    wall = new bool*[m];
    for (int i = 0; i < m; i++) {
        wall[i] = new bool[m];
        if (i % 2 == 1) {
            for (int j = 0; j < m; j++)
                wall[i][j] = (j % 2 == 0);
        } else {
            memset(wall[i], 1, m);
        }
    }
}

/**
 * Depth-First backtracking recursive function.
 * Return true if (x, y) is on the path.
 */
bool Maze::dfs(int x, int y) {
    if (wall[x][y]) return 0;
    wall[x][y] = 1;    // mark reached cells
    if ((x + y) == 4 * n - 2 || dfs(x, y + 1) || dfs(x + 1, y)
    || dfs(x, y - 1) || dfs(x - 1, y)) {
        if ((x + y) % 2 == 0) path.push(x / 2 * n + y / 2 % n);  //save path into stack
        return 1;
    }
    return 0;
}
