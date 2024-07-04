#include "animacion_moneda.h"

Animacion_Moneda::Animacion_Moneda() : Animacion() {}

void Animacion_Moneda::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_MONEDA, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Moneda::~Animacion_Moneda() {}