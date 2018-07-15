//
// Created by Anton on 15.07.2018.
//

#ifndef PROJECT_MINIMUMSPANNINGTREE_H
#define PROJECT_MINIMUMSPANNINGTREE_H


#include <queue>
#include <algorithm>
#include <map>
#include "Graph.h"

class KruskalMST {
public:
    KruskalMST()
        : weight_(0){};

    std::vector<Edge> makeMST(const WeightedGraph &g) {
        std::map<size_t, std::set<Edge::VertexType>> vertexSets;

        for(size_t i = 0; i < g.V(); ++i) {
            std::set<Edge::VertexType> vset;
            vset.insert(i);
            vertexSets.insert(std::make_pair(i, vset));
        }

        auto edges = g.edges();

        auto edgesCompare = [](const Edge &a, const Edge &b) {return a.weight() < b.weight(); };
        std::sort(edges.begin(), edges.end(), edgesCompare);


        auto findSetId = [&vertexSets](Edge::VertexType u) -> size_t {
            for(auto& set : vertexSets) {
                if ( set.second.count(u) ) return set.first;
            }
        };

        for (auto e : edges) {
            auto uId = findSetId(e.u());
            auto vId = findSetId(e.v());

            if ( uId != vId ) {
                mst_.push_back(e);
                auto minId = std::min<size_t >(uId, vId);
                auto maxId = std::max<size_t >(uId, vId);

                vertexSets.at(minId).insert(vertexSets.at(maxId).begin(),
                                          vertexSets.at(maxId).end());

                vertexSets.erase(maxId);
            }
        }

        return mst_;
    }

    double weight() const { return weight_; }

private:
    double weight_;
    std::vector<Edge> mst_;
};


#endif //PROJECT_MINIMUMSPANNINGTREE_H
