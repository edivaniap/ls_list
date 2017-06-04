/**
* @file list.h
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

            value_type data;
            node_t * next;
            node_t * prev;

            node_t( const T & d_= T() , node_t * n_ = nullptr, node_t * p_ = nullptr )
                : data ( d_ )
                , next ( n_ )
                , prev ( p_ )
            { /* empty */ }
        };
        int     m_len;
        node_t *m_head;        
        node_t *m_tail;
        
    public:
        using iterator = MyBidirectionalIterator< node_t >;
        using const_iterator = MyBidirectionalIterator< const node_t >;

        list()
            : m_len( 0 )
            , m_head( new node_t() )
            , m_tail( new node_t() )
        {
            m_head->next = m_tail;
            m_tail->prev = m_head;
        }

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
        

        //<! ==TODO
        /*
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