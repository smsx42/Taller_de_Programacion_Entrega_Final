#ifndef ANIMACION_MONEDA_H_
#define ANIMACION_MONEDA_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Moneda : public Animacion {

   public:

    explicit Animacion_Moneda();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Moneda();
};

#endif