#include "variables_globales.h"
#include "mensajes_es.h"
#include "logo_bitmap.h"

/***************************************************************
* Función: mostrarSplashCompleto()
* Descripción: Muestra el splash completo con título, logo,
* mensajes tipo POST, copyright y limpieza final.
****************************************************************/
void mostrarSplashCompleto() {
  tft.st7735_fill_screen(ST7735_BLACK);

  // Título centrado arriba
  tft.st7735_write_str((ST7735_WIDTH - 8 * strlen(MENSAJE_CYBERSYS)) / 2,
                       2, MENSAJE_CYBERSYS, Font_7x10, ST7735_CYAN, ST7735_BLACK);

  // Logo centrado más abajo
  int x = (ST7735_WIDTH - 96) / 2;
  int y = 20;
  tft.st7735_draw_image(x, y, 96, 96, (const uint16_t*)logo_bitmap);

  // Mensajes estilo POST
  const char* pasos[] = {
    MENSAJE_POST_1,
    MENSAJE_POST_2,
    MENSAJE_POST_3,
    MENSAJE_POST_4,
    MENSAJE_POST_5,
    MENSAJE_LISTO
  };

  int numPasos = sizeof(pasos) / sizeof(pasos[0]);
  int yInicio = y + 96 + 4;

  for (int i = 0; i < numPasos && (yInicio + i * 11) < ST7735_HEIGHT - 14; i++) {
    String msg(pasos[i]);
    if (msg.length() > 22) msg = msg.substring(0, 22);  // truncar

    tft.st7735_write_str(2, yInicio + i * 11, msg.c_str(), Font_7x10, ST7735_WHITE, ST7735_BLACK);
    delay(300);
    yield();
  }

  // Mensaje de copyright
  tft.st7735_write_str(2, ST7735_HEIGHT - 10, MENSAJE_COPYRIGHT, Font_7x10, ST7735_DARKGREY, ST7735_BLACK);
  delay(1200);

  // Limpieza antes del dashboard
  tft.st7735_fill_screen(ST7735_BLACK);
  dibujarEncabezadoUsuario();
}
