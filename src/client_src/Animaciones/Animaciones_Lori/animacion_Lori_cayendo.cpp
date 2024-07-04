#include "animacion_Lori_cayendo.h"

Animacion_Lori_Cayendo::Animacion_Lori_Cayendo() : Animacion() {}

void Animacion_Lori_Cayendo::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_CAYENDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Cayendo::~Animacion_Lori_Cayendo() {}