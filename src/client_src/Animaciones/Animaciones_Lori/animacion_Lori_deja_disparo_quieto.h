#ifndef ANIMACION_LORI_DEJA_DISPARO_QUIETO_H_
#define ANIMACION_LORI_DEJA_DISPARO_QUIETO_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Lori_Deja_Disparo_Quieto : public Animacion {

   public:

   explicit Animacion_Lori_Deja_Disparo_Quieto();

   ~Animacion_Lori_Deja_Disparo_Quieto();

   void crear_texturas(SDL2pp::Renderer *render) override;
};

#endif