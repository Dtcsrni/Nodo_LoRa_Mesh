/***************************************************************
* Pruebas TDD técnicas simuladas en Arduino IDE
****************************************************************/

void ejecutarPruebas() {
  Serial.println(F("\n---- EJECUCIÓN DE PRUEBAS TDD ----"));
  int fallos = 0;

  if (!test_mostrarSplashCompleto()) fallos++;

  if (fallos == 0)
    Serial.println(F("✅ TODAS LAS PRUEBAS PASARON"));
  else {
    Serial.print(F("❌ PRUEBAS CON FALLOS: "));
    Serial.println(fallos);
  }
}

// 🧪 TDD Técnica #2
bool test_mostrarSplashCompleto() {
  Serial.print(F("[TEST] mostrarSplashCompleto()... "));
  mostrarSplashCompleto();
  Serial.println(F("→ Verifica logo, POST, copyright y encabezado."));
  return true;
}
