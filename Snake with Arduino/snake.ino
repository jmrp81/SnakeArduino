#include "characters.h"
#include "BodySnake.h"

/* Variables joystick */
/* Pines Joystick */
int joystickPinEjeX = A1; // entrada analogica
int joystickPinEjeY = A0; // entrada analogica
int joystickPinPulsador = 13;

/* Valores a usar Joystick */
int joystickValorX = 0;
int joystickValorY = 0;
int joystickValorPulsador = 0;
int maxValueXLeft = 1023;
int maxValueXRight = 0;
int maxValueYUp = 1023;
int maxValueYDown = 0;

/* Variables del juego */
const int cabezaSnake = 2; // 2
const int cuerpoSnake = 1; // 1
const int comidaSnake = 3; // 3
const int huecoVacio = 0;
int delayValueToMov = 750;
int timer = 0; // timer retraso joystick
bool firstTime = true;
bool endGame = false;

/* snake */
BodySnake _Snake[1];
int snakeSize = 0;

/* Posicion de snake */
const int leftDirection = 0;
const int topDirection = 1;
const int downDirection = 2;
const int rightDirection = 4;
int posXHeadSnake = -1;
int posYHeadSnake = -1;
int snakeDirection = 0;
int oldSnakeDirection = 0;

/* Posicion de la comida */
int posXMeal = -1;
int posYMeal = -1;

/* Crear matrices para el juego y la matriz 8x8 */
const int rowsGameTable = 8; // se definen como constantes para poder usarlar al crear la matriz
const int colsGameTable = 8;
int gameTable[rowsGameTable][colsGameTable];

/* Variables matriz led 8x8 y 74HC595 */
/* 74HC595 */
#define DS_PIN 10    // data pin
#define SH_CP_PIN 11 // clock pin
#define ST_CP_PIN 12 // latch pin

/* matriz 8x8 pins de las columnas en arduino led */
uint8_t colPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

