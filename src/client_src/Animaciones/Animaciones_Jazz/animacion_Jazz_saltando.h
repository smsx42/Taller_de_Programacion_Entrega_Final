#ifndef ANIMACION_JAZZ_SALTANDO_H_
#define ANIMACION_JAZZ_SALTANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Jazz_Saltando : public Animacion {

   public:

   explicit Animacion_Jazz_Saltando();

   ~Animacion_Jazz_Saltando();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif