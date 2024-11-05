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
  int markAnt = 0;

  if(digitalRead(right) == LOW) // Si se apretó el botón de la derecha
  {
    if(mark == bookCount)
    {
      mark = bookCount;
    }
    else
    {
      mark++;
    }
  }
  else if(digitalRead(left) == LOW) // Si se apretó el botón de la izquierda
  {
    if(mark == 1)
    {
      mark = 1;
    }
    else
    {
      mark--;
    }
  }

  if(mark == markAnt){}
  else
  {

    bookCount = 0;

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
      if(bookCount == mark)
      {
        Serial.print(files.name());
        Serial.print(" ←");
      }
      else
      {
        Serial.print(files.name());
      }

      Serial.print("\n");

      files.close();
    }
  }
  markAnt = mark;
}