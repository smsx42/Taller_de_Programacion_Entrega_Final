#ifndef ANIMACION_SPAZ_CAMINANDO_H_
#define ANIMACION_SPAZ_CAMINANDO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Caminando : public Animacion {

   public:

   explicit Animacion_Spaz_Caminando();

   ~Animacion_Spaz_Caminando();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif