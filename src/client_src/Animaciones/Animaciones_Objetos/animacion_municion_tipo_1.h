#ifndef ANIMACION_MUNICION_TIPO_1_H_
#define ANIMACION_MUNICION_TIPO_1_H_

#include "../src/client_src/Animaciones/animacion.h"
#include "../src/client_src/direcciones.h"

class Animacion_municion_tipo_1 : public Animacion {
    
   public:
    
    explicit Animacion_municion_tipo_1();

    void crear_texturas(SDL2pp::Renderer *render) override;

    ~Animacion_municion_tipo_1();




};

#endif