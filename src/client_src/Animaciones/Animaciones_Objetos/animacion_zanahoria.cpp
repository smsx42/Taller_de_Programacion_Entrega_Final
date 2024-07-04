#include "animacion_zanahoria.h"

Animacion_Zanahoria::Animacion_Zanahoria() : Animacion() {}

void Animacion_Zanahoria::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_ZANAHORIA, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Zanahoria::~Animacion_Zanahoria() {}