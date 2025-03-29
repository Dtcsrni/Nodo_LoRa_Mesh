#ifndef VARIABLES_GLOBALES_H
#define VARIABLES_GLOBALES_H

#include <Arduino.h>

// Variables de estado compartidas
extern int velocidad;
extern int velocidadAnterior;

extern int nivelBateria;
extern int bateriaAnterior;

extern bool estadoConexionLoRa;
extern bool conexionAnterior;

extern char direccionCardinal[4];
extern String alertaActual;

extern String nombreUsuario;
extern String idVehiculo;

// Constantes
#define VEL_MAXIMA_URBANA 60

// Colores personalizados
#define ST7735_DARKGREY 0x7BEF

#endif
