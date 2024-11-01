#include <SD.h>

const int pin = 10;
File testFile;

void setup()
{
  Serial.begin(9600);

  if (!SD.begin(pin)) {
    Serial.println("SD no conectada.");
    while (1);
  }

  if (SD.exists("testFile.pdf")) {
  } else {
    Serial.println("No se encuentra el archivo.");
  }

  Serial.println("Creando testFile.pdf...");
  testFile = SD.open("testFile.pdf", FILE_WRITE);
  testFile.close();
}

void loop() {
  // aca no va nada por ahora
}