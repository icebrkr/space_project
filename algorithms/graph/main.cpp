#include <iostream>
#include <typeinfo>
#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "MinimumSpanningTree.h"

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
void testKruskalMST();

int main() {

    enum Algorithms {
        BFS,
        DFS,
        TOPOLOGICAL_SORT,
        DIRECTED_CYCLE,
        KRUSKAL_MST
    };

    Algorithms alg = KRUSKAL_MST;

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
        case KRUSKAL_MST: {
            testKruskalMST();
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

void testKruskalMST() {
    WeightedGraph g(8);

    g.addEdge(Edge(0, 7, 0.16));
    g.addEdge(Edge(2, 3, 0.17));
    g.addEdge(Edge(1, 7, 0.19));
    g.addEdge(Edge(0, 2, 0.26));
    g.addEdge(Edge(5, 7, 0.28));
    g.addEdge(Edge(1, 3, 0.29));
    g.addEdge(Edge(1, 5, 0.32));
    g.addEdge(Edge(2, 7, 0.34));
    g.addEdge(Edge(4, 5, 0.35));
    g.addEdge(Edge(1, 2, 0.36));
    g.addEdge(Edge(4, 7, 0.37));
    g.addEdge(Edge(0, 4, 0.38));
    g.addEdge(Edge(6, 2, 0.40));
    g.addEdge(Edge(3, 6, 0.52));
    g.addEdge(Edge(6, 0, 0.58));
    g.addEdge(Edge(6, 4, 0.93));

    std::cout << g.toString() << std::endl;

    KruskalMST kruskalMST;

    auto mst = kruskalMST.makeMST(g);

    for (auto e : mst) {
        std::cout << e.toString() << std::endl;
    }
}