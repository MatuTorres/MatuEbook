#include <SD.h>

#define uSD 10 // pin del lector de micro SD
#define right 4 // pin para el botón de la derecha
#define left 5 // pin para el botón de la izquierda

File testFile;
File root;
int bookCount = 0;
File books[10];

void setup()
{
  Serial.begin(9600);

  if (!SD.begin(uSD)) {
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
  
  root = SD.open("/");

  printDirectory(root, 0);
}

void loop() 
{
  bookSelection(root, 0);
}