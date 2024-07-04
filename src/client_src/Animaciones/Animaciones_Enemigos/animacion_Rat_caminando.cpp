#include "animacion_Rat_caminando.h"

Animacion_Rat_Caminando::Animacion_Rat_Caminando() : Animacion() {}


void Animacion_Rat_Caminando::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_RAT_CAMINANDO, render)));
    this->size_frame = 70;  //Ancho del frame
    this->cantidad_frames = texturas->GetWidth() / 70; // Ancho total / Ancho de cada frame
    
}

Animacion_Rat_Caminando::~Animacion_Rat_Caminando() {}