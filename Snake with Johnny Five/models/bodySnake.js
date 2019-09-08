class BodySnake {
    constructor(posX, posY) {
        this._posX = posX;
        this._posY = posY;
    }

    GetPosX() {
        return this._posX;
    }

    GetPosY() {
        return this._posY;
    }

    SetPosX(posX) {
        this._posX = posX;
    }

    SetPosY(posY) {
        this._posY = posY;
    }
}

module.exports = BodySnake;