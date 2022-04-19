#include "bombs.h"
#include "coordinate.h"
#include <memory>

Bombs::Bombs() {
  _coordinates =
      std::unique_ptr<std::vector<Coordinate>>(new std::vector<Coordinate>);
}

void Bombs::addCoordinate(const Coordinate &&coordinate) {
  _coordinates->emplace_back(coordinate);
}

bool Bombs::BombCell(const Coordinate &&coordinate) {
  for (const Coordinate &_coordinate : *_coordinates) {
    if (_coordinate == coordinate) {
      return true;
    }
  }
  return false;
}

int Bombs::count() const { return _coordinates->size(); }

const std::vector<Coordinate> &Bombs::getCoordinates() const {
  return *_coordinates;
}