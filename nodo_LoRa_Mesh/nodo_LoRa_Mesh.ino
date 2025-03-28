// Sketch principal - Nodo A LoRa Mesh + ST7735
#include "HT_st7735.h"
#include "logo_bitmap_96x96.c"
#include "mensajes_es.h"

extern void mostrarLogoInicio();
extern void dibujarEncabezadoUsuario();
extern void tareaModoSimulacion(void*);
extern void tareaDashboard(void*);
extern HT_st7735 tft;

void setup() {
  Serial.begin(115200);
  tft.st7735_init();
  mostrarLogoInicio();
  tft.st7735_fill_screen(ST7735_BLACK);
  dibujarMarcoSistema();
  dibujarEncabezadoUsuario();
  dibujarVelocidad();
  dibujarDireccion();
  dibujarBateria();
  dibujarConexionLoRa();

  xTaskCreatePinnedToCore(tareaModoSimulacion, "ModoSim", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tareaDashboard, "Dashboard", 4096, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelete(NULL); // No se usa
}
