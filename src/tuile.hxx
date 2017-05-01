#include "tetravex.hh"

template <typename T>
inline const T& Tuile<T>::North() const
{
  return North_;
}

template <typename T>
inline const T& Tuile<T>::South() const
{
  return South_;
}

template <typename T>
inline const T& Tuile<T>::East() const
{
  return East_;
}

template <typename T>
inline const T& Tuile<T>::West() const
{
  return West_;
}

template <typename T>
inline void Tuile<T>::set(T val, int pos)
{
  if (pos == 0)
    South_= val;
  if (pos == 1)
      East_= val;
  if (pos == 2)
    North_= val;
  if (pos == 3)
    West_= val;
}
