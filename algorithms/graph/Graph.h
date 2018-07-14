//
// Created by Anton on 23.06.2018.
//

#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <vector>
#include <list>
#include <stdexcept>
#include <set>
#include <sstream>
#include <string>


struct Edge {
    Edge(int ui = 0, int vi = 0, int w = 0) : u(ui), v(vi), weight(w) {};

    std::string toString() const {
        std::ostringstream oss;
        oss << "( " << v << ", " << weight << " )";
        return oss.str();
    }

    int u;
    int v;
    int weight;

private:

};

class Graph {
public:
    explicit Graph(int n) : V(n), adj(n) {};

    Graph(const Graph &other) = default;

    virtual void addEdge(int u,int v) {
        validateVertex(u);
        validateVertex(v);

        if( !contains(u, v) ) {
            adj.at(u).push_back(v);
            adj.at(v).push_back(u);
        }

        ++E;
    }

    bool contains(int u, int v) const {
        validateVertex(u);
        validateVertex(v);

        for(auto i : adj.at(u)) {
            if (i == v) return true;
        }

        return false;
    }

    const std::vector<std::list<int>> &getAdj() const { return adj; }

    int getV() const { return V; }

    int getE() const { return E; }

    void validateVertex(int v) const {
        if ( v < 0 || v >= V )
            throw std::logic_error("invalid v. Must be between 0 and " );
    }

    std::string toString() {
        std::ostringstream oss;

        for(int i = 0; i < adj.size(); ++i) {
            oss << "[" << i << "]=>";
            for(auto v : adj.at(i)) {
                oss << "(" << v << "," << 0 << ") ";
            }
            oss << std::endl;
        }

        return oss.str();
    }

protected:
    int V;
    int E;
    std::vector<std::list<int>> adj;
};


class DirectedGraph : public Graph {
public:
    using Graph::Graph;

    void addEdge(int u, int v) override {
        validateVertex(u);
        validateVertex(v);

        adj.at(u).push_back(v);

        ++E;
    }

    DirectedGraph reverse() {
        DirectedGraph g(V);

        for(int u = 0; u < V; ++u) {
            for( auto v : adj.at(u) ) {
                g.addEdge(v, u);
            }
        }

        return g;
    }
};


#endif //PROJECT_GRAPH_H
