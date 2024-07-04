#include "objetoMonedaView.h"

ObjetoMonedaView::ObjetoMonedaView(SDL2pp::Renderer *render) : ObjetoView() {
    this->sonido = std::make_unique<SDL2pp::Chunk>(PATH_SONIDO_AGARRAR_MONEDA);
    this->factory.crear_animacion_objeto(MONEDA_OBJETO);
    this->factory.crear_texturas(render);
}

ObjetoMonedaView::~ObjetoMonedaView() {}