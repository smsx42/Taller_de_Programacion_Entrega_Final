#include "objetoMunicionTipo_3View.h"

ObjetoMunicionTipo_3View::ObjetoMunicionTipo_3View() : ObjetoView() {
    this->crear_animacion();
}

void ObjetoMunicionTipo_3View::crear_animacion() {

    this->animacion = std::unique_ptr<Animacion>(new Animacion_municion_tipo_3());
}

ObjetoMunicionTipo_3View::~ObjetoMunicionTipo_3View() {}