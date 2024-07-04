#include "animacion_proyectil_tipo_2.h"

Animacion_Proyectil_Tipo_2::Animacion_Proyectil_Tipo_2() : Animacion() {}

void Animacion_Proyectil_Tipo_2::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture> (new SDL2pp::Texture(crear_surface_y_texturas(PATH_PROYECTIL_TIPO_2, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Proyectil_Tipo_2::~Animacion_Proyectil_Tipo_2() {}