/**
* @file main.cpp
* @brief The list driver
* @author Edivânia Pontes
* @date 03/05/2017
*/

#include "list.hpp"

int main( void )
{
    //--------------- TESTE 1    
    ls::list< int > L1;

    assert( L1.empty() );

    //int test = L.front(); //testa out_of_range OK

    for( auto i(0) ; i < 10 ; ++i )
        L1.push_back( i+1 );


    for( auto i(0) ; i < 10 ; ++i )
        L1.push_front( i+1 );

    std::cout << "------ L1: \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 2
    L1.pop_back();
    L1.pop_front();

    std::cout << "\n------ L1 (pop_back e pop_front): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 3
    L1.assign(4);

    std::cout << "\n------ L1 ( assign(4) ): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 4
    L1.assign({0, 1, 2});

    std::cout << "\n------ L1 ( assign( {0, 1, 2} ) ): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 5
    ls::list< int > L2;

    for( auto i(0) ; i < 10 ; ++i )
        L2.push_back( i+1 );
    
    std::cout<< "\n------ L2:\n";
    L2.print();
    std::cout<< "\n------ L2 assign l1:\n";
    L2.assign(L1.begin(), L1.end());

    L2.print();
    std::cout << "front: " << L2.front() << "\n";
    std::cout << "back: " << L2.back() << "\n";


    //--------------- TESTE 6
    ls::list<int> L3( L1 );
    std::cout << "\n------ L3 copy L1: \n";
    L3.print();
    std::cout << "front: " << L3.front() << "\n";
    std::cout << "back: " << L3.back() << "\n";

    //--------------- TESTE 7 not working
    /*std::cout << "\n------ insert 8 na 4ª posicao de L3: \n";
    L3.insert(L3.begin(), 8);
    L3.print();*/

    return 0;
}
