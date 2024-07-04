#ifndef ANIMACION_ZANAHORIA_H_
#define ANIMACION_ZANAHORIA_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Zanahoria : public Animacion {

   public:

    explicit Animacion_Zanahoria();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_Zanahoria();
};

#endif