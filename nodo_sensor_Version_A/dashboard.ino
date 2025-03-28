/***************************************************************
* Función: dibujarEncabezadoUsuario()
* Descripción: Muestra nombre de usuario e ID en la parte superior
****************************************************************/

void dibujarEncabezadoUsuario() {
  tft.st7735_fill_rectangle(0, 4, 128, 22, ST7735_BLACK);
  tft.st7735_write_str(5, 6, (ETIQUETA_USUARIO + nombreUsuario).c_str(),
                       Font_7x10, ST7735_CYAN, ST7735_BLACK);
  tft.st7735_write_str(5, 16, (ETIQUETA_ID + idVehiculo).c_str(),
                       Font_7x10, ST7735_WHITE, ST7735_BLACK);
}
