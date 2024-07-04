#include "animacion_gema.h"

Animacion_Gema::Animacion_Gema() : Animacion() {}

void Animacion_Gema::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_GEMA, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Gema::~Animacion_Gema() {}