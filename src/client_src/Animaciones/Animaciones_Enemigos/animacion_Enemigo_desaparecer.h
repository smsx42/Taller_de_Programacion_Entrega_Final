#ifndef ANIMACION_ENEMIGO_DESAPARECER_H_
#define ANIMACION_ENEMIGO_DESAPARECER_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_Enemigo_Desaparecer : public Animacion {

   public:

    explicit Animacion_Enemigo_Desaparecer();

    ~Animacion_Enemigo_Desaparecer();

    void crear_texturas(SDL2pp::Renderer *render) override;

};

#endif