/* Principal functions */
void setup()
{
  /* Inicializacion de los pines de entrada */
  pinMode(joystickPinEjeX, INPUT);
  pinMode(joystickPinEjeY, INPUT);
  pinMode(joystickPinPulsador, INPUT_PULLUP); // indicamos es entrada pull up

  /* inicializamos la matriz vacia */
  initializeGameTable();

  /* inicializamos valores  matriz led 8x8 y 74HC595 */
  for (int i = 0; i < 8; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  pinMode(DS_PIN, OUTPUT);
  pinMode(SH_CP_PIN, OUTPUT);
  pinMode(ST_CP_PIN, OUTPUT);

  Serial.begin(9600); // Establecemos las comunicarciones en serie en 9600 bps (bytes por seg.)

  timer = millis() + delayValueToMov;
}

void loop()
{
  joystickValorPulsador = digitalRead(joystickPinPulsador);

  if (joystickValorPulsador == 0 && endGame)
  {
    firstTime = true;
    endGame = false;
  }

  if (firstTime)
  {
    initializeAppleAndSnakeHead();
    showWelcome();
    firstTime = false;
  }
  else if (endGame)
  {
    showFinish();
  }
  else
  {
    runGame();
  }
}

// Initialize functions
void initializeGameTable()
{
  for (int i = 0; i < rowsGameTable; i++)
  {
    for (int j = 0; j < colsGameTable; j++)
    {
      gameTable[i][j] = huecoVacio;
    }
  }
}

void initializeAppleAndSnakeHead()
{
  posXHeadSnake = random(0, 7);
  posYHeadSnake = random(0, 7);

  gameTable[posYHeadSnake][posXHeadSnake] = cabezaSnake;
  snakeSize = 1;

  drawAppleInTable();
}

// Game functions
void runGame()
{
  int now = millis();
  // añadir un poco de retraso entre lecturas
  if (now > timer)
  {
    timer = (now + delayValueToMov);
    readDataMoveJoystick();
  }

  drawGameTable();
}

void controlSpeed()
{
  if (joystickValorPulsador != 0)
  {
    delayValueToMov -= 500;

    if (delayValueToMov < 0)
    {
      delayValueToMov = 0;
    }
  }
  else
  {
    delayValueToMov = 5000; //5000
  }
}

void readDataMoveJoystick()
{
  joystickValorX = analogRead(joystickPinEjeX);
  joystickValorY = analogRead(joystickPinEjeY);

  if (maxValueXLeft >= joystickValorX && joystickValorX > 800)
  {
    snakeDirection = leftDirection;
  }
  else if (maxValueXRight <= joystickValorX && joystickValorX < 250)
  {
    snakeDirection = rightDirection;
  }
  else if (maxValueYUp >= joystickValorY && joystickValorY > 800)
  {
    snakeDirection = topDirection;
  }
  else if (maxValueYDown <= joystickValorY && joystickValorY < 250)
  {
    snakeDirection = downDirection;
  }

  if (snakeDirection == leftDirection)
  {
    moveLeft();
  }
  else if (snakeDirection == topDirection)
  {
    moveUp();
  }
  else if (snakeDirection == downDirection)
  {
    moveDown();
  }
  else if (snakeDirection == rightDirection)
  {
    moveRight();
  }
}

// Move functions
void moveLeft()
{
  int oldposXHeadSnake = posXHeadSnake;
  int oldposYHeadSnake = posYHeadSnake;

  if (posXHeadSnake != 0)
  {
    posXHeadSnake -= 1;
  }
  else if (posXHeadSnake == 0)
  {
    posXHeadSnake = 7;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

void moveRight()
{
  int oldposXHeadSnake = posXHeadSnake;
  int oldposYHeadSnake = posYHeadSnake;

  if (posXHeadSnake != 7)
  {
    posXHeadSnake += 1;
  }
  else if (posXHeadSnake == 7)
  {
    posXHeadSnake = 0;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

void moveUp()
{
  int oldposXHeadSnake = posXHeadSnake;
  int oldposYHeadSnake = posYHeadSnake;

  if (posYHeadSnake != 0)
  {
    posYHeadSnake -= 1;
  }
  else if (posYHeadSnake == 0)
  {
    posYHeadSnake = 7;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

void moveDown()
{
  int oldposXHeadSnake = posXHeadSnake;
  int oldposYHeadSnake = posYHeadSnake;

  if (posYHeadSnake != 7)
  {
    posYHeadSnake += 1;
  }
  else if (posYHeadSnake == 7)
  {
    posYHeadSnake = 0;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

void snakeActions(int oldposXHeadSnake, int oldposYHeadSnake, int posXHeadSnake, int posYHeadSnake)
{
  switch (gameTable[posYHeadSnake][posXHeadSnake])
  {
  case comidaSnake: // manzana: crece
    eatSnake(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
    break;
  case huecoVacio: // hueco vacio se mueve
    moveSnake(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
    break;
  case cabezaSnake: // Serpiente muere
  case cuerpoSnake:
    GameOver();
    break;
  }
}

void eatSnake(int oldposXHeadSnake, int oldposYHeadSnake, int newPosXhead, int newPosYHead)
{
  snakeSize = snakeSize + 1;

  BodySnake _SnakeCopy[snakeSize];

  _SnakeCopy[0].SetPosX(newPosXhead);
  _SnakeCopy[0].SetPosY(newPosYHead);

  for (int i = 0; i < (snakeSize - 1); i++)
  {
    _SnakeCopy[i + 1].SetPosX(_Snake[i].GetPosX());
    _SnakeCopy[i + 1].SetPosY(_Snake[i].GetPosY());
  }

  BodySnake _Snake[snakeSize];

  memcpy(_Snake, _SnakeCopy, snakeSize);
  
  moveSnake(oldposXHeadSnake, oldposYHeadSnake, newPosXhead, newPosYHead);
  drawAppleInTable();
}

void moveSnake(int oldPosXhead, int oldPosYhead, int newPosXhead, int newPosYHead)
{
  gameTable[newPosYHead][newPosXhead] = cabezaSnake;

  if (snakeSize == 1)
  {
    gameTable[oldPosYhead][oldPosXhead] = huecoVacio;
  }
  else
  {
    gameTable[_Snake[snakeSize - 1].GetPosY()][_Snake[snakeSize - 1].GetPosX()] = huecoVacio; // si se comenta la serpiente crece continuamente no haria falta el metodo eat variacion II
  }

  for (int i = (snakeSize - 1); i >= 0; i--)
  {
    if (i == 0)
    {
      _Snake[i].SetPosX(newPosXhead);
      _Snake[i].SetPosY(newPosYHead);
    }
    else
    {
      _Snake[i].SetPosX(_Snake[i - 1].GetPosX());
      _Snake[i].SetPosY(_Snake[i - 1].GetPosY());
    }
  }
}

// draw functions
void showWelcome()
{
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(S);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(N);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(A);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(K);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(E);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(Empty);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(N3);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(N2);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(N1);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(N0);
  }
}

void GameOver()
{
  endGame = true;
  showFinish();
  initializeGameTable();
  initializeAppleAndSnakeHead();
}

void showFinish()
{
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(L);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(O);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(S);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(T);
  }
  for (int k = 0; k < 1000; k++)
  {
    displayCharacter(Empty);
  }
}

void displayCharacter(byte character[8])
{
  for (int j = 0; j < 8; j++)
  {
    digitalWrite(ST_CP_PIN, LOW); // latch pin
    digitalWrite(colPins[j], LOW);

    shiftOut(DS_PIN, SH_CP_PIN, MSBFIRST, character[j]);

    digitalWrite(ST_CP_PIN, HIGH);
    delay(0);
    digitalWrite(ST_CP_PIN, LOW);

    shiftOut(DS_PIN, SH_CP_PIN, MSBFIRST, B00000000);
    digitalWrite(ST_CP_PIN, HIGH);
    digitalWrite(colPins[j], HIGH);
  }
}

void drawAppleInTable()
{
  do
  {
    posXMeal = random(0, 7);
    posYMeal = random(0, 7);
  } while (gameTable[posYMeal][posXMeal] != huecoVacio);

  gameTable[posYMeal][posXMeal] = comidaSnake;
}

void drawGameTable()
{
  int maxValueCol = (colsGameTable - 1);
  for (int col = maxValueCol; col >= 0; col--)
  {
    digitalWrite(ST_CP_PIN, LOW); // latch pin
    digitalWrite(colPins[col], LOW);

    byte actualRow = (int)(((gameTable[0][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 7) + ((gameTable[1][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 6) + ((gameTable[2][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 5) + ((gameTable[3][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 4) + ((gameTable[4][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 3) + ((gameTable[5][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 2) + ((gameTable[6][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 1) + ((gameTable[7][(maxValueCol - col)]) > 0 ? 1 : 0) * pow(2, 0));

    shiftOut(DS_PIN, SH_CP_PIN, MSBFIRST, actualRow);

    digitalWrite(ST_CP_PIN, HIGH);
    delay(0);
    digitalWrite(ST_CP_PIN, LOW);

    shiftOut(DS_PIN, SH_CP_PIN, MSBFIRST, B00000000);
    digitalWrite(ST_CP_PIN, HIGH);
    digitalWrite(colPins[col], HIGH);
  }
}
