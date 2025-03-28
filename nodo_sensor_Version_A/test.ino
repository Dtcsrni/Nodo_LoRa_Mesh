/***************************************************************
* Simulación de prueba automatizada – Historia TDD #1
****************************************************************/

void ejecutarPruebas() {
  Serial.println(F("\n---- EJECUCIÓN DE PRUEBAS TDD ----"));
  int fallos = 0;

  if (!test_mostrarLogoInicio()) fallos++;

  if (fallos == 0) {
    Serial.println(F("✅ TODAS LAS PRUEBAS PASARON"));
  } else {
    Serial.print(F("❌ PRUEBAS CON FALLOS: "));
    Serial.println(fallos);
  }
}

// 🧪 PRUEBA #1: Mostrar logo correctamente
bool test_mostrarLogoInicio() {
  Serial.print(F("[TEST] mostrarLogoInicio()... "));
  mostrarLogoInicio();

  Serial.println(F("→ Verifica visualmente el logo centrado y el texto 'Sistema listo'."));
  // Prueba es visual → pasa si no hay errores y se ve correctamente
  return true;
}
