/*******************************************************************************
 * Proyecto: Nodo LoRaWAN OTAA - Heltec Wireless Stick Lite V3
 * Autor: I.S.C. Erick Renato Vega Ceron
 * Dispositivo: nodo01stick
 * Gateway: pachuca-norponiente-iot-01
 * App TTS: pruebas_1_iot
 * Banda: US915 (México)
 * Protocolo: OTAA - Clase A
 *******************************************************************************/

#include "LoRaWan_APP.h"
#include "Arduino.h"


// ===============================
// 🔐 Credenciales OTAA desde TTS
// ===============================
uint8_t devEui[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x06, 0xF5, 0x2C };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0x8B, 0xD6, 0x8E, 0xF9, 0x38, 0xEC, 0x45, 0xDA, 0xA2, 0x9B, 0x1A, 0x5F, 0x57, 0x7A, 0x5C, 0x14 };

// Dummy variables requeridas aunque no se use ABP
uint8_t nwkSKey[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
uint8_t appSKey[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
uint32_t devAddr = 0x00000000;


// ===============================
// ⚙️ Configuración LoRaWAN
// ===============================
bool overTheAirActivation = true;
uint8_t confirmedNbTrials = 4;
bool isTxConfirmed = true;
bool loraWanAdr = true;

DeviceClass_t  loraWanClass = CLASS_A;
LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_US915;

uint32_t appTxDutyCycle = 60000;  // 60 segundos entre envíos
uint8_t appPort = 2;

uint16_t userChannelsMask[6] = { 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

// ===============================
// 💡 LED de estado
// ===============================
#define LED_PIN 35
void parpadeo(uint8_t veces, uint16_t tiempo = 100, uint16_t pausa = 200) {
  for (uint8_t i = 0; i < veces; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(tiempo);
    digitalWrite(LED_PIN, LOW);
    delay(pausa);
  }
}

// ===============================
// 📤 Cargar datos a enviar
// ===============================
static void prepareTxFrame(uint8_t port) {
  appDataSize = 4;
  appData[0] = 'N';
  appData[1] = 'O';
  appData[2] = 'D';
  appData[3] = 'E';
}

// ===============================
// 🔁 Loop principal de estados
// ===============================
void loop() {
  switch (deviceState) {
    case DEVICE_STATE_INIT: {
#if (LORAWAN_DEVEUI_AUTO)
      LoRaWAN.generateDeveuiByChipID();
#endif
      LoRaWAN.init(loraWanClass, loraWanRegion);
      LoRaWAN.setDefaultDR(3);  // Spreading Factor
      Serial.println("✅ Nodo inicializado");
      pinMode(LED_PIN, OUTPUT);
      parpadeo(1, 100, 1000);  // Encendido
      break;
    }

    case DEVICE_STATE_JOIN: {
      Serial.println("🔗 Intentando OTAA Join...");
      parpadeo(2, 100, 150);
      LoRaWAN.join();
      break;
    }

    case DEVICE_STATE_SEND: {
      Serial.println("📤 Enviando datos...");
      prepareTxFrame(appPort);
      LoRaWAN.send();
      deviceState = DEVICE_STATE_CYCLE;
      parpadeo(1, 150);  // Envío exitoso
      break;
    }

    case DEVICE_STATE_CYCLE: {
      txDutyCycleTime = appTxDutyCycle + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      break;
    }

    case DEVICE_STATE_SLEEP: {
      LoRaWAN.sleep(loraWanClass);
      break;
    }

    default: {
      deviceState = DEVICE_STATE_INIT;
      break;
    }
  }
}

// ===============================
// 🔧 Setup inicial del microcontrolador
// ===============================
void setup() {
  Serial.begin(115200);
  delay(100);
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);  // Inicializa la placa Heltec
}
