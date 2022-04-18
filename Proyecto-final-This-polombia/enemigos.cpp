#include "enemigos.h"
#include "proyectil.h"
#include "puntaje.h"
extern puntaje *Score ;

enemigos::enemigos( int n_enemy ){

    if( n_enemy == 0 ){

       sprites1.load(":/Recursos/New_enemigo_100.png") ;

        tX = 61 ;

        tY = 50 ;

        n = 0 ;
    }
    else if( n_enemy == 1 ){

       sprites1.load(":/Recursos/new_enemigo_150.png") ;

        tX = 60 ;

        tY = 50 ;

        amplitud=rand()%3;

        n = 1 ;
    }
    else if( n_enemy == 2 ){

        sprites1.load(":/Recursos/new_enemigo_200.png") ;

        tX = 62 ;

        tY = 58 ;

        amplitud=rand()%3;

        n = 2 ;
    }

    timer_enemy = new QTimer() ;

    connect( timer_enemy , SIGNAL( timeout() ) , this , SLOT( movimiento_enemigos() ) ) ;

    timer_enemy->start( T ) ;

        explosion = new QSoundEffect ;

        explosion->setSource( QUrl("qrc:/Recursos/explosion.wav") ) ;

        explosion->setVolume( 0.20f ) ;

}

void enemigos::set_enemigo(){

    if( n == 0 ){

        enemy = sprites1.copy( tX*frame , 0 , tX , tY ) ;

    }
    else if( n == 1 ){

        enemy = sprites1.copy( tX*frame , 0 , tX , tY ) ;

    }
    else if( n == 2 ){

        enemy = sprites1.copy( tX*frame , 0 , tX , tY ) ;

    }

    setPixmap( enemy.scaled( tX , tY ) ) ;
}



void enemigos::movimiento_enemigos(){

        //colisiones

    colisiones = collidingItems() ;

    for( int i = 0 , nl = colisiones.size() ; i < nl ; i++ ){


        if( (typeid( *( colisiones[i] )  ) ==  typeid( proyectil )) && collide ){
            Score->aumentar_puntaje( n ) ;
            explosion->play() ;

            scene()->removeItem( colisiones[i] ) ;

            delete colisiones[i] ;

            frame = 1 ;

            set_enemigo() ;
            collide = false ;

            QTimer::singleShot( 800 , this, SLOT( muerte() ) );

            return;

        }


    }

    int px , py ;

    px = this->x() ;

    py = this->y() ;
    if( n == 0 ){

        setPos( px , py+5 ) ;
    }

    else if( n == 1 ){

        double pos_y = 0;

        if (amplitud==0)pos_y = 5*qSin( 4*t_disc1*(0.001*T) ) ;

        else if(amplitud==1)pos_y = 8*qSin( 4*t_disc1*(0.001*T) ) ;

        else if(amplitud==2)pos_y = 10*qSin( 4*t_disc1*(0.001*T) ) ;


        t_disc1++ ;

        if(t_disc1==43)
        {
            t_disc1=0;
        }
        setPos( px - 5 , py + pos_y) ;

    }
    else if( n == 2 ){

        double pos_x=0;
        double pos_y=0;

        if (amplitud==0){

            pos_x = 5*qCos(4*t_disc*(0.001*T));

            pos_y = 5*qSin( 4*t_disc*(0.001*T) ) ;
        }
        else if(amplitud==1)
        {
            pos_x = 8*qCos(4*t_disc*(0.001*T));

            pos_y = 8*qSin( 4*t_disc*(0.001*T) ) ;

        }
        else if(amplitud==2)
        {
            pos_x = 10*qCos(4*t_disc*(0.001*T));

            pos_y = 10*qSin( 4*t_disc*(0.001*T) ) ;
        }
        if(t_disc==43)
        {
            t_disc=0;
        }

        t_disc++;

        setPos( px - 3 - pos_x , py + pos_y ) ;

    }



    int flag = this->x() + 62 ;

    if( flag < 0 ){

        scene()->removeItem( this ) ;

        delete this ;
    }

    int flag2= this->y();

    if(flag2>500){

        scene()->removeItem(this);

        delete this;
    }

}

void enemigos::muerte(){

    scene()->removeItem( this ) ;

    delete this ;

    return;
}
