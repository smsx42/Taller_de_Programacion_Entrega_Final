#ifndef MAPA_H
#define MAPA_H

#include "SDL2pp/SDL2pp.hh"
#include "camara.h"
#include "../common_src/evento.h"

class Mapa {
    private:
        MapaCompleto mapa;
        SDL2pp::Rect src;
        SDL2pp::Rect dest;
        std::map<std::string, SDL2pp::Texture*> texturas;
        int ancho_ventana;
        int alto_ventana;

    public:
        explicit Mapa(SDL2pp::Renderer &render, MapaCompleto &&map);

        void dibujar_fondo(SDL2pp::Renderer &render, Camara &camara);

        void dibujar_fondo_final(SDL2pp::Renderer &render);

        void dibujar_entidades(SDL2pp::Renderer &render, Camara &camara);

        ~Mapa();

};

#endif