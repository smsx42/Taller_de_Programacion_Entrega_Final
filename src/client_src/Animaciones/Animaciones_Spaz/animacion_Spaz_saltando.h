#ifndef ANIMACION_SPAZ_SALTANDO_H_
#define ANIMACION_SPAZ_SALTANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Saltando : public Animacion {

   public:

   explicit Animacion_Spaz_Saltando();

   ~Animacion_Spaz_Saltando();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif