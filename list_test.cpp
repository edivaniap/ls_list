#include "lslist.h"

using namespace ls;
/*template <typename T>
MyBidirectionalIterator::MyBidirectionalIterator( T * ptr_ = nullptr )
{ 
    m_ptr = ptr_;
}

// Special methods. Default versions.
~MyBidirectionalIterator() = default;
MyBidirectionalIterator( const self_type & ) = default;
self_type & operator=( const self_type & ) = default;*/

/*! The  *it operator.
 *  Supports: *it = XXXX or XXXX = *it.
 *  \return A reference to the object this iterator points to.
 */
template <typename T>
typename T::value_type  & MyBidirectionalIterator::operator*()
{
    assert( m_ptr != nullptr );
    return m_ptr->data;
}

template <typename T>
self_type MyBidirectionalIterator::operator++()
{
    m_ptr = m_ptr->next;
    return *this;
}
template <typename T>
self_type MyBidirectionalIterator::operator++(int)
{
    self_type temp = *this;
    m_ptr = m_ptr->next;
    return temp;
}

template <typename T>
self_type MyBidirectionalIterator::operator--()
{
    m_ptr = m_ptr->prev;
    return *this;
}

template <typename T>
self_type MyBidirectionalIterator::operator--(int)
{
    self_type temp = *this;
    m_ptr = m_ptr->prev;
    return temp;
}

template <typename T>
bool MyBidirectionalIterator::operator==( const self_type & rhs_ ) const
{
    return m_ptr == rhs_.m_ptr;
}

template <typename T>
bool MyBidirectionalIterator::operator!=( const self_type & rhs_ ) const
{
    return m_ptr != rhs_.m_ptr;
}

template <typename T>
self_type MyBidirectionalIterator::operator+=( difference_type step_ );

template <typename T>
self_type MyBidirectionalIterator::operator-=(  difference_type step_ );

template <typename T>
pointer MyBidirectionalIterator::operator->( void ) const
{
    assert( m_ptr );
    return *m_ptr;
}

template <typename T>
difference_type MyBidirectionalIterator::operator-( const self_type & rhs_ ) const;



template <typename T>
list( void )
    : m_len( 0 )
    , m_head( new node_t() )
    , m_tail( new node_t() )
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template <typename T>
~list( void )
{
    clear(); // TODO: Apagar os nós da lista.
    delete m_head;
    delete m_tail;
}

template <typename T>
list( const list & clone_ )
    : m_len( 0 )
    , m_head( new node_t() )
    , m_tail( new node_t() )
{
    // TODO: copiar os dados de clone para this.
    for ( auto it( clone_.begin() ) ; it != clone_.end() ; ++it )
        push_back( *it );
}

template <typename T>
list( list && );

template <typename T>
list & operator= ( const list & );

template <typename T>
list & operator= ( list && );
    
iterator begin( void )
{
    return iterator( m_head->next );
}

const_iterator cbegin( void ) const;

iterator end( void )
{
    return iterator( m_tail );
}
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