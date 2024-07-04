#include "animacion_Bruja_caminando.h"

Animacion_Bruja_Caminando::Animacion_Bruja_Caminando() : Animacion() {}


void Animacion_Bruja_Caminando::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_BRUJA_CAMINANDO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
    
}

Animacion_Bruja_Caminando::~Animacion_Bruja_Caminando() {}