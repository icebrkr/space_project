#include <iostream>
#include "metafunctions.h"
#include "TypeList.h"
#include <typeinfo>

using namespace std;

int main() {

    /// Test Math metafunction
    cout << "Square<9> = " <<  Square<9>::value << endl;
    cout << "Fact<3> = " << Fact<3>::value << endl;
    cout << "fact(4) = " << fact(4) << endl;
    cout << "Fib<10> = " << Fib<10>::value << endl;
    cout << "fib(10) = " << fib(10) << endl;

    /// Test Type lists
    using types = TypeList<int, double, char>;

//    cout << typeid(typename types::Head).name() << " "
//         << typeid(typename types::Tail::Head).name() <<  endl;
    cout << sizeof(types::Head) << endl;
    cout << typeid(types::Head()).name() << endl;
    cout << typeid(types::Tail::Head()).name() << endl;

    using ints = IntList<2, 3, 5, 6, 2 ,3>;
    cout << ints::Head << " " <<ints::Tail::Head << endl;

    cout << "Length<TypeList<int, double, char>> = " << Length<types>::value << endl;
    cout << "IntList<2, 3, 5, 6, 2 ,3> = " << Length<ints>::value << endl;

    /// Test operation with Type lists
    using list = TypeList<int, double, char, bool>;
    using adjList = Cons<int, list>::type;
    cout << adjList::length << endl;

    using concatList = Concat<adjList, list>::type;
    cout << concatList::length << endl;


    return 0;
}