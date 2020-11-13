#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include "disjsets.h"

class Maze {
friend class MazeWidget;
friend class PathWidget;
public:
    Maze(int n);
    ~Maze();
    static void initWall(bool** &wall, int n);
private:
    int n;
    bool **wall;
    int **process;   // record of creation process
    std::stack<int> path;
    bool dfs(int x, int y);
};

#endif // MAZE_H
