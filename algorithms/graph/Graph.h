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

struct Edge {
    using VertexType = size_t;

    Edge(VertexType u = 0, VertexType v = 0, double w = 0)
            : m_u(u),
              m_v(v),
              m_weight(w)
    {};

    std::string toString() const {
        std::ostringstream oss;
        oss << "( " << m_u << ", " << m_v << ", " << m_weight << " )";
        return oss.str();
    }

    VertexType u() const {
        return m_u;
    }

    VertexType v() const {
        return m_v;
    }

    double weight() const {
        return m_weight;
    }

    VertexType other(VertexType u) {
        if ( u == m_u ) { return m_v; }
        else if ( u == m_v ) { return m_u; }
        else throw std::invalid_argument("Edge::other invalid u");
    }
private:
    VertexType m_u;
    VertexType m_v;
    double m_weight;
};


class WeightedGraph {
public:
    using AdjListType = std::vector<std::list<Edge>>;

    WeightedGraph() = delete;

    explicit WeightedGraph(size_t n)
            : m_V(n),
              m_adj(n)
    {};

    WeightedGraph(const WeightedGraph &other) = default;

    virtual void addEdge(Edge e) {

        validateVertex(e.v());
        validateVertex(e.u());

        m_adj.at(e.u()).push_back(e);
        m_adj.at(e.v()).push_back(e);

        ++m_E;
//        ++m_V;
    }

    const AdjListType &adj() const { return m_adj; }

    int V() const { return m_V; }

    int E() const { return m_E; }

    void validateVertex(size_t v) const {
        if ( v >= m_V )
            throw std::logic_error("invalid v. Must be between 0 and " );
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> edges(m_V);

        for (Edge::VertexType v = 0; v < m_V; ++v) {
            int selfLoops = 0;
            for (auto e : m_adj.at(v)) {

                if (e.other(v) > v) {
                    edges.push_back(e);
                }
                    // add only one copy of each self loop (self loops will be consecutive)
                else if (e.other(v) == v) {
                    if (selfLoops % 2 == 0) edges.push_back(e);
                    selfLoops++;
                }
            }
        }

        return edges;
    }

    std::string toString() {
        std::ostringstream oss;

        for(int i = 0; i < m_adj.size(); ++i) {
            oss << "[" << i << "]=>";
            for(auto e : m_adj.at(i)) {
                oss << "(" << e.u() << " " << e.v() << "," << 0 << ") ";
            }
            oss << std::endl;
        }

        return oss.str();
    }

protected:
    size_t m_V;
    size_t m_E;
    AdjListType m_adj;
};



#endif //PROJECT_GRAPH_H
