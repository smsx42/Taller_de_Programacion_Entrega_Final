#include "animacion_Jazz_disparo_saltando.h"

Animacion_Jazz_Disparo_Saltando::Animacion_Jazz_Disparo_Saltando() : Animacion() {}

void Animacion_Jazz_Disparo_Saltando::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_DISPARO_SALTANDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Jazz_Disparo_Saltando::~Animacion_Jazz_Disparo_Saltando() {}