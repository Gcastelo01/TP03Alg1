#include "mesa.hpp"

/**
 * @class Mesa
 * @brief Construtor da calsse
*/
Mesa::Mesa(int largura, int comprimento) : largura(largura), comprimento(comprimento){
  this->area_total = largura * comprimento;
}

/**
 * @class Mesa
 * @brief Rotaciona a mesa em 90 graus, invertendo largura e comprimento.
*/
void Mesa::gira_mesa(){
  int temp = this->largura;
  this->largura = this->comprimento;
  this->comprimento = temp;
}

/**
 * @class Mesa
 * @brief Coloca um valor no atributo comprimento
 * @param comp Comprimento da mesa
*/
void Mesa::set_comprimento(int comp){
  this->comprimento = comp;
}

/**
 * @class Mesa
 * @brief Coloca uma valor no atributo largura
 * @param larg Largura da mesa
*/
void Mesa::set_largura(int larg){
  this->largura = larg;
}

/**
 * @class Mesa
 * @brief Gera um par com as dimensões da mesa (comprimento, largura)
 * @return pair<int, int> com as dimensões
*/
pair<int, int> Mesa::get_dimensions(){
  return pair<int, int>(comprimento, largura);
}

bool Mesa::cabe(vector<pair<int, int>> a){
  for(vector<pair<int, int>>::iterator i = a.begin(); i != a.end(); i++){
    if(i->first >= this->largura && i->second >= this->comprimento) return true;
    else{
      this->gira_mesa();
      if(i->first >= this->largura && i->second >= this->comprimento) return true;
      return false;
    }
  }
  return false;
}

int Mesa::get_area(){
  return this->area_total;
}
