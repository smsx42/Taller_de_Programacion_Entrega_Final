#ifndef ANIMACION_SPAZ_SALTANDO_HORIZONTAL_H_
#define ANIMACION_SPAZ_SALTANDO_HORIZONTAL_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Saltando_Horizontal : public Animacion {

   public:

   explicit Animacion_Spaz_Saltando_Horizontal();

   ~Animacion_Spaz_Saltando_Horizontal();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif