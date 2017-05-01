#pragma once
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream> 

template <class T>
class Tuile
{
public:
  const T& North() const;
  const T& South() const;
  const T& East() const;
  const T& West() const;
  void set(T val, int pos);
private:
  T North_;
  T South_;
  T East_;
  T West_;
  
};
// FIXME type definition, replace int by what you think is best
// Threshold 0
template <class T>
using Tile = class Tuile;

template <class T>
class Tetravex
{
public:
  // FIXME Functions
  // Threshold 0
  Tetravex<T>(uint8_t size)
  {size_ = size;}
  void add_tile(const Tile<T>& tile);
  // Threshold 1
  int write(const std::string& output) const ;
  int read(const std::string& input);
  const Tile<T>& index_board(int i, int j);
  // Threshold > 2
  bool resolvave(std::vector<Tile<T>>& put, Tile<T>& add);
  
  void solve2(std::vector<Tetravex<T>>& soluces,
             std::vector<Tile<T>>& put,
             std::vector<Tile<T>>& copy);
  
  int solve(const std::string& output);  
private:
  std::vector<Tile<T>> tiles_;
  uint8_t size_;
};

#include "tuile.hxx"
#include "tetravex.hxx"
