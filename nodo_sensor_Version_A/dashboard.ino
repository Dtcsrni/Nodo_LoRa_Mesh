#include "variables_globales.h"
#include "mensajes_es.h"

unsigned long tiempoUltimoParpadeo = 0;
bool estadoParpadeo = false;
bool excesoPrevio = false;

// Fade-out de alerta
unsigned long tiempoUltimaAlerta = 0;
const unsigned long DURACION_ALERTA_MS = 4000;
uint8_t nivelFade = 255;

/***************************************************************
* Funciones auxiliares de dibujo
****************************************************************/

void dibujarRectManual(int x, int y, int w, int h, uint16_t color) {
  for (int i = x; i < x + w; i++) {
    for (int j = y; j < y + h; j++) {
      tft.st7735_draw_pixel(i, j, color);
    }
  }
}

void dibujarLineaHorizontal(int x, int y, int longitud, uint16_t color) {
  for (int i = x; i < x + longitud; i++) {
    tft.st7735_draw_pixel(i, y, color);
  }
}

void dibujarLineaVertical(int x, int y, int altura, uint16_t color) {
  for (int j = y; j < y + altura; j++) {
    tft.st7735_draw_pixel(x, j, color);
  }
}

void dibujarBarraSuavizada(int x, int y, int longitud, uint16_t color) {
  if (longitud <= 0) return;
  for (int j = 0; j < 6; j++) {
    dibujarLineaHorizontal(x, y + j, longitud, color);
  }
}

/***************************************************************
* Marco y separadores
****************************************************************/

void dibujarMarcoPantalla() {
  uint16_t c = ST7735_WHITE;
  dibujarLineaHorizontal(0, 0, ST7735_WIDTH, c);
  dibujarLineaHorizontal(0, ST7735_HEIGHT - 1, ST7735_WIDTH, c);
  dibujarLineaVertical(0, 0, ST7735_HEIGHT, c);
  dibujarLineaVertical(ST7735_WIDTH - 1, 0, ST7735_HEIGHT, c);
}

void dibujarSeparadorHorizontal(int y, uint16_t color) {
  dibujarLineaHorizontal(1, y, ST7735_WIDTH - 2, color);
}

/***************************************************************
* Encabezado de usuario
****************************************************************/

void dibujarEncabezadoUsuario() {
  tft.st7735_fill_rectangle(1, 1, 126, 22, ST7735_BLACK);
  String lineaUsuario = ETIQUETA_USUARIO + nombreUsuario;
  String lineaID = ETIQUETA_ID + idVehiculo;

  tft.st7735_write_str(2, 4, lineaUsuario.c_str(), Font_7x10, ST7735_CYAN, ST7735_BLACK);
  tft.st7735_write_str(2, 14, lineaID.c_str(), Font_7x10, ST7735_WHITE, ST7735_BLACK);
}

/***************************************************************
* Visualización de velocidad y advertencia
****************************************************************/

void dibujarVelocidad() {
  if (velocidad == velocidadAnterior) return;

  int barraNueva = map(velocidad, 0, VEL_MAXIMA_URBANA, 0, 118);
  barraNueva = constrain(barraNueva, 0, 118);

  uint16_t color = (velocidad <= 30) ? ST7735_GREEN :
                   (velocidad <= 50) ? ST7735_YELLOW : ST7735_RED;

  bool excesoActual = (velocidad > VEL_MAXIMA_URBANA);
  if (excesoActual) {
    unsigned long ahora = millis();
    if (ahora - tiempoUltimoParpadeo > 300) {
      estadoParpadeo = !estadoParpadeo;
      tiempoUltimoParpadeo = ahora;
    }
    color = estadoParpadeo ? ST7735_RED : ST7735_BLACK;
  }

  char buffer[32];
  sprintf(buffer, ETIQUETA_VELOCIDAD, velocidad);
  tft.st7735_write_str(2, 28, buffer, Font_7x10, color, ST7735_BLACK);

  dibujarBarraSuavizada(2, 40, 118, ST7735_DARKGREY);
  dibujarBarraSuavizada(2, 40, barraNueva, color);

  if (excesoActual) {
    tft.st7735_write_str(2, 54, MENSAJE_EXCESO_VELOCIDAD, Font_7x10, ST7735_RED, ST7735_BLACK);
  } else if (excesoPrevio) {
    dibujarRectManual(2, 54, 124, 12, ST7735_BLACK);
  }

  excesoPrevio = excesoActual;
  velocidadAnterior = velocidad;
}

