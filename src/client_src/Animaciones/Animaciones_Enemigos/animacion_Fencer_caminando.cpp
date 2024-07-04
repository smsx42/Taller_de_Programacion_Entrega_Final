#include "animacion_Fencer_caminando.h"

Animacion_Fencer_Caminando::Animacion_Fencer_Caminando() : Animacion() {}


void Animacion_Fencer_Caminando::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_FENCER_CAMINANDO, render)));
    this->size_frame = 70;
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
    
}

Animacion_Fencer_Caminando::~Animacion_Fencer_Caminando() {}