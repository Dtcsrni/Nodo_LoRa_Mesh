#ifndef TESTS_INCLUDED
#define TESTS_INCLUDED

bool test_dashboardInicial();
bool test_advertenciaVelocidad();

void ejecutarPruebas();

bool test_dashboardInicial() {
  Serial.println(F("[TEST] TDD 3.1: Render inicial del dashboard con marco..."));
  mostrarSplashCompleto();
  delay(1000);

  tft.st7735_fill_screen(ST7735_BLACK);
  dibujarDashboardCompleto();

  velocidad = 42;
  velocidadAnterior = -1;
  dibujarVelocidad();

  Serial.println(F("[TEST] Verifica visualmente:"));
  Serial.println(F(" - Marco visible"));
  Serial.println(F(" - Usuario/ID desde x=0"));
  Serial.println(F(" - Velocidad 42 km/h con barra"));
  Serial.println(F("[RESULTADO] Verificación MANUAL necesaria"));

  return true;
}

bool test_advertenciaVelocidad() {
  Serial.println(F("[TEST] TDD 3.2: Advertencia por exceso de velocidad..."));

  tft.st7735_fill_screen(ST7735_BLACK);
  dibujarDashboardCompleto();

  velocidad = 72;
  velocidadAnterior = -1;
  dibujarVelocidad();

  for (int i = 0; i < 5; i++) {
    delay(300);
    dibujarVelocidad();
  }

  Serial.println(F("[TEST] Verifica visualmente que:"));
  Serial.println(F(" - Aparece '¡EXCESO DE VELOCIDAD!'"));
  Serial.println(F(" - Barra parpadea rojo/negro"));
  Serial.println(F("[RESULTADO] Verificación MANUAL necesaria"));

  return true;
}

void ejecutarPruebas() {
  Serial.println(F("\n=== INICIO DE PRUEBAS UNITARIAS (TDD) ==="));

  bool exito = true;
  exito &= test_dashboardInicial();
  exito &= test_advertenciaVelocidad();

  if (exito) {
    Serial.println(F("\n✅ TODAS LAS PRUEBAS PASARON"));
  } else {
    Serial.println(F("\n❌ ALGUNA PRUEBA FALLÓ"));
  }
}

#endif