/***************************************************************
* Alerta contextual con fade-out y barra de tiempo visual
****************************************************************/

void dibujarAlertaSistema() {
  static String alertaAnterior = "";

  if ((millis() - tiempoUltimaAlerta > DURACION_ALERTA_MS) && alertaActual.length() > 0) {
    alertaActual = "";
    nivelFade = 255;
  }

  bool debeRedibujar = (alertaActual != alertaAnterior || nivelFade < 255);

  if (debeRedibujar) {
    tft.st7735_fill_rectangle(1, 66, 126, 12, ST7735_BLACK);

    if (alertaActual.length() > 0) {
      uint16_t colorTexto = ST7735_WHITE;
      uint16_t colorFondo = ST7735_BLACK;

      if (alertaActual == MENSAJE_BATERIA_BAJA || alertaActual == MENSAJE_SIN_GPS) {
        colorTexto = ST7735_WHITE;
        colorFondo = ST7735_RED;
      } else if (alertaActual == MENSAJE_TOPE || alertaActual == MENSAJE_FRENADO_BRUSCO) {
        colorTexto = ST7735_BLACK;
        colorFondo = ST7735_YELLOW;
      }

      unsigned long restante = DURACION_ALERTA_MS - (millis() - tiempoUltimaAlerta);
      restante = constrain(restante, 0, DURACION_ALERTA_MS);
      nivelFade = map(restante, 0, DURACION_ALERTA_MS, 64, 255);

      uint8_t r = ((colorFondo >> 11) & 0x1F) * nivelFade / 255;
      uint8_t g = ((colorFondo >> 5) & 0x3F) * nivelFade / 255;
      uint8_t b = (colorFondo & 0x1F) * nivelFade / 255;
      uint16_t colorFade = (r << 11) | (g << 5) | b;

      tft.st7735_fill_rectangle(1, 66, 126, 12, colorFade);
      tft.st7735_write_str(2, 68, alertaActual.c_str(), Font_7x10, colorTexto, colorFade);

      // Barra de progreso tiempo restante
      int anchoBarra = map(restante, 0, DURACION_ALERTA_MS, 0, 124);
      tft.st7735_fill_rectangle(2, 77, anchoBarra, 2, ST7735_WHITE);
    }

    alertaAnterior = alertaActual;
  }
}

/***************************************************************
* Zona especial de mensajes del sistema (parte inferior)
****************************************************************/

void mostrarMensajeSistema(const String& texto) {
  const int yBase = 112;
  const int altoZona = 48;
  const int anchoMax = 24;

  tft.st7735_fill_rectangle(1, yBase, 126, altoZona, ST7735_BLACK);

  String linea1 = texto;
  String linea2 = "";

  if (texto.length() > anchoMax) {
    linea1 = texto.substring(0, anchoMax);
    linea2 = texto.substring(anchoMax, min((int)texto.length(), 2 * anchoMax));
  }

  tft.st7735_write_str(2, yBase + 6, linea1.c_str(), Font_7x10, ST7735_WHITE, ST7735_BLACK);
  if (linea2.length() > 0) {
    tft.st7735_write_str(2, yBase + 18, linea2.c_str(), Font_7x10, ST7735_WHITE, ST7735_BLACK);
  }
}

/***************************************************************
* Dibujado completo del dashboard inicial
****************************************************************/

void dibujarDashboardCompleto() {
  dibujarMarcoPantalla();
  dibujarEncabezadoUsuario();
  dibujarSeparadorHorizontal(24, ST7735_WHITE);
  dibujarVelocidad();
  dibujarSeparadorHorizontal(52, ST7735_WHITE);
  dibujarAlertaSistema();
}

/***************************************************************
* Tarea FreeRTOS para actualización en tiempo real
****************************************************************/

void tareaDashboard(void *pvParameters) {
  while (true) {
    dibujarVelocidad();
    dibujarAlertaSistema();
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}
