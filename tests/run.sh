#!/usr/bin/env bash

# Ruta al directorio donde se encuentran los ejecutables de prueba
TEST_DIR="./tests"

# Verifica si el directorio de pruebas existe
if [ ! -d "$TEST_DIR" ]; then
    echo "Error: El directorio de pruebas '$TEST_DIR' no existe. Intenta compilar con cmake testing"
    exit 1
fi

# Contadores de pruebas
TOTAL_TESTS=0
FAILED_TESTS=0

# Itera sobre todos los ejecutables de prueba en el directorio
for TEST_EXECUTABLE in $(ls $TEST_DIR/test_* | grep -v 'CMakeLists.txt'); do
    if [ -x "$TEST_EXECUTABLE" ]; then
        echo "Ejecutando prueba: $TEST_EXECUTABLE"
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        # Ejecuta el test
        "$TEST_EXECUTABLE"
        # Verifica el código de salida del test
        EXIT_CODE=$?
        if [ $EXIT_CODE -ne 0 ]; then
            echo "Error en la prueba: $TEST_EXECUTABLE"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    fi
done

echo ""
echo ""
echo "Total de archivos de pruebas ejecutados: $TOTAL_TESTS"
echo ""
echo ""


if [ $FAILED_TESTS -ne 0 ]; then
    echo "Archivos con pruebas fallidas: $FAILED_TESTS"
    echo ""
    exit 1
else
    echo "Todos los tests han sido ejecutados exitosamente"
fi