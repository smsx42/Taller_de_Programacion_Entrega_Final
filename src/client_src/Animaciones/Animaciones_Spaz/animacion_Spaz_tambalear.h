#ifndef ANIMACION_SPAZ_TAMBALEAR_H_
#define ANIMACION_SPAZ_TAMBALEAR_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Spaz_Tambalear : public Animacion {

   public:

   explicit Animacion_Spaz_Tambalear();

   ~Animacion_Spaz_Tambalear();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif