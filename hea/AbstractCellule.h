//
// Created by lucas on 03/12/2024.
//

#ifndef CELLULE_H
#define CELLULE_H


class AbstractCellule{
protected:
    int x;
    int y;
    int state;
public:
    AbstractCellule();
    AbstractCellule(int x, int y, int state);
    virtual int getX() const;
    virtual int getY() const;
    virtual int GetState()const;
};

class StandardCellule: public AbstractCellule{
public:
    StandardCellule();
    StandardCellule(int x, int y, int state);
    int getX() const override;
    int getY() const override;
    int GetState() const override;
    void ChangeState(int s);
};

class Obstacle:public AbstractCellule{
public:
    Obstacle();
    Obstacle(int x,int y, int state);
    int getX()const override;
    int getY()const override;
    int GetState()const override;
};

#endif //CELLULE_H
