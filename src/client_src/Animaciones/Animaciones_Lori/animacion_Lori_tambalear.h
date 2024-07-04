#ifndef ANIMACION_LORI_TAMBALEAR_H_
#define ANIMACION_LORI_TAMBALEAR_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Tambalear : public Animacion {

   public:

   explicit Animacion_Lori_Tambalear();

   ~Animacion_Lori_Tambalear();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif