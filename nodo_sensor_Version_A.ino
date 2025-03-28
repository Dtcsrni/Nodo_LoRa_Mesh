// Sketch optimizado con FreeRTOS para Nodo A - Heltec V3 + ST7735
// Estructura modular con código limpio, eficiente y mantenible

#include "HT_st7735.h"
#include "Arduino.h"
#include "logo_bitmap_96x96.c"
#include "mensajes_es.h"  // Idioma por defecto: español

#define ST7735_DARKGREY 0x7BEF
#define MODO_SIMULACION true

HT_st7735 tft;

// -----------------------------
// Variables configurables
// -----------------------------
String idiomaActual = "es"; // Idioma configurable remotamente
String nombreUsuario = "Renato";
String idVehiculo = "CYB-001";

// -----------------------------
// Variables en tiempo real
// -----------------------------
volatile int velocidad = 0;
volatile int nivelBateria = 100;
volatile char direccionCardinal[4] = "N";
volatile bool estadoConexionLoRa = true;

int velocidadAnterior = -1;
int bateriaAnterior = -1;
String direccionAnterior = "";
bool conexionAnterior = !estadoConexionLoRa;

// -----------------------------
void mostrarLogoInicio() {
  tft.st7735_fill_screen(ST7735_BLACK);
  int x = (ST7735_WIDTH - 96) / 2;
  int y = (ST7735_HEIGHT - 96) / 2 - 10;
  tft.st7735_draw_image(x, y, 96, 96, (const uint16_t*)logo_bitmap);
  tft.st7735_write_str((ST7735_WIDTH - 9 * 8) / 2, y + 96 + 6, MENSAJE_CYBERSYS, Font_7x10, ST7735_CYAN, ST7735_BLACK);

  unsigned long t0 = millis();
  while (millis() - t0 < 1800) {
    if (millis() - t0 > 200 && millis() - t0 < 600)
      tft.st7735_write_str(5, 130, MENSAJE_INICIAL_SENSORES, Font_7x10, ST7735_WHITE, ST7735_BLACK);
    if (millis() - t0 > 600 && millis() - t0 < 1000)
      tft.st7735_write_str(5, 140, MENSAJE_CONFIGURANDO_LORA, Font_7x10, ST7735_WHITE, ST7735_BLACK);
    if (millis() - t0 > 1000)
      tft.st7735_write_str(5, 150, MENSAJE_SISTEMA_LISTO, Font_7x10, ST7735_GREEN, ST7735_BLACK);
    delayMicroseconds(500);
    yield();
  }
}

void dibujarMarcoSistema() {
  uint16_t color = (!estadoConexionLoRa) ? ST7735_RED : (nivelBateria < 20 ? ST7735_YELLOW : ST7735_GREEN);
  tft.st7735_fill_rectangle(0, 0, 128, 3, color);
}

void dibujarEncabezadoUsuario() {
  tft.st7735_fill_rectangle(0, 4, 128, 22, ST7735_BLACK);
  tft.st7735_write_str(5, 6, (ICONO_USUARIO + nombreUsuario).c_str(), Font_7x10, ST7735_CYAN, ST7735_BLACK);
  tft.st7735_write_str(5, 16, (MENSAJE_ID + idVehiculo).c_str(), Font_7x10, ST7735_WHITE, ST7735_BLACK);
}

void dibujarVelocidad() {
  if (velocidad == velocidadAnterior) return;
  velocidadAnterior = velocidad;
  uint16_t color = (velocidad <= 30) ? ST7735_GREEN : (velocidad <= 60) ? ST7735_YELLOW : ST7735_RED;
  tft.st7735_fill_rectangle(0, 28, 128, 18, ST7735_BLACK);
  char buffer[32];
  sprintf(buffer, MENSAJE_VELOCIDAD, velocidad);
  tft.st7735_write_str(5, 30, buffer, Font_7x10, color, ST7735_BLACK);
  int barra = map(velocidad, 0, 100, 0, 100);
  tft.st7735_fill_rectangle(5, 44, 118, 8, ST7735_DARKGREY);
  tft.st7735_fill_rectangle(5, 44, barra, 8, color);
}

void dibujarDireccion() {
  char direccionTemp[4];
  strncpy(direccionTemp, (const char*)direccionCardinal, sizeof(direccionTemp));
  String direccionActual(direccionTemp);
  if (direccionActual == direccionAnterior) return;
  direccionAnterior = direccionActual;
  tft.st7735_fill_rectangle(0, 54, 128, 14, ST7735_BLACK);
  String flecha = "?";
  uint16_t color = ST7735_WHITE;
  if (direccionActual == "N") flecha = "↑";
  else if (direccionActual == "S") { flecha = "↓"; color = ST7735_BLUE; }
  else if (direccionActual == "E") { flecha = "→"; color = ST7735_RED; }
  else if (direccionActual == "W") { flecha = "←"; color = ST7735_CYAN; }
  else if (direccionActual == "NE") flecha = "↗";
  else if (direccionActual == "NW") flecha = "↖";
  else if (direccionActual == "SE") flecha = "↘";
  else if (direccionActual == "SW") flecha = "↙";
  tft.st7735_write_str(5, 56, (ICONO_BRUJULA + flecha + " " + direccionActual).c_str(), Font_7x10, color, ST7735_BLACK);
}

void dibujarBateria() {
  if (nivelBateria == bateriaAnterior) return;
  bateriaAnterior = nivelBateria;
  tft.st7735_fill_rectangle(0, 70, 128, 14, ST7735_BLACK);
  char buffer[20];
  sprintf(buffer, MENSAJE_BATERIA, nivelBateria);
  uint16_t color = (nivelBateria > 60) ? ST7735_GREEN : (nivelBateria > 30) ? ST7735_YELLOW : ST7735_RED;
  tft.st7735_write_str(5, 72, buffer, Font_7x10, color, ST7735_BLACK);
  int barra = map(nivelBateria, 0, 100, 0, 80);
  tft.st7735_fill_rectangle(90, 74, 80, 6, ST7735_DARKGREY);
  tft.st7735_fill_rectangle(90, 74, barra, 6, color);
}

void dibujarConexionLoRa() {
  if (conexionAnterior == estadoConexionLoRa) return;
  conexionAnterior = estadoConexionLoRa;
  tft.st7735_fill_rectangle(0, 86, 128, 14, ST7735_BLACK);
  String estado = estadoConexionLoRa ? MENSAJE_LORA_CONECTADO : MENSAJE_LORA_DESCONECTADO;
  uint16_t color = estadoConexionLoRa ? ST7735_GREEN : ST7735_RED;
  tft.st7735_write_str(5, 88, (ICONO_LORA + estado).c_str(), Font_7x10, color, ST7735_BLACK);
}

void tareaModoSimulacion(void *pvParameters) {
  const TickType_t intervalo = pdMS_TO_TICKS(1000);
  const char* direcciones[] = {"N", "S", "E", "W", "NE", "NW", "SE", "SW"};
  while (true) {
    if (MODO_SIMULACION) {
      velocidad = (velocidad + random(5, 12)) % 101;
      nivelBateria = std::max(0, (int)(nivelBateria - random(0, 2)));
      estadoConexionLoRa = (random(0, 10) > 1);
      strncpy((char*)direccionCardinal, direcciones[random(0, 8)], 4);
    }
    vTaskDelay(intervalo);
  }
}

void tareaDashboard(void *pvParameters) {
  for (;;) {
    dibujarMarcoSistema();
    dibujarVelocidad();
    dibujarDireccion();
    dibujarBateria();
    dibujarConexionLoRa();
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}

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
  vTaskDelete(NULL);
}
