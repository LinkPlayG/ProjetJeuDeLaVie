//
// Created by lucas on 03/12/2024.
//

#ifndef ABSTRACTCELLULE_H
#define ABSTRACTCELLULE_H


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
    virtual int GetState();
};

#endif //ABSTRACTCELLULE_H
