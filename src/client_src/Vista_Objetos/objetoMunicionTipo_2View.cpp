#include "objetoMunicionTipo_2View.h"

ObjetoMunicionTipo_2View::ObjetoMunicionTipo_2View(SDL2pp::Renderer *render) : ObjetoView() {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_AGARRAR_MUNICION);
    this->factory.crear_animacion_objeto(MUNICION_TIPO_2);
    this->factory.crear_texturas(render);
}


ObjetoMunicionTipo_2View::~ObjetoMunicionTipo_2View() {}