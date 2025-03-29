#include "variables_globales.h"

int velocidad = 0;
int velocidadAnterior = -1;

int nivelBateria = 100;
int bateriaAnterior = -1;

bool estadoConexionLoRa = true;
bool conexionAnterior = false;

char direccionCardinal[4] = "N";
String alertaActual = "";

// Datos del nodo
String nombreUsuario = "ErickRVC";
String idVehiculo = "CYB-001";
