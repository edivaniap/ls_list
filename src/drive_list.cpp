/**
* @file main.cpp
* @version 1.0  
* @title Driver List
* @brief Testador da ls::list
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

    assert( L1.size()  == 20 );
    assert( L1.front() == 10 );
    assert( L1.back()  == 10 );

    std::cout << "------ L1: \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 2
    L1.pop_back();
    L1.pop_front();

    assert( L1.size()  == 18 );
    assert( L1.front() == 9  );
    assert( L1.back()  == 9  );

    std::cout << "\n------ L1 (pop_back e pop_front): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 3
    L1.assign(4);
    assert( L1.back() == 4 and L1.front() == 4 );

    std::cout << "\n------ L1 ( assign(4) ): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 4
    L1.assign({5, 8, 3});

    std::cout << "\n------ L1 ( assign( {5, 8 , 3} ) ): \n";
    L1.print();
    std::cout << "front: " << L1.front() << "\n";
    std::cout << "back: " << L1.back() << "\n";


    //--------------- TESTE 5
    ls::list< int > L2;
    ls::list< int > L_aux = {0, 1, 2, 3};

    for( auto i(0) ; i < 10 ; ++i )
        L2.push_back( i+1 );

    std::cout<< "\n------ L2:\n";
    L2.print();
    std::cout<< "\n------ L_aux:\n";
    L_aux.print();
    std::cout<< "\n------ L2 assign L_aux:\n";
    L2.assign(L_aux.begin(), L_aux.end());

    L2.print();
    std::cout << "front: " << L2.front() << "\n";
    std::cout << "back: " << L2.back() << "\n";


    //--------------- TESTE 6
    ls::list<int> L3( L1 );
    std::cout << "\n------ L3 copy L1: \n";
    L3.print();
    std::cout << "front: " << L3.front() << "\n";
    std::cout << "back: " << L3.back() << "\n";
    assert( L3.size() == L1.size() );
    assert( L3.front() == L1.front() );
    assert( L3.back() == L1.back() );


    //--------------- TESTE 7 not working
    /*
    std::cout << "\n------ insert 8 na 4ª posicao de L3: \n";
    L3.insert(L3.begin(), 8);
    L3.print();
    */

    //--------------- TESTE 8
    ls::list<int> L4(L2.begin(), L2.end());
    std::cout << "\n------ L4 construido por L2 begin e end: \n";
    L4.print();
    assert( L4.size() == L2.size() );
    assert( L4.front() == L2.front() );
    assert( L4.back() == L2.back() );

     //--------------- TESTE 9
    ls::list<float> L5 = { 7.5, 3.1 , 1.1 };
    std::cout << "\n------ L5 construido por iList: \n";
    L5.print();
    assert( L5.size() == 3 );
    assert( L5.back() == 1.1f );
    assert( L5.front() == 7.5f );

    std::cout << "\n\n>>> Passou nos testes feitos...\n";

    return 0;
}
