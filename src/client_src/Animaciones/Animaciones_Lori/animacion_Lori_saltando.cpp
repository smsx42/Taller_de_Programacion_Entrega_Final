#include "animacion_Lori_saltando.h"

Animacion_Lori_Saltando::Animacion_Lori_Saltando() : Animacion() {}

void Animacion_Lori_Saltando::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_SALTANDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Saltando::~Animacion_Lori_Saltando() {}