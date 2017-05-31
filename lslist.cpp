namespace ls
{
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
        int m_size;
        Node *m_head;
        Node *m_tail;
    };
}