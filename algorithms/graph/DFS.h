//
// Created by Anton on 23.06.2018.
//

#ifndef PROJECT_DFS_H
#define PROJECT_DFS_H


#include <vector>
#include "Graph.h"
#include <functional>
#include <stack>

class DFS {
public:

    explicit DFS(const Graph &g)
            : marked(g.getV(), false) {
        dfs(g);
    }

    DFS(const Graph &g, int s) :
            _s(s),
            marked(g.getV(), false) {
        validateVertex(s);
        marked.at(s) = true;
        visit(g, s);
    }

    void dfs(const Graph &g) {
        for(int u = 0; u < g.getV(); ++u) {
            if( !marked.at(u) ) {
                visit(g, u);
            }
        }
    }

    void visit(const Graph &g, int u) {
        for(auto v : g.getAdj().at(u) ) {
            if ( !marked.at(v) ) {
                visit(g, v);
            }
        }
        marked.at(u) = true;
    }

private:
    int _s;
    std::vector<int> marked;

    void validateVertex(int v) {
        if ( v < 0 || v >= marked.size() )
            throw std::logic_error("Invalid v. v must be between 0 and G.V");
    }
};


class CormenDFS {
public:
    enum class Marker : int {
        WHITE,
        GRAY,
        BLACK
    };

    explicit CormenDFS(const Graph &g) :
            _d(g.getV()),
            _f(g.getV()),
            _parent(g.getV()),
            _marked(g.getV(), Marker::WHITE) {
        dfs(g);
    }

    CormenDFS(const Graph &g, int s) :
            _s(s),
            _d(g.getV()),
            _f(g.getV()),
            _parent(g.getV()),
            _marked(g.getV(), Marker::WHITE) {
        visit(g, _s);
    }


    void dfs(const Graph &g) {
        for( int s = 0; s < g.getV(); ++s ) {
            if( _marked.at(s) == Marker::WHITE ) {
                visit(g, s);
            }
        }
    }

    void visit(const Graph &g, int u) {
        // Откраты белая вершина
        ++time;
        ++count;
        _d.at(u) = time;
        _marked.at(u) = Marker::GRAY;
        for( auto v : g.getAdj().at(u) ) {
            if ( _marked.at(v) == Marker::WHITE ) {
                _parent.at(v) = u;
                visit(g, v);
            }
        }
        //Закончили работу с текущей вершиной
        _marked.at(u) = Marker::BLACK;
        ++time;
        _f.at(u) = time;
    }

    const std::vector<int> &d() const {
        return _d;
    }

    const std::vector<int> &f() const {
        return _f;
    }

    const std::vector<int> &parent() const {
        return _parent;
    }

    const std::vector<Marker> &marked() const {
        return _marked;
    }

private:
    int time = 0;
    int _s; /// source vertex
    int count = 0; /// number of vertices reachable from source(s)
    std::vector<int> _d;
    std::vector<int> _f;
    std::vector<int> _parent;
    std::vector<Marker> _marked;

    void init(const Graph &g){
        _d = std::vector<int>(g.getV());
        _f = std::vector<int>(g.getV());
        _parent = std::vector<int>(g.getV());
        _marked = std::vector<Marker>(g.getV(), Marker::WHITE);
    }
};


inline std::vector<int> topologicalSort(const Graph &g) {
    std::list<int>     sorted;
    std::vector<bool>   marked(g.getV(), false);

    std::function<void(const Graph &, int)> visit = [&marked, &sorted, &visit](const Graph &g, int u) {
        marked.at(u) = true;
        for( auto v : g.getAdj().at(u) ) {
            if ( !marked.at(v)) {
                visit(g, v);
            }
        }
        sorted.push_front(u);
    };

    for( int s = 0; s < g.getV(); ++s ) {
        if( !marked.at(s) ) {
            visit(g, s);
        }
    }

    return std::vector<int>(sorted.begin(), sorted.end());
}


class DirectedCycle {
public:
    explicit DirectedCycle(const DirectedGraph &g) :
            marked(g.getV(), false),
            onStack(g.getV(), false),
            edgeTo(g.getV(), -1) {
        for( int u = 0; u < g.getV(); ++u ) {
            if( !marked.at(u) && cycle.empty() ) {
                dfs(g, u);
            }
        }
    }

    void dfs(const DirectedGraph &g, int u) {
        onStack.at(u) = true;
        marked.at(u) = true;

        for( auto v : g.getAdj().at(u) ) {
            if ( !cycle.empty() ) return;

            else if ( !marked.at(v) ) {
                edgeTo.at(v) = u;
                dfs(g, v);
            }

            else if ( onStack.at(v) ) { ///Cycle is found
                for(int x = u; x != v; x = edgeTo.at(x) ) {
                    cycle.push_back(x);
                }

                cycle.push_back(v);
                cycle.push_back(u);
                return;
            }
        }

        onStack.at(u) = false;
    }

    const std::vector<int> &getCycle() const {
        return cycle;
    }

private:
    std::vector<bool> marked;
    std::vector<bool> onStack;
    std::vector<int> cycle;
    std::vector<int> edgeTo;
};


#endif //PROJECT_DFS_H
