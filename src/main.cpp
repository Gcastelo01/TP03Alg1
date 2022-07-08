#include <iostream>
#include <casa.hpp>

int main(int argc, char* argv[]){
  Casa haus;
  int linhas, colunas;

  cin >> linhas >> colunas;
  haus.set_casa(linhas, colunas);

  cin >> linhas;

  haus.set_mesas(linhas);
  haus.find_best_table();

  return 0;
}