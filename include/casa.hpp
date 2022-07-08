#ifndef CASA_H
#define CASA_H

#include <vector>
#include "mesa.hpp"
using namespace std;

class Casa{
  private:
    int linhas = 0;
    int colunas = 0;
    vector<vector<int>> house;
    vector<Mesa> tables;
    pair<int, int> best_table;

    vector<int> set_linha(string l);
    pair<int, int> max_space();
    pair<int, int> max_rectangle_temp(vector<int> temp);

  public:
    void find_best_table();
    void set_mesas(int mesas);
    void set_casa(int linhas, int colunas);
};

#endif