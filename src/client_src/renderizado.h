#ifndef RENDERIZADO_H
#define RENDERIZADO_H

#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "../common_src/evento.h"
#include "../common_src/codigo_enemigo.h"
#include "../common_src/codigo_objeto.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "../src/client_src/Vista_Personajes/personajeView.h"
#include "../src/client_src/Vista_Personajes/personajeJazzView.h"
#include "../src/client_src/Vista_Personajes/personajeLoriView.h"
#include "../src/client_src/Vista_Personajes/personajeSpazView.h"
#include "../src/client_src/Vista_Enemigos/enemigoView.h"
#include "../src/client_src/Vista_Enemigos/enemigoLizzardView.h"
#include "../src/client_src/Vista_Enemigos/enemigoFencerView.h"
#include "../src/client_src/Vista_Enemigos/enemigoRatView.h"
#include "../src/client_src/Vista_Enemigos/enemigoBrujaView.h"
#include "../src/client_src/Vista_Objetos/objetoView.h"
#include "../src/client_src/Vista_Objetos/objetoGemaView.h"
#include "../src/client_src/Vista_Objetos/objetoMonedaView.h"
#include "../src/client_src/Vista_Objetos/objetoZanahoriaView.h"
#include "../src/client_src/Vista_Objetos/objetoMunicionTipo_1View.h"
#include "../src/client_src/Vista_Objetos/objetoMunicionTipo_2View.h"
#include "../src/client_src/Vista_Objetos/objetoMunicionTipo_3View.h"
#include "direcciones.h"
#include "mapa.h"
#include "camara.h"
#include "../src/client_src/Vista_Proyectiles/balasPersonajes.h"
#include "interfaz.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Music.hh>


#include "protocolo_cliente.h"

class Renderizado {
    
   private:
    std::unique_ptr<SDL2pp::SDL> sdl;
    std::unique_ptr<SDL2pp::Window> window;
    std::unique_ptr<SDL2pp::Renderer> render;
    std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews;
    std::map<uint32_t, std::unique_ptr<EnemigoView>> enemigosViews;
    std::map<uint32_t, std::unique_ptr<ObjetoView>> objetosViews;
    std::unique_ptr<SDL2pp::Mixer> reproductor_audio;
    BalasPersonajes mapa_balas_pj;
    uint32_t id_jugador;
    std::unique_ptr<SDL2pp::Music> musica;
    int contador_musica;
    std::unique_ptr<Mapa> mapa;
    std::unique_ptr<Camara> camara;
    std::unique_ptr<Interfaz> interfaz;

   public:

    explicit Renderizado(std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews);
    
    virtual ~Renderizado();

    public: 

    void inicializar_SDL2pp();

    void recibir_id(uint32_t id_jugador);

    void crear_ventana_y_render(const std::string& title, int width, int height);

    void crear_reproductor_audio();

    bool renderizar(Evento evento);

    void iniciar_mapa(MapaCompleto &&map);

    void iniciar_camara(Camara &&cam);

    void iniciar_interfaz(int w, int h);

    void mostrar_tablero_final();
};

#endif
