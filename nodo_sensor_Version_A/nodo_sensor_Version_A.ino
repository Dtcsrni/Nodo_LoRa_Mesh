#include "HT_st7735.h"
#include "Arduino.h"
#include "logo_bitmap.h"
#include "mensajes_es.h"
#include "variables_globales.h"

// Objeto global de pantalla
HT_st7735 tft;

// Prototipo de pruebas
void ejecutarPruebas();

/***************************************************************
* setup(): Inicialización con pruebas TDD activadas
****************************************************************/
void setup() {
  Serial.begin(115200);
  delay(100);
  tft.st7735_init();
  tft.st7735_fill_screen(ST7735_BLACK);

  mostrarSplashCompleto();
  delay(500);

    
  // Modo producción (comentado mientras se prueba)
  tft.st7735_fill_screen(ST7735_BLACK);
  dibujarDashboardCompleto();

  xTaskCreatePinnedToCore(tareaModoSimulacion, "Sim", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tareaDashboard, "Dash", 4096, NULL, 1, NULL, 1);
  
}

void loop() {
  vTaskDelete(NULL);
}
