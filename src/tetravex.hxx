#include "tetravex.hh"


template <class T>
void Tetravex<T>::add_tile(const Tile<T>& tile) {
    /* FIXME */
    tiles_.push_back(tile);
  }

// Threshold 1
template <class T>
int Tetravex<T>::write(const std::string& output) const
  {
    /* FIXME */
    std::ofstream fs;
    fs.open(output, std::ios::out);
    int size = size_;
    fs << size << std::endl;
    for (size_t i = 0; i < tiles_.size(); ++i)
      {
        fs << tiles_[i].South() << " "
           << tiles_[i].East()  << " "
           << tiles_[i].North() << " "
           << tiles_[i].West();
        fs << std::endl;
      }
    fs.close();
    return 0;
  }

template <class T>
int Tetravex<T>::read(const std::string& input)
{
    std::ifstream fs;
    fs.open(input);
    if (!fs.is_open())
      return 3;
    std::string line;
    fs >> size_;
    T val;
    std::getline(fs, line);
    for (;std::getline(fs, line);)
      {
        std::stringstream lines(line);
        Tile<T> tuiles;
        lines >> val;
        tuiles.set(val, 0);
        
        lines >> val;
        tuiles.set(val, 1);
        
        lines >> val;
        tuiles.set(val, 2);
        
        lines >> val;
        tuiles.set(val, 3);
        
        add_tile(tuiles);                         
      }
    fs.close();
    return 0;
}

template <class T>
const Tile<T>&  Tetravex<T>::index_board(int i, int j)
{
  return  tiles_[(i * size_ +j)];
}

template <class T>
 bool Tetravex<T>::resolvave(std::vector<Tile<T>>& put, Tile<T>& add)  //verif
{
  if (put.empty())
    return true;
  else
    {
      int i = (put.size())/(size_-48); //ligne 
      int j = (put.size())%(size_-48); //colone
      if (i == 0 && j != 0)
        {
          if (put.back().East() == add.West())
            return true;
        }
      else if (i !=0 && j == 0)
        {
          if (put[(put.size() - (size_-48))].South() == add.North())
            return true;
        }
      else if (i !=0 && j !=0)
        {
          if ((put[(put.size() - (size_-48))].South() == add.North())
              && (put.back().East() == add.West()))
            return true;
        }
      return false;  
    }  
}

template <class T>
void Tetravex<T>::solve2(std::vector<Tetravex<T>>& all_soluce,
                        std::vector<Tile<T>>& put,
                        std::vector<Tile<T>>& copy)
{
  if (copy.empty())
    {
      Tetravex<T> res(size_-48);
      for(size_t i = 0; i < put.size(); i++)
        res.add_tile(put[i]);
      all_soluce.push_back(res);
    }
  else
    {
      for(size_t i = 0; i < copy.size();i++)
        {
          auto save = copy[copy.size()-1];
          copy.pop_back();
          if (resolvave(put, save))
            {
              put.push_back(save); //pos la tuil
              solve2(all_soluce, put, copy); // check pour les autres tuiles;
              put.pop_back();
            }
          copy.insert(copy.begin(), save); //remet la tuile a la fin
        }
    }
}

template <class T>
int Tetravex<T>::solve(const std::string& output)
{
  
  std::vector<Tetravex<T>> all_soluce;
  std::vector<Tile<T>> copy = tiles_;
   for(size_t i = 0; i < tiles_.size(); ++i)
    {
      auto save = copy[copy.size()-1];
      copy.pop_back();
      std::vector<Tile<T>> put;
      put.push_back(save); //pos la tuil
      solve2(all_soluce, put, copy); // check pour les autres tuiles;
      put.pop_back();
      copy.insert(copy.begin(), save); //remet la tuile a la fin
    }
  if (all_soluce.size() > 0)
    {
      if (all_soluce.size() == 1)
        all_soluce[0].write(output+".vex");
      else  
        for(size_t i = 0; i < all_soluce.size(); ++i)
          {
            std::string file= output+"_"+std::to_string(i)+".vex";
            all_soluce[i].write(file);
          }
      return 0;
    }
  return 1;
}

template <class T>
Tetravex<T> generate(uint8_t size);

template<>
Tetravex<int> generate<int>(uint8_t size)
{
  Tetravex<int> tab(size); 
  std::srand(std::time(0));
  float max = RAND_MAX;
  int random_ = 0;
  int size_ = size;
  for(int i = 0; i < size_; ++i)
    {
      for( int j = 0; j < size_; ++j)
        {
          Tile<int> tuile;
          if (i != 0 && j != 0)
            {
             int South = tab.index_board(i-1,j).South();
             int East = tab.index_board(i,j-1).East();
             tuile.set(East,3);
             tuile.set(South,2);
            }
          if(i == 0 && j != 0)
            {
              int  East = tab.index_board(i,j-1).East();
             tuile.set(East,3);
             random_ = (std::rand()/max)*9;
             tuile.set(random_,2);
              
            }
          if(i != 0 && j == 0)
            {
              int South = tab.index_board(i-1,j).South();
              tuile.set(South,2);
              random_ = (std::rand()/max)*9;
              tuile.set(random_,3);
            }
          if(i == 0 && j ==0)
            {
              random_ = (std::rand()/max)*9;
              tuile.set(random_,2);
              random_ = (std::rand()/max)*9;
              tuile.set(random_,3);
           }
          random_ = (std::rand()/max)*9;
          tuile.set(random_,0);
          random_ = (std::rand()/max)*9;
          tuile.set(random_,1);
         tab.add_tile(tuile);
        }
    }
  return tab;
}
