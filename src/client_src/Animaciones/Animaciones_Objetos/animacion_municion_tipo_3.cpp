#include "animacion_municion_tipo_3.h"

Animacion_municion_tipo_3::Animacion_municion_tipo_3() : Animacion() {}

void Animacion_municion_tipo_3::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_MUNICION_TIPO_3, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;

}

Animacion_municion_tipo_3::~Animacion_municion_tipo_3() {}