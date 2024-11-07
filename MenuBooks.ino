int mark = 0;
int rightPrevState = HIGH;
int leftPrevState = HIGH;

void printDirectory(File dir, int numTabs)
{
  Serial.println("LIBROS");

  while (true)
  {
    File files = dir.openNextFile();
    if (!files)
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

    files.close();
  }
}

void bookSelection(File dir, int numTabs)
{
  static int markAnt = -1;

  int rightState = digitalRead(right);
  int leftState = digitalRead(left);

  bool rightReleased = (rightState == LOW && rightPrevState == HIGH);
  bool rightPressed = (rightState == HIGH && rightPrevState == LOW);
  bool leftReleased = (leftState == LOW && leftPrevState == HIGH);
  bool leftPressed = (leftState == HIGH && leftPrevState == LOW);

  if (rightPressed)
  {
    mark = (mark < bookCount) ? mark + 1 : bookCount;
  }
  else if (leftPressed)
  {
    mark = (mark > 1) ? mark - 1 : 1;
  }

  if ((rightReleased || leftReleased) && mark != markAnt)
  {
    bookCount = 0;
    Serial.println("︵‿︵‿୨♡୧‿︵‿︵LIBROS︵‿︵‿୨♡୧‿︵‿︵");
    dir.rewindDirectory(); // Asegura que el directorio se lea desde el principio.
    while (true)
    {
      File files = dir.openNextFile();
      if (!files)
      {
        break;
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
      }
      else
      {
        Serial.print(files.name());
      }
      Serial.print("\n");
      files.close();
    }
    markAnt = mark;
  }

  // Actualiza el estado previo de los botones
  rightPrevState = rightState;
  leftPrevState = leftState;
}
