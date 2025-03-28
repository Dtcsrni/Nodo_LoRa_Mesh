/***************************************************************
* Proyecto: Nodo IoT con LoRa Mesh para Monitoreo de Flotas Móviles
* Autor: I.S.C. Erick Renato Vega Cerón
* Archivo: nodo_sensor_Version_A.ino
* Versión: 0.1-TDD
* Fecha: Marzo/2025
****************************************************************/

#include "HT_st7735.h"
#include "mensajes_es.h"
#include "logo_bitmap_96x96.c"


HT_st7735 tft;

extern void mostrarSplashCompleto();
extern void ejecutarPruebas();

void setup() {
  Serial.begin(115200);
  delay(300);
  tft.st7735_init();
  ejecutarPruebas(); // Punto de entrada a pruebas TDD
}

void loop() {
  vTaskDelete(NULL); // No usado en pruebas
}
