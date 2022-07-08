#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Mesa{
  private:
    int largura = 0;
    int comprimento = 0;
    int area_total = 0;
    bool rodou = false;

  public:
    Mesa(int largura, int comprimento);
    void gira_mesa();
    void set_largura(int larg);
    void set_comprimento(int comp);
    bool cabe(pair<int, int> a);
    int get_area();
    bool get_rodou();
    pair<int, int> get_dimensions();
};

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
  this->rodou = true;
}

bool Mesa::get_rodou(){
  return this->rodou;
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

bool Mesa::cabe(pair<int, int> a){
  if(a.first >= this->largura && a.second >= this->comprimento) return true;
  else{
    this->gira_mesa();
    if(a.first >= this->largura && a.second >= this->comprimento) return true;
    return false;
  }
}

int Mesa::get_area(){
  return this->area_total;
}

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