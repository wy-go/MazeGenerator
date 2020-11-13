#include "disjsets.h"

/**
 * Construct the disjoint sets object.
 * n is the initial number of disjoint sets.
 */
DisjSets::DisjSets(int n) {
    par = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rank[i] = 0;
    }
}

/**
 * Destruct the disjoint sets object.
 */
DisjSets::~DisjSets() {
    delete par;
    delete rank;
}

/**
 * Perform a find with path compression.
 * Return the set containing x.
 */
int DisjSets::find(int x) {
    if (x != par[x]) {
        par[x] = find(par[x]);
    }
    return par[x];
}

/**
 * Link roots of two sets.
 * x and y are pointers to two distinct roots.
 */
void DisjSets::link(int x, int y) {
    if (rank[x] > rank[y]) {
        par[y] =x;
    } else {
        par[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
    }
}

/**
 * Union two disjoint sets with union by rank.
 * Assuming x and y are in distinct sets.
 */
void DisjSets::unionSets(int x, int y) {
    link(find(x), find(y));
}
