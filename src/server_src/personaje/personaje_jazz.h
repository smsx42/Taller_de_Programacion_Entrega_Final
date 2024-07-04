#ifndef SERVER_PERSONAJE_JAZZ_H_
#define SERVER_PERSONAJE_JAZZ_H_

#include <map>
#include "personaje.h"


class Jazz: public Personaje {
private:
public:
    explicit Jazz(uint32_t id_jugador, std::vector<SpawnPoint> spawns);

    uint8_t obtener_personaje() override;

    void usar_habilidad(std::chrono::duration<double> tiempo_transcurrido) override;

    void actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido,
                             std::map<uint32_t, Objeto*>& map_objetos, std::map<uint32_t, std::unique_ptr<Objeto>>& map_objetos_comunes) override;
};


#endif
