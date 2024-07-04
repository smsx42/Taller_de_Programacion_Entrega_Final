#ifndef ANIMACION_SPAZ_HABILIDAD_H_
#define ANIMACION_SPAZ_HABILIDAD_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Habilidad : public Animacion {

   public:

   explicit Animacion_Spaz_Habilidad();

   ~Animacion_Spaz_Habilidad();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif