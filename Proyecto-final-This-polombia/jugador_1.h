#ifndef JUGADOR_1_H
#define JUGADOR_1_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

class Jugador_1: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Jugador_1( int n );     //Constructor del objeto, se le debe pasar el # del personaje del jugador
    void set_imagen_jugador( int n );   //Funcion para setear las diferentes imagenes del personaje

        int frame = 0 , num_plane ;     //Variables utiles para la animacion del personaje

    public slots:

        void animacion_sprite() ;       //Slot para la animacion del personaje

    private:
        QPixmap sprite_jugador , sprite_actual ;        //Aqui se guardan los sprites del personaje

          QTimer *animacion ;     //Timer para la animacion del personaje

      };

      #endif // JUGADOR_1_H
