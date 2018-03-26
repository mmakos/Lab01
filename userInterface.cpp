#include <iostream>
#include <fstream>

#include "userInterface.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

#define FACTOR 7

void UserInterface::writeResources()
{
    std::cout << "TURA:" << m_rM.getTour() << std::endl << std::endl;
    for( int i = 0; i < 5; i++ ){
        m_rM.getResource( i ).writeName();
        m_rM.getResource( i ).writeNumber();
        m_rM.getResource( 10 + i ).writeName();
        m_rM.getResource( 10 + i ).writeNumber();
        m_rM.getResource( 5 + i ).writeName();
        m_rM.getResource( 5 + i ).writeNumber();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void UserInterface::saveGame()
{
    std::fstream save;
    save.open( "save.game", std::ios::out | std::ios::binary );
    if( !save.good() ){
        std::cout << "Nie uda\210o si\251 zapisa\206 stanu gry :-( Spr\242buj ponownie!" << std::flush;
        Sleep( 2000 );
        system( "clear || cls" );
        return;
    }
    for( int i = 0; i < MAX_RESOURCES; i++ ){
        save << m_rM.getResource( i ).getQuantity() << " ";
    }
    save << m_rM.getTour();
    std::cout << "Stan gry zapisano pomy\230lnie :-)" << std::flush;
    Sleep( 2000 );
    system( "clear || cls" );
    save.close();
}

void UserInterface::loadGame()
{
    std::fstream load;
    load.open( "save.game", std::ios::in | std::ios::binary );
    if( !load.good() ){
        std::cout << "Nie znaleziono zapisu gry :-(" << std::flush;
        Sleep( 2000 );
        system( "clear || cls" );
        return;
    }
    for( int i = 0; i < MAX_RESOURCES; i++ ){
        int quantity;
        load >> quantity;
        m_rM.getResource( i ).setQuantity( quantity );
    }
    int tour = 0;
    load >> tour;
    m_rM.setTour( tour );

    std::cout << "Stan gry wczytano pomy\230lnie :-)" << std::flush;
    Sleep( 2000 );
    system( "clear || cls" );
    load.close();
}

void UserInterface::gameInstruction()
{
    int tour = m_rM.getTour();
    std::cout <<  "W tej grze musisz zdobywa\206 surwce, budowa\206 nowe fabryki oraz zatrudnia\206 w nich pracownik\242w. " << std::endl << std::endl;

    std::cout <<  "Koszty fabryk:" << std::endl;
    std::cout <<  "Kopalnia z\210ota - " << 30 * ( tour / FACTOR + 1 ) << " stali + " << 250 * ( tour / FACTOR + 1 ) << " drewna + " << 70 * ( tour / FACTOR + 1 ) << " kamienia" << std::endl;
    std::cout <<  "Huta stali - " << 100 * ( tour / FACTOR + 1 ) << " drewna + " << 100 * ( tour / FACTOR + 1 ) << " kamienia" << std::endl;
    std::cout <<  "Tartak - " << 100 * ( tour / FACTOR + 1 ) << " stali + " << 50 * ( tour / FACTOR + 1 ) << " kamienia" << std::endl;
    std::cout <<  "Kamienio\210om - " << 400 * ( tour / FACTOR + 1 ) << " drewna + " << 30 * ( tour / FACTOR + 1 ) << " stali" << std::endl;
    std::cout <<  "Farma - " << 200 * ( tour / FACTOR + 1 ) << " drewna + " << 20 * ( tour / FACTOR + 1 ) << " stali + " << 25 * ( tour / FACTOR + 1 ) << " kamienia" << std::endl << std::endl;

    std::cout <<  "Produktywno\230\206 robotnik\242w na tur\251:" << std::endl;
    std::cout <<  "G\242rnik - " << 5 * ( tour / FACTOR + 1 ) << " z\210ota" << std::endl;
    std::cout <<  "Stalownik - 15 stali" << std::endl;
    std::cout <<  "Drwal - 50 drewna" << std::endl;
    std::cout <<  "Kamieniarz - 30 kamienia" << std::endl;
    std::cout <<  "Farmer - " << 8 * ( tour / FACTOR + 1 ) << " zwierz\245t" << std::endl << std::endl;

    std::cout <<  "Koszt utrzymania robotnika to " << ( tour / FACTOR + 1 ) << " sztuka z\210ota i " << 2 * ( tour / FACTOR + 1 ) << " zwierz\251ta na tur\251." << std::endl << std::endl;

    std::cout <<  "POWODZENIA!!!" << std::endl << std::endl;
    std::cout << "Aby wr\242ci\206 do gry wci\230nij dowolny klawisz.";

    char a; std::cin >> a;
    system( "clear || cls" );
}

void UserInterface::hireWorker()
{
    writeResources();

    int actionNumber;

    std::cout << "1. Zatrudnij g\242rnik\242w." << std::endl;
    std::cout << "2. Zatrudnij stalownik\242w." << std::endl;
    std::cout << "3. Zatrudnij drwali." << std::endl;
    std::cout << "4. Zatrudnij kamieniarzy." << std::endl;
    std::cout << "5. Zatrudnij farmer\242w." << std::endl;
    std::cin >> actionNumber;
    if( !std::cin.good() ){
        std::cin.clear();
        std::cin.ignore( 100, '\n' );
    }
    system( "clear || cls" );
    if( actionNumber > 0 && actionNumber < 6 ){
        writeResources();
        m_rM.hireWorker( actionNumber );
    }
    else{
        std::cout << "Niepoprawny wyb\242r!" << std::flush;
        Sleep( 2000 );
        system( "clear || cls" );
    }
}

void UserInterface::buildFactory()
{
    writeResources();

    int actionNumber;
    std::cout << "1. Wybuduj kopalni\251." << std::endl;
    std::cout << "2. Wybuduj hut\251 stali." << std::endl;
    std::cout << "3. Wybuduj tartak." << std::endl;
    std::cout << "4. Wybuduj kamienio\210om." << std::endl;
    std::cout << "5. Wybuduj farm\251." << std::endl;
    std::cin >> actionNumber;
    if( !std::cin.good() ){
        std::cin.clear();
        std::cin.ignore( 100, '\n' );
    }
    system( "clear || cls" );
    if( actionNumber > 0 && actionNumber < 6 ){
        writeResources();
        m_rM.buildFactory( actionNumber );
    }
    else{
        std::cout << "Niepoprawny wyb\242r!" << std::flush;
        Sleep( 2000 );
        system( "clear || cls" );
    }
}

int UserInterface::chooseAction()
{
    writeResources();

    int actionNumber;
    std::cout << "Wybierz dzialanie: " << std::endl;
    std::cout << "1. Zatrudnij robotnik\242w." << std::endl;
    std::cout << "2. Wybuduj now\245 fabryk\251." << std::endl;
    std::cout << "3. Nast\251pna tura." << std::endl;
    std::cout << "4. Wy\230wietl instrukcj\251." << std::endl;
    std::cout << "5. Zapisz." << std::endl;
    std::cout << "6. Wczytaj gr\251." << std::endl;
    std::cout << "7. Zako\344cz gr\251." << std::endl;
    std::cin >> actionNumber;
    if( !std::cin.good() ){
        std::cin.clear();
        std::cin.ignore( 100, '\n' );
    }
    system( "clear || cls" );
    return actionNumber;
}

void UserInterface::executeAction( int actionNumber )
{
    switch( actionNumber )
    {
    case 1:
        hireWorker();
        break;
    case 2:
        buildFactory();
        break;
    case 3:
        m_rM.nextTurn();
        break;
    case 4:
        gameInstruction();
        break;
    case 5:
        saveGame();
        break;
    case 6:
        loadGame();
        break;
    default:
        std::cout << "Niepoprawny wyb\242r!" << std::flush;
        Sleep( 2000 );
        system( "clear || cls" );
        break;
    }
}


#ifdef _TEST
int UserInterface::test()
{
    int errors = 0;

    for( int i = 5; i < 10; i++ ){
        m_rM.getResource( i ).setQuantity( 12 );
        m_rM.getResource( i ).setMutiny( 3 );
    }
    for( int i = 10; i < 15; i++ ){
        m_rM.getResource( i ).setQuantity( 3 );
        m_rM.getResource( i ).setMutiny( 1 );
    }
    m_rM.setTour( 3 );
    for( int i = 0; i < 5; i++ ){
        m_rM.getResource( i ).setQuantity( 0 );
    }

    //resourcesAssign test
    m_rM.resourcesAssign();
    if( m_rM.getResource( 0 ).getQuantity() != 18 ){
        errors++;
        std::cout << "Kopalnia zlota zle generuje przychody!   " << m_rM.getResource( 0 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 1 ).getQuantity() != 90 ){
        errors++;
        std::cout << "huta stali zle generuje przychody!   " << m_rM.getResource( 1 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 2 ).getQuantity() != 300 ){
        errors++;
        std::cout << "Tartak zlota zle generuje przychody!   " << m_rM.getResource( 2 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 3 ).getQuantity() != 180 ){
        errors++;
        std::cout << "Kamieniolom zlota zle generuje przychody!   " << m_rM.getResource( 3 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 4 ).getQuantity() != 36 ){
        errors++;
        std::cout << "Farma zlota zle generuje przychody!   " << m_rM.getResource( 4 ).getQuantity() << std::endl;
    }

    //endMutiny test
    m_rM.endMutiny();
    for( int i = 0; i < 15; i++ ){
        if( m_rM.getResource( i ).getMutiny() != 0 ){
            errors++;
            m_rM.getResource( i ).writeName();
            std::cout << " ma nieprawidlowa wartos buntownikow!" << std::endl;
        }
    }
    for( int i = 0; i < 5; i++ ){
        m_rM.getResource( i ).setQuantity( 0 );
    }
    m_rM.setTour( 10 );

    //second resourcesAssign test (without mutiny and on 10th tour)
    m_rM.resourcesAssign();
    if( m_rM.getResource( 0 ).getQuantity() != 72 ){
        errors++;
        std::cout << "Kopalnia zlota zle generuje przychody w 10 turze bez buntu!   " << m_rM.getResource( 0 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 1 ).getQuantity() != 180 ){
        errors++;
        std::cout << "huta stali zle generuje przychody w 10 turze bez buntu!   " << m_rM.getResource( 1 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 2 ).getQuantity() != 600 ){
        errors++;
        std::cout << "Tartak zlota zle generuje przychody w 10 turze bez buntu!   " << m_rM.getResource( 2 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 3 ).getQuantity() != 360 ){
        errors++;
        std::cout << "Kamieniolom zlota zle generuje przychody w 10 turze bez buntu!   " << m_rM.getResource( 3 ).getQuantity() << std::endl;
    }
    if( m_rM.getResource( 4 ).getQuantity() != 144 ){
        errors++;
        std::cout << "Farma zlota zle generuje przychody w 10 turze bez buntu!   " << m_rM.getResource( 4 ).getQuantity() << std::endl;
    }
    return errors;
}
#endif
