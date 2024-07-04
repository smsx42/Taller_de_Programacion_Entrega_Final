#include "animacion_Jazz_cayendo.h"

Animacion_Jazz_Cayendo::Animacion_Jazz_Cayendo() : Animacion() {}

void Animacion_Jazz_Cayendo::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_CAYENDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Jazz_Cayendo::~Animacion_Jazz_Cayendo() {}