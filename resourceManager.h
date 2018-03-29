#ifndef __RESOURCEMANAGER_H_
#define __RESOURCEMANAGER_H_

#include "resource.h"

#define MAX_RESOURCES 15

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager(){};

    void nextTurn();
    void resourcesAssign();
    void mutiny();
    void endMutiny();
    void hungry();
    void breakdown();
    void thiefs();
    void miracle();
    void destruction();
    void buildFactory( int number );
    void hireWorker( int number );
    Resource &getResource( int r )
    {
        return m_resources[ r ];
    }
    void setTour( int t )
    {
        m_tour = t;
    }
    int getTour() const
    {
        return m_tour;
    }

protected:
    Resource m_resources[ MAX_RESOURCES ];
    int m_tour;

};

#endif //RESOURCEMANAGER_H_
