/***************************************************************
* Función: mostrarLogoInicio()
* Descripción: Muestra el logo del sistema y mensaje de arranque
****************************************************************/

void mostrarLogoInicio() {
  tft.st7735_fill_screen(ST7735_BLACK);
  int x = (ST7735_WIDTH - 96) / 2;
  int y = (ST7735_HEIGHT - 96) / 2 - 10;
  tft.st7735_draw_image(x, y, 96, 96, (const uint16_t*)logo_bitmap);

  tft.st7735_write_str((ST7735_WIDTH - 9 * 8) / 2, y + 96 + 6,
                       MENSAJE_CYBERSYS, Font_7x10, ST7735_CYAN, ST7735_BLACK);
  
  delay(500);

  tft.st7735_write_str(5, 150, MENSAJE_SISTEMA_LISTO,
                       Font_7x10, ST7735_GREEN, ST7735_BLACK);
}
