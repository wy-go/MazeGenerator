#ifndef DISJSETS_H
#define DISJSETS_H

class DisjSets {
public:
    DisjSets(int n);
    ~DisjSets();
    int find(int x);
    void unionSets(int x, int y);
private:
    int *par;
    int *rank;
    void link(int x, int y);
};

#endif // DISJSETS_H
