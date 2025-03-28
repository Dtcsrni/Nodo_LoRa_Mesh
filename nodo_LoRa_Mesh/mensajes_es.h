// Archivo de mensajes en español y símbolos visuales compatibles con pantallas TFT ST7735
// Versión optimizada con íconos gráficos embebidos para mayor detalle visual y escala compacta a color

#ifndef MENSAJES_ES_H
#define MENSAJES_ES_H

// Mensajes estáticos para pantalla de bienvenida y sistema
#define MENSAJE_CYBERSYS            "Cybersys"
#define MENSAJE_INICIAL_SENSORES   "Iniciando sensores..."
#define MENSAJE_CONFIGURANDO_LORA  "Configurando LoRa..."
#define MENSAJE_INICIALIZANDO_GPS  "Inicializando GPS..."
#define MENSAJE_CARGANDO_CONFIG    "Cargando config..."
#define MENSAJE_SISTEMA_LISTO      "Sistema listo"
#define MENSAJE_ID                 "ID Vehiculo: "

// Mensajes para indicadores del dashboard
#define MENSAJE_VELOCIDAD          "Velocidad: %dkm/h"
#define MENSAJE_BATERIA            "Bateria: %d%%"
#define MENSAJE_LORA_CONECTADO    "LoRa conectado"
#define MENSAJE_LORA_DESCONECTADO "LoRa desconectado"
#define MENSAJE_AUTENTICANDO      "Autenticando..."
#define MENSAJE_NFC_REQUERIDA     "Coloque tarjeta NFC"
#define MENSAJE_BATERIA_CRITICA   "Bateria baja"

// Definiciones de íconos gráficos embebidos (referencias a arrays definidos en archivos .c)
#define ICONO_USUARIO_ID     1  // Icono de persona (estilo perfil)
#define ICONO_LORA_ID        2  // Icono de antena con ondas
#define ICONO_BRUJULA_ID     3  // Flecha orientada con borde circular
#define ICONO_BATERIA_ID     4  // Batería con relleno proporcional
#define ICONO_VELOCIDAD_ID   5  // Velocímetro con aguja y fondo
#define ICONO_ALERTA_ID      6  // Triángulo con signo de exclamación
#define ICONO_CONFIG_ID      7  // Engrane con detalles
#define ICONO_GPS_ID         8  // Marcador de ubicación estilizado
#define ICONO_TOUCH_ID       9  // Dedo tocando pantalla (vista lateral)

#endif
