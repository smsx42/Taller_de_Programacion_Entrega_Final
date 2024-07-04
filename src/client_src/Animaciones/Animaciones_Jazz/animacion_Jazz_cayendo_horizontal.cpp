#include "animacion_Jazz_cayendo_horizontal.h"

Animacion_Jazz_Cayendo_Horizontal::Animacion_Jazz_Cayendo_Horizontal() : Animacion() {}

void Animacion_Jazz_Cayendo_Horizontal::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_CAYENDO_HORIZONTAL, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Jazz_Cayendo_Horizontal::~Animacion_Jazz_Cayendo_Horizontal() {}