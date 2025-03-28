// Archivo: iconos_graficos.c
// Definiciones gráficas de íconos embebidos para TFT ST7735 (10x10, RGB565)

#include <stdint.h>

// === ÍCONO 01: USUARIO ===
const uint16_t icono_usuario[100] = {
  0x0000,0x18C6,0x18C6,0x18C6,0x0000,0x18C6,0x18C6,0x18C6,0x0000,0x0000,
  0x18C6,0xFFFF,0xFFFF,0xFFFF,0x18C6,0xFFFF,0xFFFF,0xFFFF,0x18C6,0x0000,
  0x18C6,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x18C6,
  0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
  0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
  0x18C6,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x18C6,
  0x0000,0x18C6,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x18C6,0x0000,
  0x0000,0x0000,0x18C6,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x18C6,0x0000,0x0000,
  0x0000,0x0000,0x18C6,0x18C6,0xFFFF,0xFFFF,0x18C6,0x18C6,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x18C6,0x18C6,0x18C6,0x18C6,0x0000,0x0000,0x0000,
};

// === ÍCONO 02: LORA ===
const uint16_t icono_lora[100] = {
  0x0000,0x07E0,0x0000,0x07E0,0x0000,0x0000,0x07E0,0x0000,0x07E0,0x0000,
  0x07E0,0x0000,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x0000,0x07E0,0x0000,0x07E0,
  0xFFFF,0x0000,0x0000,0x0000,0xFFFF,0x0000,0x0000,0x0000,0x0000,0xFFFF,
  0x0000,0x0000,0xFFFF,0x0000,0x0000,0x0000,0xFFFF,0x0000,0x0000,0x0000,
  0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0xFFFF,
  0x0000,0x0000,0x0000,0xFFFF,0x0000,0xFFFF,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0xFFFF,0xFFFF,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x07E0,0x07E0,0x07E0,0x07E0,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x07E0,0x07E0,0x0000,0x07E0,0x07E0,0x0000,0x07E0,0x07E0,0x0000,
  0x0000,0x0000,0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF,0x0000,0x0000,0x0000,
};

// === ÍCONO 03: BATERÍA ===
const uint16_t icono_bateria[100] = {
  0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0xFFFF,0x07E0,0x07E0,0x07E0,0x07E0,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0xFFFF,0x07E0,0xFFFF,0xFFFF,0x07E0,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0xFFFF,0x07E0,0xFFFF,0xFFFF,0x07E0,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0xFFFF,0x07E0,0x07E0,0x07E0,0x07E0,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0xFFFF,0xFFFF,0xFFFF,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0xFFFF,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

// Continúa con los demás íconos aquí ↓↓↓↓↓↓↓↓
// icono_brujula
// icono_flecha_direccion
// icono_velocidad
// icono_alerta
// icono_gps
// icono_gateway
// icono_wifi_ble
// icono_nfc
// icono_candado
// icono_configuracion
// icono_log
// icono_estado_emergencia
// icono_id_vehiculo

// Cada ícono debe seguir el patrón:
// const uint16_t icono_nombre[100] = { ... };

