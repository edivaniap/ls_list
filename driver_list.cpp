#include <iostream>  // cout, endl
#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
#include <cstddef>   // std::ptrdiff_t
#include <exception> // out_of_range

namespace ls { // linear sequence
    /*!
     * A template class representing a biderectional iterator defines
     * over a dynamic array.
     *
     * \note
     * This iterator only works for traversing elements inside the same array.
     *
     * This class is incomplete and it is provided "as is".
     *
     * \date May, 2nd 2017.
     * \author Selan R. dos Santos
     */

    template <typename T>
    class MyBidirectionalIterator
    {
        // =============================================================
        // Some aliases to help writing a clearer code.
        // =============================================================
        public:
            using self_type = MyBidirectionalIterator;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            /*!
             * \brief std::ptrdiff_t is the signed integer type of the result of subtracting two pointers.
             *
             * std::ptrdiff_t is used for pointer arithmetic and array indexing,
             * if negative values are possible. Programs that use other types, such
             * as int, **may fail** on, e.g. 64-bit systems when the index exceeds
             * INT_MAX or if it relies on 32-bit modular arithmetic.
             *
             * When working with the C++ container library, the proper type for the
             * difference between iterators is the member typedef difference_type,
             * which is often synonymous with std::ptrdiff_t.
             * Only pointers to elements of the same array (including the pointer
             * one past the end of the array) may be subtracted from each other.
             */
            using difference_type = std::ptrdiff_t;
            /*!
             * Defines the category of an iterator.
             * Iterator category tags carry information that can be used
             * to select the most efficient algorithms for the specific
             * requirement set that is implied by the category.
             */
            using iterator_category = std::bidirectional_iterator_tag;

            // =============================================================
            // The raw pointer we want to encapsulate.
            // =============================================================
        private:
            T * m_ptr;
            //node_t * m_ptr;

            // =============================================================
            // Public interface that mimics the behaviour of a regular pointer.
            // =============================================================
        public:
            // Constructor
            MyBidirectionalIterator( T * ptr_ = nullptr )
                : m_ptr ( ptr_ )
            { /* empty */ }

            // Special methods. Default versions.
            ~MyBidirectionalIterator() = default;
            MyBidirectionalIterator( const self_type & ) = default;
            self_type & operator=( const self_type & ) = default;

            /*! The  *it operator.
             *  Supports: *it = XXXX or XXXX = *it.
             *  \return A reference to the object this iterator points to.
             */
            //node_t::value_type & operator*()
            const typename T::value_type & operator*() const
            {
                assert( m_ptr != nullptr );
                return m_ptr->data;
            }

            /*! The ++it operator.
             *  \return The calling object.
             */
            self_type operator++()
            {
                m_ptr = m_ptr->next;
                return *this;
            }

            /*! The it++ operator.
             *  \return The calling object.
             */
            self_type operator++(int)
            {
                self_type temp = *this;
                m_ptr = m_ptr->next;
                return temp;
            }

            /*! The --it operator.
             *  \return The calling object.
             */
            self_type operator--()
            {
                m_ptr = m_ptr->prev;
                return *this;
            }

            /*! The it-- operator.
             *  \return The calling object.
             */
            self_type operator--(int)
            {
                self_type temp = *this;
                m_ptr = m_ptr->prev;
                return temp;
            }

            /// The it == it2 operator.
            bool operator==( const self_type & rhs_ ) const
            {
                return m_ptr == rhs_.m_ptr;
            }

            /// The it != it2 operator.
            bool operator!=( const self_type & rhs_ ) const
            {
                return m_ptr != rhs_.m_ptr;
            }

            /// it += 3; // Go back  3 positions within the container. 
            self_type operator+=( difference_type step_ )
            {
                self_type temp = *this;
                while(step_ > 0 )
                {
                    m_ptr = m_ptr->next;
                    step_--;
                }
                return temp;
            }

            /// it -= 3; // Go back  3 positions within the container. 
            self_type operator-=(  difference_type step_ )
            {
                self_type temp = *this;
                while(step_ > 0 )
                {
                    m_ptr = m_ptr->prev;
                    step_--;
                }
                return temp;
            }

            /// it->method()
            pointer operator->( void ) const
            {
                assert( m_ptr );
                return *m_ptr;
            }
    };

    template < typename T >
    class list
    {
        //=== the data node.
        struct node_t
        {
            //=== Alias
            typedef T value_type; // using value_type = T;

            value_type data; // Tipo de informação a ser armazenada no container.
            node_t * next;
            node_t * prev;

            node_t( const T & d_= T() , node_t * n_ = nullptr, node_t * p_ = nullptr )
                : data ( d_ )
                , next ( n_ )
                , prev ( p_ )
            { /* empty */ }
        };

