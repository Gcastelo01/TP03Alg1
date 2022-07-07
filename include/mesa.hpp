#ifndef MESA_H
#define MESA_H

#include <map>
#include <vector>

using namespace std;

class Mesa{
  private:
    int largura = 0;
    int comprimento = 0;
    int area_total = 0;

  public:
    Mesa(int largura, int comprimento);
    void gira_mesa();
    void set_largura(int larg);
    void set_comprimento(int comp);
    bool cabe(vector<pair<int, int>> a);
    int get_area();
    pair<int, int> get_dimensions();
};

#endif