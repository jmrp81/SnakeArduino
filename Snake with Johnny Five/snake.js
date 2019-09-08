const five = require("johnny-five");
var Raspi = require("raspi-io").RaspiIO;
const bodySnake = require("./models/bodySnake");
const characters = require("./scripts/characters");

// variables movimiento
// const buttonTopPin = "P1-12";
// const buttonButtonPin = "P1-11";
// const buttonLeftPin = "P1-15";
// const buttonRightPin = "P1-13";

const buttonTopPin = "GPIO18";
const buttonButtonPin = "GPIO17";
const buttonLeftPin = "GPIO22";
const buttonRightPin = "GPIO27";

let buttonTop = null;
let buttonButton = null;
let buttonLeft = null;
let buttonRight= null;

// variables juego
const cabezaSnake = 2; // 2
const cuerpoSnake = 1; // 1
const comidaSnake = 3; // 3
const huecoVacio = 0;

let firstTime = true;
let endGame = false;

// variables snake
const leftDirection = 0;
const topDirection = 1;
const downDirection = 2;
const rightDirection = 4;

let posXHeadSnake = -1;
let posYHeadSnake = -1;
let snakeDirection = leftDirection;
let oldSnakeDirection = 0;

let bodySnakeArray = [];
let snakeSize = 0;

// variables comida
let posXMeal = -1;
let posYMeal = -1;

// variables tablero
const rowsGameTable = 8;
const colsGameTable = 8;
let gameTable = [];

// variables matriz
const DATA_PIN = "P1-22"; 
const CS_PIN = "P1-24"; 
const CLOCK_PIN = "P1-26"; 
let matrix = null;

const board = new five.Board({
  io: new Raspi()
});

board.on("ready", function () {
  initializeGameTable();

  buttonTop = new five.Button(buttonTopPin);
  buttonButton = new five.Button(buttonButtonPin);
  buttonLeft = new five.Button(buttonLeftPin);
  buttonRight = new five.Button(buttonRightPin);

  buttonTop.on("press", function() {
    snakeDirection = topDirection;
  });

  buttonButton.on("press", function() {
    snakeDirection = downDirection;
  });

  buttonLeft.on("press", function() {
    snakeDirection = leftDirection;
  });

  buttonRight.on("press", function() {
    snakeDirection = rightDirection;
  });
  
  matrix = new five.Led.Matrix({
    pins: {
      data: DATA_PIN,
      clock: CLOCK_PIN,
      cs: CS_PIN
    }
  });

  matrix.on();

  setInterval(loop, 1000);
});

function initializeGameTable() {
  for (let i = 0; i < rowsGameTable; i++) {
    gameTable[i] = new Array(8);
    for (let j = 0; j < colsGameTable; j++) {
      gameTable[i][j] = huecoVacio;
    }
  }
}

function loop() {
    if (endGame) {
      firstTime = true;
      endGame = false;
      initializeGameTable();
    }

    if (firstTime) {
      initializeAppleAndSnakeHead();
      showWelcome();
      firstTime = false;
    } else if (endGame) {
      showFinish();
    } else {
      runGame();
    }
}


function initializeAppleAndSnakeHead() {
  posXHeadSnake = Math.floor((Math.random() * 7) + 1);
  posYHeadSnake = Math.floor((Math.random() * 7) + 1);

  gameTable[posYHeadSnake][posXHeadSnake] = cabezaSnake;
  snakeSize = 1;

  drawAppleInTable();
}

// Game functions
function runGame() {
  if (snakeDirection == leftDirection) {
    moveLeft();
  } else if (snakeDirection == topDirection) {
    moveUp();
  } else if (snakeDirection == downDirection) {
    moveDown();
  } else if (snakeDirection == rightDirection) {
    moveRight();
  }

  drawGameTable();
}


