#ifndef BOMBS_H
#define BOMBS_H

#include <memory>
#include <vector>
#include "coordinate.h"

class Bombs
{
    public:
    Bombs();

    void addCoordinate(const Coordinate &&coordinate);
    bool BombCell(const Coordinate &&coordinate);
    int count() const;

    const std::vector<Coordinate> &getCoordinates() const;

    private:
    std::unique_ptr<std::vector<Coordinate>> _coordinates;
};

#endif