//
// Created by Anton on 14.07.2018.
//

#ifndef PROJECT_METAFUNCTIONS_H
#define PROJECT_METAFUNCTIONS_H

template<int N>
struct Square {
    static const int value = N * N;
};

template <typename T>
struct AddPointer {
    typedef T* type;
};

template<int N>
struct Fact {
    static const int value = N * Fact<N - 1>::value;
};

template<>
struct Fact<0> {
    static const int value = 1;
};

constexpr int fact(int N) {
    return N != 0? N * fact(N - 1) : 1;
}

template<int N>
struct Fib {
    static const int value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<1> {
    static const int value = 1;
};

template<>
struct Fib<0> {
    static const int value = 0;
};

constexpr int fib(int N) {
    return N > 1 ? fib(N - 1) + fib(N - 2) : N == 1 ? 1 : 0;
}

#endif //PROJECT_METAFUNCTIONS_H
