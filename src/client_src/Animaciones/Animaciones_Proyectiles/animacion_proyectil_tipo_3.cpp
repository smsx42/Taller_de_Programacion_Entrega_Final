#include "animacion_proyectil_tipo_3.h"

Animacion_Proyectil_Tipo_3::Animacion_Proyectil_Tipo_3() : Animacion() {}

void Animacion_Proyectil_Tipo_3::crear_texturas(SDL2pp::Renderer *render) {

    this->texturas = std::unique_ptr<SDL2pp::Texture> (new SDL2pp::Texture(crear_surface_y_texturas(PATH_PROYECTIL_TIPO_3, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Proyectil_Tipo_3::~Animacion_Proyectil_Tipo_3() {}