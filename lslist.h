/**
* @file lslist.h
* @brief Classes para lista duplamente encadeada genérica
* @author Edivania Pontes
* @date 01/06/2017
*/

#ifndef _LSLIST_H_
#define _LSLIST_H_

#include <iostream>  // cout, endl
#include <iterator>  // bidirectional_iterator_tag
#include <cassert>   // assert()
#include <algorithm> // copy
#include <cstddef>   // std::ptrdiff_t

namespace ls         // linear sequence
{
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
                T * m_ptr; // node_t * m_ptr;

                // =============================================================
                // Public interface that mimics the behaviour of a regular pointer.
                // =============================================================
            public:
                // Constructor
                MyBidirectionalIterator( T * ptr_ = nullptr );

                // Special methods. Default versions.
                ~MyBidirectionalIterator() = default;
                MyBidirectionalIterator( const self_type & ) = default;
                self_type & operator=( const self_type & ) = default;

                /*! The  *it operator.
                 *  Supports: *it = XXXX or XXXX = *it.
                 *  \return A reference to the object this iterator points to.
                 */
                //node_t::value_type & operator*()
                typename T::value_type  & operator*();
                
                /*! The ++it operator.
                 *  \return The calling object.
                 */
                self_type operator++();

                /*! The it++ operator.
                 *  \return The calling object.
                 */
                self_type operator++(int);

                /*! The --it operator.
                 *  \return The calling object.
                 */
                self_type operator--();
                /*! The it-- operator.
                 *  \return The calling object.
                 */
                self_type operator--(int);

                /// The it == it2 operator.
                bool operator==( const self_type & rhs_ ) const;

                /// The it != it2 operator.
                bool operator!=( const self_type & rhs_ ) const;
                
                // ==================================================
                /* Other methods that you might wanto to implement. */
                // ==================================================

                /// it += 3; // Go back  3 positions within the container. 
                self_type operator+=( difference_type step_ );

                /// it -= 3; // Go back  3 positions within the container. 
                self_type operator-=(  difference_type step_ );

                /// it->method()
                pointer operator->( void ) const;

                /// it1 - it2
                difference_type operator-( const self_type & rhs_ ) const;

        };
        
    template <typename T>
    class list 
    {
    private:
        struct Node { /*See Code 2*/ };
        
    public:
        class const_iterator { /*See Code 3*/ };
        class iterator : public const_iterator { /*See Code 3*/ };
        
        list( void );
        ~list( void );
        list( const list & );
        list( list && );
        list & operator= ( const list & );
        list & operator= ( list && );
    
        iterator begin( void );
        const_iterator cbegin( void ) const;
        iterator end( void );
        const_iterator cend( void ) const;
        int size( void ) const;
        bool empty( void ) const;
        void clear( void );
        T & front( void );
        const T & front( void ) const;
        T & back( void );
        const T & back( void ) const;
        void push_front( const T & value );
        void push_back( const T & value );
        void pop_front( void );
        void pop_back( void );
        void assign(const T& value );
        template <class InItr >
        void assign( InItr first, InItr last );
        void assign( std::initializer_list<T> ilist );
        iterator insert( const_iterator itr, const T & value );
        iterator insert( const_iterator pos, std::initializer_list<T> ilist );
        iterator erase( const_iterator itr );
        iterator erase( const_iterator first, const_iterator last );
        const_iterator find( const T & value ) const;
    
    private:
        int   m_size;
        Node *m_head;
        Node *m_tail;
    };
}

#endif