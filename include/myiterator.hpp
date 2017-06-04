/**
* @file myiterator.hpp
* @version 1.0  
* @title MyIterator
* @brief Classe para iterator que será usado na lista
* @author Selan R. Santos (Algumas alterações: Edivânia)
* @date 03/06/2017
*/

#ifndef _MYITERATOR_H_
#define _MYITERATOR_H_

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
}

#endif