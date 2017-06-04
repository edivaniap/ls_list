/**
* @file list.hpp
* @version 1.0  
* @title Class List
* @brief Classe para lista duplamente encadeada genérica
* @author Edivânia Pontes
* @date 03/06/2017
*/

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // cout, endl
#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
#include <cstddef>   // std::ptrdiff_t
#include <string>
#include "myiterator.hpp"

namespace ls         // linear sequence
{
    template <typename T>
    class list 
    {        
    private:
        struct node_t
        {

            typedef T value_type;

            value_type data; //<! Data field
            node_t * next;   //<! Pointer to the next node in the list
            node_t * prev;   //<! Pointer to the previous node in the list

            //<! Basic constructor
            node_t( const T & d_= T() , node_t * n_ = nullptr, node_t * p_ = nullptr )
                : data ( d_ )
                , next ( n_ )
                , prev ( p_ )
            { /* empty */ }
        };

        size_t   m_len; //<! size of list
        node_t *m_head; //<! head of list       
        node_t *m_tail; //<! tail of list
        
    public:
        using iterator = MyBidirectionalIterator< node_t >;
        using const_iterator = MyBidirectionalIterator< const node_t >;

        /*!
         * @brief Default constructor that creates an empty list
         */
        list()
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

        /*!
         * @brief Copy constructor. Constructs the list with the deep copy of the contents of clone_
         * @param clone_ List that will be copied
         */  
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

        /*!
         * @brief Constructs the list with the contents of the range [first, last)
         * @param first Points to the first element of the range
         * @param last Points to tthe end mark of the range
         */
        template< typename InputIt >
        list( InputIt first, InputIt last )
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            m_head->next = m_tail;
            m_tail->prev = m_head;

            while( first != last )
                push_back( *first++ );
        }

        /*!
         * @brief Constructs the list with the contents of the initializer list ilist
         * @param ilist An initializer list
         */
        list( std::initializer_list<T> ilist )
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            m_head->next = m_tail;
            m_tail->prev = m_head;

            for(auto i = 0u; i < ilist.size(); i++ )
                push_back( *(ilist.begin()+i) );
        }

         /*!
         * @brief Destructs the list. The destructors of the elements are called and the used storage is deallocated
         */
        ~list()
        {
            clear();
            delete m_head;
            delete m_tail;
        }

        /*!
         * @brief Remove (either logically or physically) all elements from the container
         */
        void clear( void )
        {
            node_t * temp = m_head;

            while( temp != m_tail )
            {
                node_t * condenado = temp;
                temp = temp->next;
                delete condenado;
            }
            m_len = 0;
            delete temp;
        }

        /*!
         * @brief 
         */
        iterator begin()
        {
            return iterator( m_head->next );
        }

        /*!
         * @brief 
         */
        const_iterator cbegin( void ) const
        {
            return const_iterator( m_head->next );
        }

        /*!
         * @brief 
         */
        iterator end()
        {
            return iterator( m_tail );
        }

        const_iterator cend( void ) const
        {
            return const_iterator( m_tail );
        }

        /*!
         * @brief Informs the list size
         * @return Number of elements in the container
         */
        size_t size( void ) const
        {
            return m_len;
        }

        /*!
         * @brief Verifies if the list is empty
         * @return True if the container contains no elements, and false otherwise
         */
        bool empty( void ) const
        {
            return m_len == 0;
        }

        /*!
         * @return The object at the end of the list
         */
        T & back( void )
        {
            if( empty() )
                throw std::out_of_range("[back()]: Cannot recover an element from an empty list!");
            return m_tail->prev->data;
        }

        /*!
         * @return The object at the beginning of the list
         */
        T & front( void )
        {
            if( empty() )
                throw std::out_of_range("[front()]: Cannot recover an element from an empty list!");
            return m_head->next->data;
        }

        /*!
         * @return The constant object at the end of the list
         */
        const T & back( void ) const
        {
            if( empty() )
                throw std::out_of_range("[back()]: Cannot recover an element from an empty list!");
            return m_tail->prev->data;
        }

        /*!
         * @return The constant object at the beginning of the list
         */
        const T & front( void ) const
        {
            if( empty() )
                throw std::out_of_range("[front()]: Cannot recover an element from an empty list!");
            return m_head->next->data;
        }

        /*!
         * @brief Adds value to the end of the list
         * @param value The value to add
         */
        void push_back( const T & value )
        {
            node_t * new_node = new node_t( value );
            
            new_node->next = m_tail;
            new_node->prev = m_tail->prev;

            m_tail->prev->next = new_node;
            m_tail->prev = new_node;

            m_len++;
        }

        /*!
         * @brief Adds value to the begin of the list
         * @param value The value to add
         */
        void push_front( const T & value )
        {
            node_t * new_node = new node_t( value );
            
            new_node->next = m_head->next;
            new_node->prev = m_head;

            m_head->next->prev = new_node;
            m_head->next = new_node;

            m_len++;
        }
        
        /*!
         * @brief Removes the object at the begin of the list
         */
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

        /*!
         * @brief Removes the object at the end of the list
         */
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

        /*!
         * @brief Replaces the content of the list with copies of value
         * @param value Value to copy
         */
        void assign(const T& value )
        {
            node_t * temp = m_head;

            while( temp != m_tail )
            {
                temp = temp->next;
                temp->data = value;
            }
        }

        /*!
         * @brief Replaces all the list with content of the range
         * @param first Begin of range
         * @param last End of range
         */
        template <class InItr >
        void assign( InItr first, InItr last )
        {
            node_t * temp = m_head;
            InItr it = last;

            while( temp != m_tail )
            {
                if(it == last) //quando chegar no last, voltar pro first, para continuar copiando
                    it = first;

                temp = temp->next;
                temp->data = *(it++);
            }
        }

        /*!
         * @brief Replaces all the list with content initializer list
         * @param ilist An initializer list
         */
        void assign( std::initializer_list<T> ilist )
        {
            node_t * temp = m_head;
            auto i = 0u;

            while( temp != m_tail)
            {
                if ( i == ilist.size() ) //quando i chega no limite , volta pro inicio para continuar copiando
                    i = 0u;

                temp = temp->next;
                temp->data = *(ilist.begin()+i);
                i++;
            }
        }

        /*! 
         * @brief Prints the list and your length and capacity
         */
        void print() const
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
        

        //<! ===== TODO
        /*<!
            list( list<T> && );
            list & operator= ( const list<T> & );
            list & operator= ( list<T> && );
            iterator insert( const_iterator itr, const T & value );
            iterator insert( const_iterator pos, std::initializer_list<T> ilist );
            iterator erase( const_iterator itr );
            iterator erase( const_iterator first, const_iterator last );
            const_iterator find( const T & value ) const;
        */
    };
}

#endif