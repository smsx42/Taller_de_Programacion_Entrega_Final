#include "objetoZanahoriaView.h"

ObjetoZanahoriaView::ObjetoZanahoriaView(SDL2pp::Renderer *render) : ObjetoView() {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_AGARRAR_ZANAHORIA);
    this->factory.crear_animacion_objeto(ZANAHORIA_OBJETO);
    this->factory.crear_texturas(render);
}

ObjetoZanahoriaView::~ObjetoZanahoriaView() {}