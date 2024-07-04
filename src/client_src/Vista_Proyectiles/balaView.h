#ifndef BALAVIEW_H_
#define BALAVIEW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <map>
#include "../src/common_src/evento.h"
#include "../src/common_src/codigo_objeto.h"
#include "../src/client_src/direcciones.h"
#include "../src/client_src/Animaciones/animacion.h"
#include "proyectilViewFactory.h"

#define BALA_HEIGHT 15
#define BALA_WIDTH 15

class BalaView {
   
   private:

    int posicion_x;
    int posicion_y;
    int width;
    int height;
    std::unique_ptr<Animacion> animacion_bala;
    std::unique_ptr<SDL2pp::Chunk> sonido;
    ProyectilViewFactory factory;
    int contador_disparos;

    bool facingLeft;

   public:
    
    BalaView(bool face, int x, int y, uint8_t tipo, SDL2pp::Renderer *render);

    ~BalaView();

    void actualizar(EventoBala const &evento,float dt);

    void renderizar(SDL2pp::Renderer &render, int cam_x, int cam_y);

    void crear_sonido(SDL2pp::Mixer &reproductor_sonido);
    
};















#endif