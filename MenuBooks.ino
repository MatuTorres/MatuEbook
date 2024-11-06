#include <SD.h>

int mark = 0;

void printDirectory(File dir, int numTabs)
{

  Serial.println("LIBROS");

  while (true)
  {
    File files =  dir.openNextFile();
    if (! files)
    {
      break;
    }

    bookCount++;

    for (uint8_t i = 0; i < numTabs; i++)
    {
      Serial.print('\t');
    }
    Serial.print(files.name());
    
    Serial.print("\n");

    books[bookCount] = files;

    files.close();
  }
}

void bookSelection(File dir, int numTabs)
{
  static int markAnt = -1;

  bool rightPressed = (digitalRead(right) == LOW);
  bool leftPressed = (digitalRead(left) == LOW);

  if (rightPressed)
  {
    mark = (mark < bookCount) ? mark + 1 : bookCount; // Evita que mark sobrepase bookCount
  } else if (leftPressed) {
    mark = (mark > 1) ? mark - 1 : 1; // Evita que mark baje de 1
  }

  if (mark != markAnt)
  {
    bookCount = 0;
    Serial.println("︵‿︵‿୨♡୧‿︵‿︵LIBROS︵‿︵‿୨♡୧‿︵‿︵");

    dir.rewindDirectory(); // Asegura que el directorio se lea desde el principio.

    while (true)
    {
      File files = dir.openNextFile();
      if (!files)
      {
        break; // No hay más archivos
      }

      bookCount++;

      for (uint8_t i = 0; i < numTabs; i++)
      {
        Serial.print('\t');
      }

      if (bookCount == mark)
      {
        Serial.print(files.name());
        Serial.print(" ←");
      } else {
        Serial.print(files.name());
      }

      Serial.print("\n");
      files.close();
    }
    markAnt = mark;
  }
}