        //=== The iterator classes.
        public:
            using iterator = MyBidirectionalIterator< node_t >;
            using const_iterator = MyBidirectionalIterator< const node_t >;

        //=== Private members.
        private:
            size_t m_len;    // comprimento da lista.
            node_t * m_head; // nó cabeça.
            node_t * m_tail; // nó calda.

        public:
        //=== Special members
        // Default constructor
        list()
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            /*  Head & tail nodes.
             *     +---+    +---+   
             *     |   |--->|   |--+
             *     | H |    | T |  |
             *  +--|   |<---|   |  |
             *  |  +---+    +---+  |
             *  |                  |
             * ===                ===
             */
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

        // Copy constructor
        list( const list & clone_ )
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            m_head->next = m_tail;
            m_tail->prev = m_head;

            for ( auto it( clone_.cbegin() ) ; it != clone_.cend() ; ++it )
                push_back( *it );
        }

        list & operator= ( const list & clone_ )
        {
            //=== TODO
            //=== not working
            //limpa lista            
            clear();

            //copia de clone
            for ( auto it( clone_.cbegin() ) ; it != clone_.cend() ; ++it )
                push_back( *it );

            return *this;
        }

        //list( list && );
        //list & operator= ( list && );

        ~list()
        {
            clear();
            delete m_head;
            delete m_tail;
        }

        void clear( void )
        {
            node_t * temp = m_head;

            while( temp != m_tail )
            {
                node_t * condenado = temp;
                temp = temp->next;
                delete condenado;
            }

            delete temp;
        }

        void push_back( const T & value )
        {
            node_t * new_node = new node_t( value );
            
            new_node->next = m_tail;
            new_node->prev = m_tail->prev;

            m_tail->prev->next = new_node;
            m_tail->prev = new_node;

            m_len++;
        }

        void push_front( const T & value )
        {
            node_t * new_node = new node_t( value );
            
            new_node->next = m_head->next;
            new_node->prev = m_head;

            m_head->next->prev = new_node;
            m_head->next = new_node;

            m_len++;
        }


        //=== Public interface
        iterator begin()
        {
            return iterator( m_head->next );
        }

        const_iterator cbegin( void ) const
        {
            return const_iterator( m_head->next );
        }

        iterator end()
        {
            return iterator( m_tail );
        }

        const_iterator cend( void ) const
        {
            return const_iterator( m_tail );
        }

        int size( void ) const
        {
            return m_len;
        }

        bool empty( void ) const
        {
            return m_len == 0;
        }

        T & back( void )
        {
            if( empty() )
                throw std::out_of_range("[back()]: Cannot recover an element from an empty list!");
            return m_tail->prev->data;
        }

        T & front( void )
        {
            if( empty() )
                throw std::out_of_range("[front()]: Cannot recover an element from an empty list!");
            return m_head->next->data;
        }

        const T & back( void ) const
        {
            if( empty() )
                throw std::out_of_range("[back()]: Cannot recover an element from an empty list!");
            return m_tail->prev->data;
        }

        const T & front( void ) const
        {
            if( empty() )
                throw std::out_of_range("[front()]: Cannot recover an element from an empty list!");
            return m_head->next->data;
        }

        void pop_front( void )
        {
            if( empty() )
                throw std::out_of_range("[pop_front()]: Cannot delete an element from an empty list!");

            node_t * temp = m_head->next;

            temp->next->prev = m_head;
            m_head->next = temp->next;

            delete temp;
            m_len--;
        }

        void pop_back( void )
        {
            if( empty() )
                throw std::out_of_range("[pop_back()]: Cannot delete an element from an empty list!");

            node_t * temp = m_tail->prev;

            temp->prev->next = m_tail;
            m_tail->prev = temp->prev;

            delete temp;
            m_len--;
        }

        void assign(const T& value )
        {
            node_t * temp = m_head;

            while( temp != m_tail )
            {
                temp = temp->next;
                temp->data = value;
            }
        }

        template <class InItr >
        void assign( InItr first, InItr last )
        {
            node_t * temp = m_head;

            while( temp != m_tail && first != last )
            {
                temp = temp->next;
                temp->data = *(first++);
            }
        }

        void assign( std::initializer_list<T> ilist )
        {
            node_t * temp = m_head;
            auto i = 0u;

            while( temp != m_tail && i != ilist.size() )
            {
                temp = temp->next;
                temp->data = *(ilist.begin()+i);
                i++;
            }
        }

        void print()
        {
            node_t * temp = m_head->next;
            std::cout << ">>> [ ";
            while( temp != m_tail )
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << "], size: " << m_len << "\n";
        }

    };
}

// The vector/iterator driver.
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
