#include <iostream>
#include <typeinfo>
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"

void buildGraph(Graph &g) {
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(4, 2);
    g.addEdge(4, 5);
    g.addEdge(5, 5);
}

void testBFS();
void testDFS();
void testTopologicalSort();
void testDirectedCycle();

int main() {

    enum Algorithms {
        BFS,
        DFS,
        TOPOLOGICAL_SORT,
        DIRECTED_CYCLE
    };

    Algorithms alg = DIRECTED_CYCLE;

    switch (alg) {
        case BFS: {
            testBFS();
            break;
        }
        case DFS: {
            testDFS();
            break;
        }
        case TOPOLOGICAL_SORT: {
            testTopologicalSort();
            break;
        }
        case DIRECTED_CYCLE: {
            testDirectedCycle();
            break;
        }
    }

    return 0;
}

void testBFS() {
    Graph g(6);

    buildGraph(g);

    std::cout << g.toString() << std::endl;

    BFS bfs(g, 0);

    std::cout << "distance to 4: " << bfs.getDistTo(4) << std::endl;

    auto path = bfs.pathTo(4);

    std::cout << "path from 0 to 4: ";
    for ( auto v : path) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "path from 0 to 4: ";
    bfs.printPath(4);
}

void testDFS() {
    DirectedGraph g(6);

    buildGraph(g);

    std::cout << g.toString() << std::endl;

    CormenDFS dfs(g);

    std::cout << "finishing time: ";
    for(auto item : dfs.f()) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void testTopologicalSort () {
    DirectedGraph g(9);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 2);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);
    g.addEdge(6, 3);
    g.addEdge(8, 7);

    std::cout << g.toString() << std::endl;

    CormenDFS dfs(g);

    std::cout << "finishing time: ";
    for(auto item : dfs.f()) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout<< "topological sort result: ";
    auto res = topologicalSort(g);
    for( auto item : res ) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void testDirectedCycle() {
    DirectedGraph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.addEdge(4, 2);
    g.addEdge(4, 5);
    g.addEdge(5, 5);

    std::cout << g.toString() << std::endl;

    DirectedCycle dc(g);
    if( dc.getCycle().empty() ) {
        std::cout << "Cycle didn't find" << std::endl;
    } else {
        std::cout << "Cycle contains vertices: ";
        for (auto item : dc.getCycle() ) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

}