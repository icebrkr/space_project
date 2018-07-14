//
// Created by Anton on 23.06.2018.
//

#ifndef PROJECT_BFS_H
#define PROJECT_BFS_H


#include <vector>
#include <stdexcept>
#include <queue>
#include <string>
#include <iostream>
#include "Graph.h"

class BFS {
public:
    BFS(const Graph &g, int s)
            : _s(s),
              distTo(g.getV(), 0),
              marked(g.getV(), false),
              parent(g.getV(), -1)
    {
        validate(s);

        bfs(g, s);
    }

    void bfs(const Graph &g, int s) {
        distTo.at(s) = 0;
        marked.at(s) = true;

        std::queue<int> q;
        q.push(s);
        while ( !q.empty() ) {
            int u = q.front();
            q.pop();
            for(auto v : g.getAdj().at(u) ) {
                if ( !marked.at(v) ) {
                    parent.at(v) = u;
                    distTo.at(v) = distTo.at(u) + 1;
                    marked.at(v) = true;

                    q.push(v);
                }
            }
        }
    }

    std::vector<int> pathTo(int v) {
        validate(v);
//        validate(s);


        int n = distTo.at(v);
        std::vector<int> path(n);
        int i = n - 1;
        for(int x = v; distTo.at(x) > 0; x = parent.at(x) ) {
            path.at(i) = parent.at(x);
            --i;
        }

        return path;
    }

    void printPath(int v) {
        validate(_s);
        validate(v);

        if( _s == v ) {
            std::cout << _s << " ";
        } else if ( parent.at(v) == -1 ) {
            std::cout << "Path from s to v is absent";
        } else {
            printPath( parent.at(v) );
            std::cout << v << " ";
        }
    }

    int getDistTo(int v) {
        validate(v);
        return distTo.at(v);
    }

private:
    int _s;
    std::vector<int> distTo;
    std::vector<bool> marked;
    std::vector<int> parent;

    void validate(int s) {
        if ( s < 0 || s >= distTo.size() )
            throw std::logic_error("invalid s. Must be between 0 and ");
    }
};


#endif //PROJECT_BFS_H
