#include "enemigoBrujaView.h"

EnemigoBrujaView::EnemigoBrujaView(SDL2pp::Renderer *render) : EnemigoView() {
    this->animaciones.insert(std::make_pair(CAMINANDO, this->factory.crear_animacion_enemigo(ENEMIGO_BRUJA)));
    this->animaciones.insert(std::make_pair(DESAPARECER, this->factory.crear_animacion_enemigo(DESAPARECER)));
    this->factory.crear_texturas(render);
}

EnemigoBrujaView::~EnemigoBrujaView() {}