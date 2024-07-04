#include "animacion_Lori_tambalear.h"

Animacion_Lori_Tambalear::Animacion_Lori_Tambalear() : Animacion() {}

void Animacion_Lori_Tambalear::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_TAMBALEAR, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Tambalear::~Animacion_Lori_Tambalear() {}