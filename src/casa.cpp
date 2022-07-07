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

pair<int, int> Casa::find_top_bottom(vector<int> a, int j){
  int top, bottom;
  int index = j;
  int max_index = a.size() - 1;
  index++;

  while(index <= max_index){
    if(a[index] == 0){
       top = index - 1;
       break; 
    }
    index++;
  }
  if(index == max_index) top = max_index;

  index = j;
  while(index >= 0){
    if(a[index] == 0){
      top = index - 1;
      break;
    }
    index--;
  }
  if(index == 0) bottom = a[0];

  return pair<int, int>(top, bottom);
}

int Casa::smaller(vector<int> a){
  int menor = a[0];
  for(int i = 1; i < a.size(); i++){
    if(a[i] < menor) menor = a[i];
  }
  return menor;
}

/**
 * @class Casa
 * @brief
 * @return
*/
vector<pair<int, int>> Casa::max_space(){
  vector<int> temp;
  vector<pair<int, int>> v;
  temp = house[0];
  
  for(int i = 1; i < linhas; i++){
    for(int j = 0; j < colunas; j++){
      if(house[i][j] == 0){
        if(house[i-1][j] != 0){
          pair<int, int> top_bot = this->find_top_bottom(temp, j);
          int menor = smaller(temp);
          int larg = top_bot.second - top_bot.first + 1;
          v.push_back(pair<int, int>(menor, larg));
        }
        temp[j] = 0;
      } 
      else temp[j] += 1;
    }
  }
  
  return possible_widths(&temp);
}

/***/
vector<pair<int, int>> Casa::possible_widths(vector<int> *v){
  vector<pair<int, int>> pares;
  int temp, larg, alt = 0;
  
  for(vector<int>::iterator i = v->begin(); i != v->end(); i++){
    if(*i == 0){
      larg = temp;
      pares.push_back(pair<int, int>(larg, alt));
      temp = 0;
      alt = 0;
    }else{
      if(*i < alt) alt = *i;
      temp += 1;
    } 
  } 
  return pares;
}

/**
 * 
*/
void Casa::find_best_table(){
  vector<pair<int, int>> espacos = this->max_space();
  vector<Mesa> mesas_viaveis;

  for(int i = 0; i < tables.size(); i++){
    if(tables[i].cabe(espacos)) mesas_viaveis.push_back(tables[i]);
  }

  int maior = 0;
  for(int i = 1; i < tables.size(); i++){
    if(tables[i].get_area() > tables[maior].get_area()) maior = i;
    else if(tables[i].get_area() == tables[maior].get_area()){
      if(tables[maior].get_dimensions().first < tables[i].get_dimensions().first) maior = i;
    }
  }

  this->best_table = tables[maior].get_dimensions();
  bool rodou = tables[maior].get_rodou();
  
  if(!rodou) cout << this->best_table.first << " " << this->best_table.second;
  else cout << this->best_table.second << " " << this->best_table.first;

}

/**
 * @class Casa
 * @brief Utilizado apenas para verificar resultados :)
*/
void Casa::debug_info(){
  cout << "| INFORMAÇÕES DA CASA |" << endl;
  for(vector<vector<int>>::iterator i = house.begin(); i != house.end(); i++){
    for(vector<int>::iterator j = i->begin(); j != i->end(); j++){
      cout << *j;
    }
    cout << endl;
  }

  cout << "Mesas cotadas: " << tables.size() << endl;
  cout << "| Dimensões das mesas |" << endl;
  for(vector<Mesa>::iterator i = tables.begin(); i != tables.end(); i++){
    cout << i->get_dimensions().first << " x " << i->get_dimensions().second << endl;
  }

  cout << "Melhor mesa possível: " << best_table.first << " x " << best_table.second << endl;
}
