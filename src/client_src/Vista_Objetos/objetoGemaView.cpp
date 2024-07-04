#include "objetoGemaView.h"

ObjetoGemaView::ObjetoGemaView(SDL2pp::Renderer *render) : ObjetoView() {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_AGARRAR_GEMA);
    this->factory.crear_animacion_objeto(GEMA_OBJETO);
    this->factory.crear_texturas(render);
}

ObjetoGemaView::~ObjetoGemaView() {}