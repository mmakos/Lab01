#include <iostream>

#include "resource.h"

void Resource::addResources( int i )
{
    m_quantity += i;
    if( m_quantity < 0 )
        m_quantity = 0;
}

bool Resource::substractResources( int i )
{
    if( i <= m_quantity ){
        m_quantity -= i;
        return true;
    }
    else
        return false;
}

int Resource::countDigits( int n ) const
{
    int i = 0;
    do{
        n = n / 10;
        i++;
    }while( n > 0 );
    return i;
}

void Resource::writeNumber() const
{
    std::cout << m_quantity << "   ";
    for( int i = countDigits( m_quantity ); i < 7; i++ )
        std::cout << " ";
}

void Resource::writeName() const
{
    std::cout << m_name << ":  ";
    for( int i = m_name.length(); i < 12; i++ )
        std::cout << " ";
}
