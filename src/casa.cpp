#include "casa.hpp"
#include <iostream>

/**
 * @class Casa
 * @brief transforma o modelo de casa da entrada em uma matriz binária que facilita os cálculos dos retângulos.
 * @param linhas Linhas da matriz
 * @param colunas Colunas da Matriz
*/
void Casa::set_casa(int linhas, int colunas){
  string linha;
  this->linhas = linhas;
  this->colunas = colunas;

  getline(cin, linha);

  while(linhas > 0){
    getline(cin, linha);
    house.push_back(this->set_linha(linha));
    linhas--;
  }
}

/**
 * @class Casa
 * @brief Transforma uma string contendo caracteres # ou . em um vetor de inteiros contendo 0's ou 1's 
 * @param l string contendo caracteres a serem transformados.
 * @return vector<int> contendo apenas 0's e 1's
*/
vector<int> Casa::set_linha(string l){
  int asciidot = 46;

  vector<int> line;
  for(string::iterator i = l.begin(); i != l.end(); i++){
    if((*i) == asciidot) line.push_back(1);
    else line.push_back(0);
  }

  return line;
}

/**
 * @class Casa
 * @brief Cria um vetor com as opções de mesa que foram cotadas para a casa
 * @param mesas Número de mesas que serão cotadas
*/
void Casa::set_mesas(int mesas){
  int larg;
  int comp;

  while(mesas > 0){
    cin >> comp >> larg;
    tables.push_back(Mesa(larg, comp)); 
    mesas--;
  }
}

/**
 * @class Casa
 * @brief Acha o retângulo de maiores dimensões na matriz Casa
 * @return vector<pair<int, int> 
*/
pair<int, int> Casa::max_space(){
  vector<int> temp;
  pair<int, int> max_ret = {0, 0};
  pair<int, int> temp_ret;

  temp = house[0];

  for(int i = 1; i < linhas; i++){
    for(int j = 0; j < colunas; j++){
      if(house[i][j] == 0) temp[j] = 0;
      else temp[j] += 1;
    }
    
    temp_ret = max_rectangle_temp(temp);
    if(temp_ret.first * temp_ret.second > max_ret.first * max_ret.second) max_ret = temp_ret;
  }
  
  return max_ret;
}

pair<int, int> Casa::max_rectangle_temp(vector<int> temp){
  vector<int> pilha;
  vector<vector<int>> subvetores;
  vector<pair<int, int>> abc;
  int last = 0;

  int max_area = -1;
  pair<int, int> max_measures = {0, 0};

  // for(int i = 0; i < temp.size(); i++){
  //   if(temp[i] == 0){
  //     vector<int> t;
  //     for(int j = last + 1; j < i; j++) t.push_back(temp[j]);
  //     subvetores.push_back(t);
  //     last = i;
  //   }
  // }

  // for(int z = 0; z < subvetores.size(); z++){    
  //   if(subvetores[z].size() > 0){
  int x;
  for(x = 0; x < temp.size();){
    if(pilha.empty() || temp[x] >= temp[pilha[pilha.size() - 1]]){
      pilha.push_back(x++);
    }
    else{
      int top = pilha[pilha.size() - 1];
      pilha.pop_back();

      if(pilha.empty()){
        pair<int, int> t(x, temp[top]);
        int area = t.first * t.second;
        if(area > max_area){
          max_measures = t;
          max_area = area;
        }
      }else{
        pair<int, int> t(x - pilha[pilha.size() - 1] - 1, temp[top]);
        int area = t.first * t.second;
        if(area > max_area){
          max_measures = t;
          max_area = area;
        }
      }
    }
  }

  while (!pilha.empty()){
      int top = pilha[pilha.size() - 1];
      pilha.pop_back();

      if(pilha.empty()){
        pair<int, int> t(x, temp[top]);
        int area = t.first * t.second;
        if(area > max_area){
          max_measures = t;
          max_area = area;
        }
      }else{
        pair<int, int> t(x - pilha[pilha.size() - 1] - 1, temp[top]);
        int area = t.first * t.second;
        if(area > max_area){
          max_measures = t;
          max_area = area;
        }
      }
    }
  return max_measures;
}

/**
 * 
*/
void Casa::find_best_table(){
  pair<int, int> espacos = this->max_space();
  vector<Mesa> mesas_viaveis;

  for(int i = 0; i < tables.size(); i++){
    if(tables[i].cabe(espacos)) mesas_viaveis.push_back(tables[i]);
  }

  int maior = 0;
  for(int i = 1; i < mesas_viaveis.size(); i++){
    if(mesas_viaveis[i].get_area() > mesas_viaveis[maior].get_area()) maior = i;
    else if(mesas_viaveis[i].get_area() == mesas_viaveis[maior].get_area()){
      if(mesas_viaveis[maior].get_dimensions().first < mesas_viaveis[i].get_dimensions().first) maior = i;
    }
  }

  this->best_table = mesas_viaveis[maior].get_dimensions();
  bool rodou = mesas_viaveis[maior].get_rodou();

  if(!rodou) cout << this->best_table.first << " " << this->best_table.second;
  else cout << this->best_table.second << " " << this->best_table.first;

}
