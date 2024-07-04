#include "animacion_Spaz_tambalear.h"

Animacion_Spaz_Tambalear::Animacion_Spaz_Tambalear() : Animacion() {}

void Animacion_Spaz_Tambalear::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_TAMBALEAR, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Spaz_Tambalear::~Animacion_Spaz_Tambalear() {}