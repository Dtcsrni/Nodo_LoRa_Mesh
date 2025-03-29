#include "variables_globales.h"
#include "mensajes_es.h"

const int velocidadesSimuladas[60] = {
  0, 4, 8, 10, 12,
  16, 22, 28, 32, 35,
  34, 30, 28, 26, 25,
  30, 35, 40, 43, 45,
  38, 28, 18, 12, 20,
  30, 40, 45, 50, 52,
  55, 58, 60, 60, 55,
  48, 40, 35, 30, 28,
  22, 18, 15, 15, 20,
  25, 30, 35, 37, 40,
  42, 45, 38, 25, 10,
  4, 0, 0, 0, 0
};


// Opciones de alerta en texto (centralizado después)
const char* alertasSimuladas[60] = {
  "", "", "", "", "",              // arranque
  "", "", "", "", "",              // aceleración
  "", "", "", "", MENSAJE_TOPE,    // semáforo
  "", "", "", "", "",              // recta
  "", MENSAJE_TOPE, "", "",        // tope
  "", "", "", "", "",              // aceleración
  "", "", "", "", "",              // recta rápida
  "", "", MENSAJE_BATERIA_BAJA, "", "",  // tráfico
  "", "", "", "", MENSAJE_SIN_GPS, // curva
  "", "", "", "",                  // salida curva
  "", "", "", "",                  // recta
  MENSAJE_FRENADO_BRUSCO, "", "", "", "", "", "", ""
};

// Direcciones cardinales aleatorias
const char* direcciones[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};



void tareaModoSimulacion(void *pvParameters) {
  const TickType_t intervalo = pdMS_TO_TICKS(1000);
  int index = 0;

  while (true) {
    velocidad = velocidadesSimuladas[index];
    nivelBateria = max(0, nivelBateria - (int)random(0, 2));

    estadoConexionLoRa = (random(0, 10) > 1);

    // Dirección aleatoria
    strncpy((char*)direccionCardinal, direcciones[random(0, 8)], 4);

    // Simulación de alerta
    alertaActual = String(alertasSimuladas[index]);

    index = (index + 1) % 60;
    vTaskDelay(intervalo);
  }
}
