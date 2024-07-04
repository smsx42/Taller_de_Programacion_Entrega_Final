#ifndef ANIMACION_SPAZ_CORRIENDO_H_
#define ANIMACION_SPAZ_CORRIENDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Corriendo : public Animacion {

   public:

   explicit Animacion_Spaz_Corriendo();

   ~Animacion_Spaz_Corriendo();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif