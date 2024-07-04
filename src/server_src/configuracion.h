#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <yaml-cpp/yaml.h>
#include "../common_src/codigo_objeto.h"


struct ConfigObjeto {
    uint32_t ancho;
    uint32_t alto;
    double tiempo_reaparicion;
    uint32_t vida_restaurada;
    uint32_t puntos_otorgados;
};

struct ConfigBala {
        uint16_t municion;
        double tiempo_entre_disparo;
        int velocidad_del_proyectil;
        uint8_t danio;
        uint32_t rango_explosion;
        uint32_t ancho;
        uint32_t largo;
        double tiempo_reaparicion;
};


class Configuracion {
private:
   uint8_t vida_personaje;
    int velocidad_x_personaje;
    int velocidad_y_personaje;
    int gravedad;
    double tiempo_invulnerabilidad;
    double tiempo_intoxicacion;
    int ancho_personaje;
    int alto_personaje;
    uint8_t puntos_personaje;

    // Atributos de habilidades por personaje
    double enfriamiento_habilidad_jazz;
    int velocidad_y_habilidad_jazz;
    double enfriamiento_habilidad_spaz;
    int velocidad_x_habilidad_spaz;
    double enfriamiento_habilidad_lori;
    int velocidad_x_habilidad_lori;
    int velocidad_y_habilidad_lori;
    uint8_t danio_habilidad_jazz;
    uint8_t danio_habilidad_spaz;
    uint8_t danio_habilidad_lori;

    //Atributos de partida

    int duracion_segundos;

    // Atributos de pantalla
    int ancho_pantalla;
    int alto_pantalla;

    // Atributos de estado

    double tiempo_estado_muerto;
    double tiempo_estado_herido;

    // Atributos de municion

    std::map<uint8_t, ConfigBala> config_balas;

    // Atributo de objeto

    std::map<uint8_t, ConfigObjeto> config_objetos;

    //Atributos de enemigos

    int vida_default_enemigo;
    int danio_default_enemigo;
    int velocidad_enemigo;
    int ancho_enemigo;
    int alto_enemigo;

    uint32_t puntos_fencer;
    int danio_fencer;
    int vida_fencer;
    int ancho_fencer;
    int alto_fencer;
    std::vector<int> probabilidad_vida_fencer;
    std::vector<int> probabilidad_municion_fencer;
    double tiempo_reaparicion_fencer;
    int velocidad_x_fencer;

    uint32_t puntos_lizzard;
    int danio_lizzard;
    int vida_lizzard;
    int ancho_lizzard;
    int alto_lizzard;
    std::vector<int> probabilidad_vida_lizzard;
    std::vector<int> probabilidad_municion_lizzard;
    double tiempo_reaparicion_lizzard;
    int velocidad_x_lizzard;

    uint32_t puntos_rat;
    int danio_rat;
    int ancho_rat;
    int alto_rat;
    int vida_rat;
    std::vector<int> probabilidad_vida_rat;
    std::vector<int> probabilidad_municion_rat;
    double tiempo_reaparicion_rat;
    int velocidad_x_rat;

    int vida_bruja;
    int ancho_bruja;
    int alto_bruja;
    uint32_t puntos_bruja;
    int danio_bruja;
    std::vector<int> probabilidad_vida_bruja;
    std::vector<int> probabilidad_municion_bruja;
    double tiempo_reaparicion_bruja;
    int velocidad_x_bruja;

    std::map<std::string, uint8_t> codigo_balas = {
            {"bala_normal", BALA_NORMAL},
            {"bala_veloz", BALA_VELOZ},
            {"cohete_rapido", COHETE_RAPIDO},
            {"cohete_toxico", COHETE_TOXICO}
    };

    std::map<std::string, uint8_t> codigo_objetos = {
            {"zanahoria", ZANAHORIA},
            {"gema", GEMA},
            {"moneda", MONEDA}
    };

    
    double tiempo_reaparicion_enemigo;
    
    Configuracion(const YAML::Node& config);
    static Configuracion* instance;
    static bool isLoaded;

public:
    static Configuracion& config();
    static void loadConfig(const bool cheats);
    static void destroyConfig();

    Configuracion(const Configuracion&) = delete;

    Configuracion& operator=(const Configuracion&) = delete;


    uint8_t getVidaPersonaje() const { return vida_personaje; }
    int getVelocidadXPersonaje() const { return velocidad_x_personaje; }
    int getVelocidadYPersonaje() const { return velocidad_y_personaje; }
    int getGravedad() const { return gravedad; }
    double getEnfriamientoHabilidadJazz() const { return enfriamiento_habilidad_jazz; }
    int getVelocidadYHabilidadJazz() const { return velocidad_y_habilidad_jazz; }
    double getEnfriamientoHabilidadSpaz() const { return enfriamiento_habilidad_spaz; }
    int getVelocidadXHabilidadSpaz() const { return velocidad_x_habilidad_spaz; }
    double getEnfriamientoHabilidadLori() const { return enfriamiento_habilidad_lori; }
    int getVelocidadXHabilidadLori() const { return velocidad_x_habilidad_lori; }
    int getVelocidadYHabilidadLori() const { return velocidad_y_habilidad_lori; }
    double getTiempoInvulnerabilidad() const { return tiempo_invulnerabilidad; }
    double getTiempoIntoxicacion() const { return tiempo_intoxicacion; }
    int getAnchoPersonaje() const { return ancho_personaje; }
    int getAltoPersonaje() const { return alto_personaje; }
    uint8_t getPuntosPersonaje() const { return puntos_personaje;}

