#include <Adafruit_NeoPixel.h>

#define PIN 6   // Define el pin al que está conectada la tira de LEDs
#define NUM_LEDS 24  // Número de LEDs en tu tira

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int brightness = 255; // Brillo predeterminado al máximo (0 a 255)


uint32_t rainbowColors[] = {
  strip.Color(255, 0, 0),   // Rojo
  strip.Color(255, 127, 0), // Naranja
  strip.Color(255, 255, 0), // Amarillo
  strip.Color(0, 255, 0),   // Verde
  strip.Color(0, 0, 255),   // Azul
  strip.Color(75, 0, 130),  // Índigo
  strip.Color(148, 0, 211)  // Violeta
};

void setup() {
  strip.begin();
  strip.show(); // Inicializa todos los LEDs con los valores actuales
  
  Serial.begin(9600); // Inicializa la comunicación serial a 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
     String data = Serial.readStringUntil('\n');
    if (data.startsWith("Color")) {
      // Comando para establecer un color y brillo: "Color R,G,B,Brillo"
      int startIndex = data.indexOf(" ");
      String colorData = data.substring(startIndex + 1);
      int separator1 = colorData.indexOf(",");
      int separator2 = colorData.lastIndexOf(",");
      
      int r = colorData.substring(0, separator1).toInt();
      int g = colorData.substring(separator1 + 1, separator2).toInt();
      int b = colorData.substring(separator2 + 1, colorData.length() - 1).toInt();
      int brillo = brightness;
      
      setColor(r, g, b, brillo);
    }
    else if (data == "FadeColor") {
       while (true) {  // Bucle infinito para la animación MixColor
        fadeColorAnimation();
       }
    }
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

// Función para la animación Mix Color
void fadeColorAnimation() {
  int brillo = 100; // Brillo al máximo
  uint32_t targetColor = rainbowColors[0];
  uint32_t currentColor = strip.Color(0, 0, 0);

  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 0; j < 256; j++) {
      int r = ((currentColor >> 16) & 0xFF) + (int)(((targetColor >> 16) & 0xFF - ((currentColor >> 16) & 0xFF)) * (j / 256.0));
      int g = ((currentColor >> 8) & 0xFF) + (int)(((targetColor >> 8) & 0xFF - ((currentColor >> 8) & 0xFF)) * (j / 256.0));
      int b = (currentColor & 0xFF) + (int)((targetColor & 0xFF - (currentColor & 0xFF)) * (j / 256.0));
      
      setColor(r, g, b, brillo);
      delay(100);
    }
    currentColor = targetColor;
    targetColor = rainbowColors[(i + 1) % (sizeof(rainbowColors) / sizeof(rainbowColors[0]))];
  }
}


