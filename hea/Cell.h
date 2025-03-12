//
// Created by lucas on 29/01/2025.
//

#ifndef CELL_H
#define CELL_H

class AbstractCellule{
protected:
  int state;
public:
  AbstractCellule();
  AbstractCellule(int state);
  virtual int GetState()const = 0;
  virtual void ChangeState(int s) = 0;
};

class StandardCellule: public AbstractCellule{
public:
  StandardCellule();
  StandardCellule(int state);
  int GetState() const override;
  void ChangeState(int s) override;
};

class Obstacle:public AbstractCellule{
public:
  Obstacle();
  Obstacle(int state);
  int GetState()const override;
  void ChangeState(int s) override;
};

#endif //CELL_H
