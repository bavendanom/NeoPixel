#include <Adafruit_NeoPixel.h>

#define PIN 6   // Define el pin al que está conectada la tira de LEDs
#define NUM_LEDS 24  // Número de LEDs en tu tira

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int brightness = 255; // Brillo predeterminado al máximo (0 a 255)

void setup() {
  strip.begin();
  strip.show(); // Inicializa todos los LEDs con los valores actuales
  
  Serial.begin(9600); // Inicializa la comunicación serial a 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    // Si hay datos disponibles en la comunicación serial
    String data = Serial.readStringUntil('\n'); // Lee la cadena de datos hasta encontrar un salto de línea
    
    // Divide la cadena en valores RGB y brillo utilizando comas como separadores
    int r = data.substring(0, data.indexOf(',')).toInt();
    data = data.substring(data.indexOf(',') + 1);
    int g = data.substring(0, data.indexOf(',')).toInt();
    data = data.substring(data.indexOf(',') + 1);
    int b = data.substring(0, data.indexOf(',')).toInt();
    int brillo = data.substring(data.indexOf(',') + 1).toInt();
    
    // Llama a la función para configurar el color y brillo
    setColor(r, g, b, brillo);
  }
}

void setColor(int r, int g, int b, int brillo) {
  // Ajusta el brillo entre 0 (apagado) y 255 (máxima intensidad)
  brillo = map(brillo, 0, 100, 0, 255);
  
  for(int i = 0; i < NUM_LEDS; i++) {
    // Aplica el brillo al color antes de establecerlo en el LED
    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.setBrightness(brillo);
  }
  strip.show(); // Actualiza la tira con el nuevo color y brillo
}
