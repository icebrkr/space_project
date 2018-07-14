
#ifndef PROJECT_TYPELIST_H
#define PROJECT_TYPELIST_H

template<typename... T>
struct TypeList{};

template <typename H, typename... T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
    static const int length = 1 + sizeof...(T);
};

template <>
struct TypeList<> {
    static const int length = 0;
};

template<int... Ints>
struct IntList{};

template <int H, int... T>
struct IntList<H, T...> {
    static const int Head = H;
    using Tail = IntList<T...>;
    static const int length = 1 + sizeof...(T);
};

template <>
struct IntList<> {
    static const int length = 0;
};

template<typename TL>
struct Length {
    static const int value = 1 + Length<typename TL::Tail>::value;
};

template<>
struct Length<TypeList<>> {
    static const int value = 0;
};

template<>
struct Length<IntList<>> {
    static const int value = 0;
};

template<typename H, typename TS>
struct Cons{};

template<typename H, typename... Types>
struct Cons<H, TypeList<Types...>> {
    using type = TypeList<H, Types...>;
};

template<typename TL1, typename TL2>
struct Concat{};

template<typename... Types1, typename... Types2>
struct Concat<TypeList<Types1...>, TypeList<Types2...>> {
    using type = TypeList<Types1..., Types2...>;
};

#endif //PROJECT_TYPELIST_H