// Move functions
function moveLeft() {
  let oldposXHeadSnake = posXHeadSnake;
  let oldposYHeadSnake = posYHeadSnake;

  if (posXHeadSnake != 0) {
    posXHeadSnake -= 1;
  } else if (posXHeadSnake == 0) {
    posXHeadSnake = 7;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

function moveRight() {
  let oldposXHeadSnake = posXHeadSnake;
  let oldposYHeadSnake = posYHeadSnake;

  if (posXHeadSnake != 7) {
    posXHeadSnake += 1;
  } else if (posXHeadSnake == 7) {
    posXHeadSnake = 0;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

function moveUp() {
  let oldposXHeadSnake = posXHeadSnake;
  let oldposYHeadSnake = posYHeadSnake;

  if (posYHeadSnake != 7) {
    posYHeadSnake += 1;
  } else if (posYHeadSnake == 7) {
    posYHeadSnake = 0;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

function moveDown() {
  let oldposXHeadSnake = posXHeadSnake;
  let oldposYHeadSnake = posYHeadSnake;

  if (posYHeadSnake != 0) {
    posYHeadSnake -= 1;
  } else if (posYHeadSnake == 0) {
    posYHeadSnake = 7;
  }

  snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake);
}

function snakeActions(oldposXHeadSnake, oldposYHeadSnake, posXHeadSnake, posYHeadSnake) {
  switch (gameTable[posYHeadSnake][posXHeadSnake]) {
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

function eatSnake(oldposXHeadSnake, oldposYHeadSnake, newPosXhead, newPosYHead) {
  snakeSize = snakeSize + 1;

  let bodySnakeArrayCopy = new Array(snakeSize);

  bodySnakeArrayCopy[0] = new bodySnake(newPosXhead, newPosYHead);
  
  for (let i = 0; i < (snakeSize - 1); i++) {
    bodySnakeArrayCopy[i + 1] = new bodySnake(bodySnakeArray[i].GetPosX(), bodySnakeArray[i].GetPosY());
  }

  bodySnakeArray = new Array(snakeSize);
  bodySnakeArray = [...bodySnakeArrayCopy];

  moveSnake(oldposXHeadSnake, oldposYHeadSnake, newPosXhead, newPosYHead);
  drawAppleInTable();
}

function moveSnake(oldPosXhead, oldPosYhead, newPosXhead, newPosYHead) {
  gameTable[newPosYHead][newPosXhead] = cabezaSnake;

  if (snakeSize == 1) {
    gameTable[oldPosYhead][oldPosXhead] = huecoVacio;
  } else {
    gameTable[bodySnakeArray[snakeSize - 1].GetPosY()][bodySnakeArray[snakeSize - 1].GetPosX()] = huecoVacio; // si se comenta la serpiente crece continuamente no haria falta el metodo eat variacion II
  }

  for (let i = (snakeSize - 1); i >= 0; i--) {
    if (i == 0) {
      bodySnakeArray[i] = new bodySnake(newPosXhead, newPosYHead);
    } else {
      bodySnakeArray[i] = new bodySnake(bodySnakeArray[i - 1].GetPosX(), bodySnakeArray[i - 1].GetPosY());
    }
  }
}

function GameOver() {
  endGame = true;
  showFinish();
  initializeGameTable();
  initializeAppleAndSnakeHead();
}

function drawAppleInTable() {
  do {
    posXMeal = Math.floor((Math.random() * 7) + 1);
    posYMeal = Math.floor((Math.random() * 7) + 1);
  } while (gameTable[posYMeal][posXMeal] != huecoVacio);

  gameTable[posYMeal][posXMeal] = comidaSnake;
}

// matrix draw functions
function showWelcome() {
  for (let k = 0; k < 100; k++)  {
    matrix.draw(characters.getLetterS());
  }

  for (let k = 0; k < 100; k++)  {
    matrix.draw(characters.getLetterN());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterA());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterK());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterE());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterEmpty());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterN3());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterN2());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterN1());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterN0());
  }
}

function showFinish() {
  for (let k = 0; k < 100; k++)  {
    matrix.draw(characters.getLetterL());
  }

  for (let k = 0; k < 100; k++)  {
    matrix.draw(characters.getLetterO());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterS());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterT());
  }

  for (let k = 0; k < 100; k++) {
    matrix.draw(characters.getLetterEmpty());
  }
}

function drawGameTable() {
  gameTableDraw = [];
  let maxValueCol = (colsGameTable - 1);
  for (let col = maxValueCol; col >= 0; col--) {
    let actualRow = (((gameTable[0][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[1][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[2][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[3][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[4][(maxValueCol - col)]) > 0 ? 1 : 0) + ""  + ((gameTable[5][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[6][(maxValueCol - col)]) > 0 ? 1 : 0) + "" + ((gameTable[7][(maxValueCol - col)]) > 0 ? 1 : 0));
    gameTableDraw.push((""+actualRow));
  }

  matrix.draw(gameTableDraw);
}