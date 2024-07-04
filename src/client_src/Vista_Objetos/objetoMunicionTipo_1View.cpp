#include "objetoMunicionTipo_1View.h"

ObjetoMunicionTipo_1View::ObjetoMunicionTipo_1View(SDL2pp::Renderer *render) : ObjetoView() {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_AGARRAR_MUNICION);
    this->factory.crear_animacion_objeto(MUNICION_TIPO_1);
    this->factory.crear_texturas(render);
}


ObjetoMunicionTipo_1View::~ObjetoMunicionTipo_1View() {}