    uint8_t getDanioHabilidadJazz() const { return danio_habilidad_jazz; }
    uint8_t getDanioHabilidadSpaz() const { return danio_habilidad_spaz; }
    uint8_t getDanioHabilidadLori() const { return danio_habilidad_lori; }


    //Getters para valores de partida
    int getDuracionPartida() const {return duracion_segundos;}

    // Getters para los valores de la pantalla
    int getAnchoPantalla() const { return ancho_pantalla; }
    int getAltoPantalla() const { return alto_pantalla; }

    // Getters para Estado
    double getTiempoEstadoMuerto() const {return tiempo_estado_muerto;}
    double getTiempoEstadoHerido() const {return tiempo_estado_herido;}

    // Getters para Municion
    const ConfigBala& obtenerBala(uint8_t codigo_bala) const {
        auto it = config_balas.find(codigo_bala);
        if (it != config_balas.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Bala no encontrada en la config.");
        }
    }

    // Getters para Objetos
    const ConfigObjeto& obtenerObjeto(uint8_t codigo_objeto) const {
        auto it = config_objetos.find(codigo_objeto);
        if (it != config_objetos.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Objeto no encontrado en la config.");
        }
    }

    std::map<std::string, uint8_t> obtenerBalas() const {return codigo_balas;}
    //Getters para enemigos
    int obtenerVidaDefaultEnemigo() const {return vida_default_enemigo;}
    int obtener_danio_default_enemigo() const {return danio_default_enemigo;}
    int obtenerVelocidadEnemigos() const {return velocidad_enemigo;}
    int obtenerAnchoEnemigo() const {return ancho_enemigo;}
    int obtenerAltoEnemigo() const {return alto_enemigo;}
    int obtenerVidaFencer() const {return vida_fencer;}
    int obtenerVidaLizzard() const {return vida_lizzard;}
    int obtenerVidaRat() const {return vida_rat;}
    double obtenerTiempoReaparicionEnemigo() const {return tiempo_reaparicion_enemigo;}
    uint32_t obtenerPuntosFencer() const {return puntos_fencer;}
    uint32_t obtenerPuntosLizzard() const {return puntos_lizzard;}
    uint32_t obtenerPuntosRat() const {return puntos_rat;}
    int obtenerDanioFencer() const {return danio_fencer;}
    int obtenerDanioLizzard() const {return danio_lizzard;}
    int obtenerDanioRat() const {return danio_rat;}

    int obtenerAltoFencer() const {return alto_fencer;}
    int obtenerAltoLizzard() const {return alto_lizzard;}
    int obtenerAltoRat() const {return alto_rat;}
    int obtenerAnchoFencer() const {return ancho_fencer;}
    int obtenerAnchoLizzard() const {return ancho_lizzard;}
    int obtenerAnchoRat() const {return ancho_rat;}

    int obtenerVidaBruja() const {return vida_bruja;}
    int obtenerDanioBruja() const {return danio_bruja;}
    int obtenerAnchoBruja() const {return ancho_bruja;}
    int obtenerAltoBruja() const {return alto_bruja;}
    uint32_t obtenerPuntosBruja() const {return puntos_bruja;}

    std::vector<int> obtenerProbabilidadVidaFencer() const {return probabilidad_vida_fencer;}
    std::vector<int> obtenerProbabilidadVidaLizzard() const {return probabilidad_vida_lizzard;}
    std::vector<int> obtenerProbabilidadVidaRat() const {return probabilidad_vida_rat;}
    std::vector<int> obtenerProbabilidadVidaBruja() const {return probabilidad_vida_bruja;}

    std::vector<int> obtenerProbabilidadMunicionFencer() const {return probabilidad_municion_fencer;}
    std::vector<int> obtenerProbabilidadMunicionLizzard() const {return probabilidad_municion_lizzard;}
    std::vector<int> obtenerProbabilidadMunicionRat() const {return probabilidad_municion_rat;}
    std::vector<int> obtenerProbabilidadMunicionBruja() const {return probabilidad_municion_bruja;}

    double obtenerReaparicionFencer() const {return tiempo_reaparicion_fencer;}
    double obtenerReaparicionLizzard() const {return tiempo_reaparicion_lizzard;}
    double obtenerReaparicionRat() const {return tiempo_reaparicion_rat;}
    double obtenerReaparicionBruja() const {return tiempo_reaparicion_bruja;}

    int obtenerVelocidadXFencer() const {return velocidad_x_fencer;}
    int obtenerVelocidadXLizzard() const {return velocidad_x_lizzard;}
    int obtenerVelocidadXRat() const {return velocidad_x_rat;}
    int obtenerVelocidadXBruja() const {return velocidad_x_bruja;}

};



#endif