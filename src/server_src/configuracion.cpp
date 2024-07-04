#include "configuracion.h"
#include <fstream>
#include <iostream>

static const std::string configPath = CONFIG_PATH;
static const std::string configCheatsPath = CONFIG_CHEAT_PATH;

Configuracion* Configuracion::instance = nullptr;
bool Configuracion::isLoaded = false;

Configuracion& Configuracion::config() {
    if (!isLoaded) {
        throw std::runtime_error("Configuration file not loaded. Call loadConfig() first.");
    }
    return *instance;
}

void Configuracion::loadConfig(bool cheats) {
    if (!isLoaded) {
        if (cheats) {
            instance = new Configuracion(YAML::LoadFile(configCheatsPath));
        } else {
        instance = new Configuracion(YAML::LoadFile(configPath));
        }
        isLoaded = true;
    }
}

void Configuracion::destroyConfig() {
    if (isLoaded) {
        delete instance;
        instance = nullptr;
        isLoaded = false;
    }
}

Configuracion::Configuracion(const YAML::Node& config) {
         // Personaje

        
        vida_personaje = config["personaje"]["vida"].as<int>();
        velocidad_x_personaje = config["personaje"]["velocidad_x"].as<int>();
        velocidad_y_personaje = config["personaje"]["velocidad_y"].as<int>();
        gravedad = config["personaje"]["gravedad"].as<int>();
        tiempo_invulnerabilidad = config["personaje"]["tiempo_invulnerabilidad"].as<double>();
        tiempo_intoxicacion = config["personaje"]["tiempo_intoxicacion"].as<double>();
        ancho_personaje = config["personaje"]["ancho"].as<int>();
        alto_personaje = config["personaje"]["alto"].as<int>();
        puntos_personaje = config["personaje"]["puntos"].as<uint8_t>();

        // Habilidades por personaje
        enfriamiento_habilidad_jazz = config["jazz"]["enfriamiento_habilidad"].as<double>();
        velocidad_y_habilidad_jazz = config["jazz"]["velocidad_y_habilidad"].as<int>();

        enfriamiento_habilidad_spaz = config["spaz"]["enfriamiento_habilidad"].as<double>();
        velocidad_x_habilidad_spaz = config["spaz"]["velocidad_x_habilidad"].as<int>();

        enfriamiento_habilidad_lori = config["lori"]["enfriamiento_habilidad"].as<double>();
        velocidad_x_habilidad_lori = config["lori"]["velocidad_x_habilidad"].as<int>();
        velocidad_y_habilidad_lori = config["lori"]["velocidad_y_habilidad"].as<int>();

        danio_habilidad_jazz = config["jazz"]["danio_habilidad"].as<uint8_t>();
        danio_habilidad_spaz = config["spaz"]["danio_habilidad"].as<uint8_t>();
        danio_habilidad_lori = config["lori"]["danio_habilidad"].as<uint8_t>();

        //partida
        duracion_segundos = config["tiempo_partida"].as<int>();

        // Pantalla
        ancho_pantalla = config["pantalla"]["lim_x"].as<int>();
        alto_pantalla = config["pantalla"]["lim_y"].as<int>();

        // Estado

        tiempo_estado_muerto = config["estado"]["tiempo_estado_muerto"].as<double>();
        tiempo_estado_herido = config["estado"]["tiempo_estado_herido"].as<double>();
        
        // Municion

        for (const auto& entry : config["municion"]) {
            std::string codigo_bala_str = entry.first.as<std::string>();
            if (codigo_balas.find(codigo_bala_str) != codigo_balas.end()) {
                uint8_t codigo_bala = codigo_balas[codigo_bala_str];
                config_balas[codigo_bala] = ConfigBala{
                    entry.second["municion"].as<uint16_t>(),
                    entry.second["tiempo_entre_disparo"].as<double>(),
                    entry.second["velocidad_del_proyectil"].as<int>(),
                    entry.second["danio"].as<uint8_t>(),
                    entry.second["rango_explosion"].as<uint32_t>(),
                    entry.second["ancho"].as<uint32_t>(),
                    entry.second["largo"].as<uint32_t>(),
                    entry.second["tiempo_reaparicion"].as<double>(),
                };
            }
        }


        for (const auto& entry : config["objeto"]) {
            std::string codigo_objeto_str = entry.first.as<std::string>();
            if (codigo_objetos.find(codigo_objeto_str) != codigo_objetos.end()) {
                uint8_t codigo_objeto = codigo_objetos[codigo_objeto_str];
                ConfigObjeto config_objeto;
                config_objeto.ancho = entry.second["ancho"].as<uint32_t>();
                config_objeto.alto = entry.second["alto"].as<uint32_t>();
                config_objeto.tiempo_reaparicion = entry.second["tiempo_reaparicion"].as<double>();
                if (entry.second["vida_restaurada"]) {
                    config_objeto.vida_restaurada = entry.second["vida_restaurada"].as<uint32_t>();
                }
                if (entry.second["puntos_otorgados"]) {
                    config_objeto.puntos_otorgados = entry.second["puntos_otorgados"].as<uint32_t>();
                }
                config_objetos[codigo_objeto] = config_objeto;
            }
        }

        //Enemigos
        vida_default_enemigo = config["enemigo"]["vida_default"].as<int>();
        danio_default_enemigo = config["enemigo"]["danio_default"].as<int>();
        velocidad_enemigo = config ["enemigo"]["velocidad_default"].as<int>();
        ancho_enemigo = config["enemigo"]["ancho"].as<int>();
        alto_enemigo = config["enemigo"]["alto"].as<int>();

        danio_fencer = config["enemigo"]["fencer"]["danio"].as<int>();
        vida_fencer = config["enemigo"]["fencer"]["vida"].as<int>();
        puntos_fencer = config["enemigo"]["fencer"]["puntos"].as<uint32_t>();
        ancho_fencer = config["enemigo"]["fencer"]["ancho"].as<int>();
        alto_fencer = config["enemigo"]["fencer"]["alto"].as<int>();
        probabilidad_vida_fencer = config["enemigo"]["fencer"]["probabilidad_drop_vida"].as<std::vector<int>>();    
        probabilidad_municion_fencer = config["enemigo"]["fencer"]["probabilidad_drop_municion"].as<std::vector<int>>();    
        tiempo_reaparicion_fencer = config["enemigo"]["fencer"]["tiempo_reaparicion"].as<double>();
        velocidad_x_fencer = config["enemigo"]["fencer"]["velocidad_x"].as<int>();    


        danio_lizzard = config["enemigo"]["lizzard"]["danio"].as<int>();
        vida_lizzard = config["enemigo"]["lizzard"]["vida"].as<int>();
        puntos_lizzard = config["enemigo"]["lizzard"]["puntos"].as<uint32_t>();
        ancho_lizzard = config["enemigo"]["lizzard"]["ancho"].as<int>();
        alto_lizzard = config["enemigo"]["lizzard"]["alto"].as<int>();
        probabilidad_vida_lizzard = config["enemigo"]["lizzard"]["probabilidad_drop_vida"].as<std::vector<int>>();    
        probabilidad_municion_lizzard = config["enemigo"]["lizzard"]["probabilidad_drop_municion"].as<std::vector<int>>();    
        tiempo_reaparicion_lizzard = config["enemigo"]["lizzard"]["tiempo_reaparicion"].as<double>();
        velocidad_x_lizzard = config["enemigo"]["lizzard"]["velocidad_x"].as<int>();  

        danio_rat = config["enemigo"]["rat"]["danio"].as<int>();
        vida_rat = config["enemigo"]["rat"]["vida"].as<int>();
        puntos_rat = config["enemigo"]["rat"]["puntos"].as<uint32_t>();
        ancho_rat= config["enemigo"]["rat"]["ancho"].as<int>();
        alto_rat = config["enemigo"]["rat"]["alto"].as<int>();
        probabilidad_vida_rat = config["enemigo"]["rat"]["probabilidad_drop_vida"].as<std::vector<int>>();    
        probabilidad_municion_rat= config["enemigo"]["rat"]["probabilidad_drop_municion"].as<std::vector<int>>();    
        tiempo_reaparicion_rat = config["enemigo"]["rat"]["tiempo_reaparicion"].as<double>();
        velocidad_x_rat = config["enemigo"]["rat"]["velocidad_x"].as<int>();  

        danio_bruja = config["enemigo"]["bruja"]["danio"].as<int>();
        vida_bruja = config["enemigo"]["bruja"]["vida"].as<int>();
        puntos_bruja = config["enemigo"]["bruja"]["puntos"].as<uint32_t>();
        ancho_bruja = config["enemigo"]["bruja"]["ancho"].as<int>();
        alto_bruja = config["enemigo"]["bruja"]["alto"].as<int>();
        probabilidad_vida_bruja = config["enemigo"]["bruja"]["probabilidad_drop_vida"].as<std::vector<int>>();    
        probabilidad_municion_bruja = config["enemigo"]["bruja"]["probabilidad_drop_municion"].as<std::vector<int>>();    
        tiempo_reaparicion_bruja = config["enemigo"]["bruja"]["tiempo_reaparicion"].as<double>();
        velocidad_x_bruja = config["enemigo"]["bruja"]["velocidad_x"].as<int>();  
        

        tiempo_reaparicion_enemigo = config["enemigo"]["tiempo_reaparicion_enemigo"].as<double>();
    
}
