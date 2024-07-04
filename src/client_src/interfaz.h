#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "SDL2pp/SDL2pp.hh"
#include "SDL2pp/SDLTTF.hh"
#include "../src/client_src/Vista_Personajes/personajeView.h"

class Interfaz {
    private:
        int ancho_ventana;
        int alto_ventana;
        SDL2pp::Rect rect;
        SDL2pp::SDLTTF sdl_ttf;
        SDL2pp::Font font;
        std::map<std::string, SDL2pp::Texture*> texturas;
        uint32_t id_jugador;
        std::string texto;
        uint16_t tiempo;
        uint32_t puntos;
        std::vector<std::pair<uint32_t, uint32_t>> puntajes;

        void mostrar_vida(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr);
        void mostrar_tiempo(SDL2pp::Renderer &render);
        void mostrar_puntaje_jugador(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr);
        void mostrar_top_puntajes(SDL2pp::Renderer &render, std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews);
        void mostrar_municiones(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr);
        void mostrar_tipo_bala(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr);

        void mostrar_texto(SDL2pp::Renderer &render, const std::string &texto, SDL_Color color, int x, int y, int w, int h);
        void mostrar_tabla_puntajes(SDL2pp::Renderer &render);
        void mostrar_mensaje_final(SDL2pp::Renderer &render);
    public:
        explicit Interfaz(SDL2pp::Renderer &render, int ancho, int alto, uint32_t id_jugador);

        void definir_tiempo(uint16_t tiempo);

        void definir_puntaje(uint32_t puntaje);

        void mostrar_hud(SDL2pp::Renderer &render, std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews);

        void mostrar_tabla_final(SDL2pp::Renderer &render);

        ~Interfaz();
};



#endif