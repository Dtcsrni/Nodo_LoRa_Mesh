#include "HT_st7735.h"
#include "Arduino.h"
#include "logo_bitmap_96x96.c"  // Incluye imagen embebida
HT_st7735 tft;

extern const uint16_t logo_bitmap[]; // Declaración

void mostrarLogo() {
    tft.st7735_fill_screen(ST7735_BLACK);
    yield();  // 👈 previene reinicio por watchdog

    int x = (ST7735_WIDTH - 96) / 2;
    int y = (ST7735_HEIGHT - 96) / 2 - 8;

    tft.st7735_draw_image(x, y, 96, 96, (const uint16_t*)logo_bitmap);
    tft.st7735_write_str((ST7735_WIDTH - 9 * 8) / 2, y + 96 + 4, "Cybersys",
                         Font_7x10, ST7735_CYAN, ST7735_BLACK);
    yield();
    delay(3000);  // Tiempo para carga de periféricos
}

void testFuentes() {
    tft.st7735_fill_screen(ST7735_BLACK);
    yield();
    tft.st7735_write_str(0, 0, "Font 7x10", Font_7x10, ST7735_YELLOW, ST7735_BLACK);
    tft.st7735_write_str(0, 18, "Font 11x18", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    delay(1500);
    yield();
}

void testColores() {
    uint16_t colores[] = {
        ST7735_BLACK, ST7735_BLUE, ST7735_RED, ST7735_GREEN,
        ST7735_CYAN, ST7735_MAGENTA, ST7735_YELLOW, ST7735_WHITE
    };
    const char* nombres[] = {
        "BLACK", "BLUE", "RED", "GREEN", "CYAN", "MAGENTA", "YELLOW", "WHITE"
    };

    for (int i = 0; i < 8; i++) {
        tft.st7735_fill_screen(colores[i]);
        yield();
        tft.st7735_write_str(5, 10, nombres[i], Font_11x18,
            (colores[i] == ST7735_BLACK ? ST7735_WHITE : ST7735_BLACK),
            colores[i]
        );
        delay(600);
    }
}

void setup() {
    Serial.begin(115200);
    tft.st7735_init();
    Serial.println("✅ Pantalla inicializada correctamente.");

    mostrarLogo();      // Splash + carga
    testFuentes();      // Prueba de fuentes
    testColores();      // Prueba de colores

    // Estado final
    tft.st7735_fill_screen(ST7735_BLACK);
    tft.st7735_write_str(10, 10, "HELTEC V3 OK", Font_11x18, ST7735_GREEN, ST7735_BLACK);
    tft.st7735_write_str(10, 30, "Listo para sensores", Font_7x10, ST7735_WHITE, ST7735_BLACK);
}

void loop() {
    // Nada por ahora
}
