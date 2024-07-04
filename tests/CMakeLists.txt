cmake_minimum_required(VERSION 3.16)
project(JazzJackRabbit2)


set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/configuracion.yaml")
set(CONFIG_CHEAT_FILE "${CMAKE_SOURCE_DIR}/configuracionCheats.yaml")
# Rutas comunes
set(COMMON_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/src/common_src" "${CMAKE_SOURCE_DIR}/src/server_src")
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/src/common_src/accion.h
    ${CMAKE_SOURCE_DIR}/src/server_src/configuracion.cpp
)
set(ESTADO_SOURCES
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_quieto.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_muerto.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_herido.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_especial.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_corriendo.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_caminando.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_saltando.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_cayendo.cpp
    ${CMAKE_SOURCE_DIR}/src/server_src/estado/estado_tambalear.cpp
)

# Define una función para configurar las pruebas
function(configure_test TEST_NAME TEST_TYPE NAME)
    add_executable(${TEST_NAME} test_${NAME}.cpp)
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main yaml-cpp)

    target_include_directories(${TEST_NAME} PUBLIC ${COMMON_INCLUDE_DIRS})
    if(TEST_TYPE STREQUAL "personaje")
        target_sources(${TEST_NAME} PRIVATE
            ${COMMON_SOURCES}
            ${ESTADO_SOURCES}
            ${CMAKE_SOURCE_DIR}/src/server_src/personaje/personaje.cpp
            ${CMAKE_SOURCE_DIR}/src/server_src/personaje/personaje_${NAME}.cpp
            ${CMAKE_SOURCE_DIR}/src/server_src/arma.cpp
            ${CMAKE_SOURCE_DIR}/src/server_src/bala/bala.cpp
        )
    elseif(TEST_TYPE STREQUAL "enemigo")
        target_sources(${TEST_NAME} PRIVATE
            ${COMMON_SOURCES}
            ${CMAKE_SOURCE_DIR}/src/common_src/codigo_enemigo.h
            ${CMAKE_SOURCE_DIR}/src/server_src/enemigo/enemigo.cpp
            ${CMAKE_SOURCE_DIR}/src/server_src/enemigo/enemigo_${NAME}.cpp
            ${CMAKE_SOURCE_DIR}/src/server_src/bala/bala.cpp
        )

    elseif(TEST_TYPE STREQUAL "bala")
        target_sources(${TEST_NAME} PRIVATE
        ${COMMON_SOURCES}
        ${CMAKE_SOURCE_DIR}/src/server_src/bala/bala.cpp
        ${CMAKE_SOURCE_DIR}/src/server_src/bala/controlador_balas.h
        )
        elseif(TEST_TYPE STREQUAL "rectangulo")
        target_sources(${TEST_NAME} PRIVATE
            ${COMMON_SOURCES}
            ${CMAKE_SOURCE_DIR}/src/server_src/rectangulo.h
        )

    elseif(TEST_TYPE STREQUAL "logica_partida")
        # Incluye todos los archivos .cpp dentro de src/server_src y sus subdirectorios
        file(GLOB_RECURSE SERVER_SOURCES "${CMAKE_SOURCE_DIR}/src/server_src/*.cpp")
        list(REMOVE_ITEM SERVER_SOURCES
            "${CMAKE_SOURCE_DIR}/src/server_src/main.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/monitorPartidas.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/monitorPartidas.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/aceptador.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/aceptador.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/enviadorJugador.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/enviadorJugador.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/protocoloServidor.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/protocoloServidor.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/recibidorJugador.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/recibidorJugador.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/servidor.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/servidor.h"
            "${CMAKE_SOURCE_DIR}/src/server_src/jugador.cpp"
            "${CMAKE_SOURCE_DIR}/src/server_src/jugador.h"
        )
        target_sources(${TEST_NAME} PRIVATE ${SERVER_SOURCES} ${COMMON_SOURCES} )
    endif()
    target_compile_definitions(${TEST_NAME} PUBLIC CONFIG_PATH="${CONFIG_FILE}")
    target_compile_definitions(${TEST_NAME} PUBLIC CONFIG_CHEAT_PATH="${CONFIG_CHEAT_FILE}")
endfunction()

# Configura las pruebas para los diferentes personajes
configure_test(test_personaje_jazz personaje jazz)
configure_test(test_personaje_spaz personaje spaz)
configure_test(test_personaje_lori personaje lori)

# Configura las pruebas para los diferentes enemigos
configure_test(test_enemigo_fencer enemigo fencer)
configure_test(test_enemigo_rat enemigo rat)
configure_test(test_enemigo_lizzard enemigo lizzard)
configure_test(test_enemigo_bruja enemigo bruja)

#Test de Bala
configure_test(test_bala bala bala)
configure_test(test_controlador_balas bala controlador_balas)

#Test Rectangulo
configure_test(test_rectangulo rectangulo rectangulo)

#Test LogicaPartida
configure_test(test_logica_partida logica_partida logica_partida)


