/* Snake Class */
#ifndef BodySnake_h
#define BodySnake_h

class BodySnake
{
  public:
    BodySnake();
    BodySnake(int posX, int posY);
	  ~BodySnake(); // destructor
    int GetPosX();
    int GetPosY();
    void SetPosX(int posX);
    void SetPosY(int posY);
    
  private:
    int _posX;
    int _posY;
};

#endif
