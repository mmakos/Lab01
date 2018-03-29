#ifndef __USERINTERFACE_H_
#define __USERINTERFACE_H_
//#define _TEST

#include "resourceManager.h"

class UserInterface
{
public:
    UserInterface(){}
    ~UserInterface(){}

    int chooseAction();
    void executeAction( int actionNumber );
    #ifdef _TEST
        int test();
    #endif // _TEST
protected:
    void writeResources();
    void saveGame();
    void loadGame();
    void gameInstruction();
    void hireWorker();
    void buildFactory();

protected:
    ResourceManager m_rM;
};

#endif //__USERINTERFACE_H_
