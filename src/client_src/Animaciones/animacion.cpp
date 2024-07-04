#include "../src/client_src/Animaciones/animacion.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

Animacion::Animacion() : texturas(nullptr), frame_actual(0),
cantidad_frames(1), 
size_frame(1), elapsed(0.0F),
loop(true){}

Animacion::~Animacion() {}

SDL2pp::Texture Animacion::crear_surface_y_texturas(std::string const &path_sprites, SDL2pp::Renderer *render) {
    SDL2pp::Surface surface(path_sprites);
    surface.SetColorKey(true, SDL_MapRGB(surface.Get()->format, 44, 102, 150));
    SDL2pp::Texture textures(*render, std::move(surface));

    return std::move(textures);
}

void Animacion::set_size_frames_y_cantida_frames() {
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

void Animacion::acualizar(float dt) {
    this->elapsed += dt;

    while(this->elapsed >= FRAME_RATE) {
        if (not this->loop and this->frame_actual == this->cantidad_frames - 1) {
            
        }else {
            this->frame_actual += 1;
            this->frame_actual = this->frame_actual % this->cantidad_frames; 

        }
        this->elapsed -= FRAME_RATE;
        

    }
}

 void Animacion::en_loop(bool booleano) {
    this->loop = booleano;
}

void Animacion::reset_frame() {
    this->frame_actual = 0;
    this->elapsed = 0;
    this->loop = true;
}

void Animacion::animar(SDL2pp::Renderer &render, SDL2pp::Rect dest, SDL_RendererFlip &flipType) {
    
    render.Copy(*texturas,
    SDL2pp::Rect((this->size_frame * this->frame_actual), 0, this->size_frame, texturas->GetHeight()),
    dest, 0.0, SDL2pp::NullOpt, flipType);
    
}

