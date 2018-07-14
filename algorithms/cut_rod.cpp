
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using PriceType = int;

int recursiveCutRod(const std::vector<int> &p);
int recursiveCutRod(const std::vector<int> &p, int n);
int memorizedCutRod(const std::vector<int> &p, size_t n);
int auxMemorizedCutRod(const std::vector<int> &p, size_t n, std::vector<int> &r);

int main() {

    std::vector<int> p;
    p = std::vector<int>{1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//    p = std::vector<int>{1, 5, 8, 9};
    int q;
    q = recursiveCutRod(p, p.size());
    std::cout << q << std::endl;

    q = memorizedCutRod(p, p.size());
    std::cout << q << std::endl;

    return 0;
}

int recursiveCutRod(const std::vector<int> &p) {
    return recursiveCutRod(p, p.size());
}

int recursiveCutRod(const std::vector<int> &p, int n) {
    if ( n  == 0 ) {
        return 0;
    }
//    int q = (unsigned int)-1 >> 1;
    int q = std::numeric_limits<int>::min();
    for(size_t i = 1; i <= n; ++i) {
        int r = p.at(i - 1) + recursiveCutRod(p, n - i);
        q = std::max(q, r);
    }

    return q;
}

int auxMemorizedCutRod(const std::vector<int> &p, size_t n, std::vector<int> &r) {
    if ( r.at(n) >= 0 ) return r.at(n);
    if ( n == 0 ) {
        return 0;
    }

    int q = std::numeric_limits<int>::min();
    for(size_t i = 1; i <= n; ++i) {
        int res = p.at(i - 1) + auxMemorizedCutRod(p, n - i, r);
        q = std::max<int>(q, res);
    }

    return q;
}

int memorizedCutRod(const std::vector<int> &p, size_t n) {
    std::vector<int> r(n + 1, std::numeric_limits<int>::min());
    return auxMemorizedCutRod(p, n, r);
}