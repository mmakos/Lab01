#ifndef __RESOURCE_H_
#define __RESOURCE_H_

#include <string>

class Resource
{
public:
    Resource( const std::string &n = "", int i = 0 )
    {
        m_name = n;
        m_quantity = i;
        m_mutiny = 0;
    }
    ~Resource(){}

    void addResources( int i );
    bool substractResources( int i );
    void writeNumber() const;
    void writeName() const;
    int getQuantity() const
    {
        return m_quantity;
    }
    void setQuantity( int a )
    {
        m_quantity = a;
    }
    int getMutiny() const
    {
        return m_mutiny;
    }
    void setMutiny( int a )
    {
        m_mutiny = a;
    }
    void addMutiny( int a = 1 )
    {
        m_mutiny += a;
    }

protected:
    int countDigits( int n ) const;

    std::string m_name;
    int m_quantity;
    int m_mutiny;

};


#endif // __RESOURCE_H_
