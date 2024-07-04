#ifndef ANIMACION_BALA_PISTOLA_H_
#define ANIMACION_BALA_PISTOLA_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Bala_Pistola : public Animacion {

   public:

    explicit Animacion_Bala_Pistola();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Bala_Pistola();



};

#endif 