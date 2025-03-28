# 🚍 Nodo IoT con LoRa Mesh para Monitoreo de Flotas Móviles

**Repositorio oficial del proyecto de tesis de maestría en Internet de las Cosas.**

Este sistema permite monitorear en tiempo real vehículos en entornos urbanos mediante un nodo IoT embebido que utiliza comunicación **LoRa Mesh híbrida**, sensores inteligentes y visualización en dashboards remotos.

---

## 🧠 Descripción del proyecto

Este repositorio contiene el firmware, scripts, configuraciones y documentación del prototipo funcional desarrollado como parte de la tesis:

**"Implementación de un Nodo IoT con LoRa Mesh para el Monitoreo de Flotas Móviles en Entornos Controlados"**  
Maestría en Internet de las Cosas, UAEH  
Autor: **I.S.C. Erick Renato Vega Cerón**  
Universidad Autónoma del Estado de Hidalgo  
Año: 2025

---

## ⚙️ Características principales

- Microcontrolador **Heltec Wireless Stick Lite V3**
- Comunicación LoRa Mesh (basada en SX1262) con optimización energética
- Sensores integrados:
  - **GPS** (NEO-6M)
  - **Acelerómetro y giroscopio** (MPU6050)
  - **Autenticación NFC** (PN532)
- Dashboard visual embebido en pantalla TFT SPI 1.8" (ST7735)
- Transmisión de datos en tiempo real mediante **MQTT + InfluxDB + Grafana**
- Backend en **Orange Pi 5 Plus** usando **Docker + Node-RED**
- Sistema de bajo consumo energético con modos sleep y deep sleep
- Logs locales, configuración remota vía LoRa y almacenamiento persistente

---

## 🔐 Licencia

Este proyecto está distribuido bajo **licenciamiento dual**:

### 🧠 Código fuente y firmware:
- Licencia: [GNU AGPL v3.0](https://www.gnu.org/licenses/agpl-3.0.html)  
- Está **prohibido el uso comercial, modificación o redistribución sin publicar el código fuente** derivado bajo la misma licencia.
- Cubre tanto el uso embebido como en plataformas web (backend, API, dashboards).

### 📄 Documentación, tesis, planos y gráficos:
- Licencia: [Creative Commons BY-NC-ND 4.0](https://creativecommons.org/licenses/by-nc-nd/4.0/)
- No se permite el uso comercial ni la creación de obras derivadas.
- Se requiere siempre atribuir al autor original.

---

- ✅ Sí puedes estudiarlo, revisarlo, y mencionarlo como inspiración citando correctamente.

---

## 📬 Contacto

Para colaboración científica, permisos de uso académico, licencias comerciales o contribuciones:

**I.S.C. Erick Renato Vega Ceron**  
📧 armsystechno@gmail.com
🏫 Maestría en Internet de las Cosas  
Universidad Autónoma del Estado de Hidalgo – UAEH


---
