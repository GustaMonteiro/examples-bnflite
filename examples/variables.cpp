#include "bnflite.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace bnf;

template <typename T> void printVector(vector<T> vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << i << ": " << vec[i].text << " (" << vec[i].length << ")" << endl;
  }
  cout << endl;
}

void trimString(string &str) {
  size_t first = str.find_first_not_of(" \n\t\r");
  size_t last = str.find_last_not_of(" \n\t\r");

  str = str.substr(first, (last - first + 1));
}

struct Variable {
  string type;
  string name;
  string value;

  Variable(string type, string name) : type(type), name(name) {}
};

vector<Variable> variables;

typedef Interface<int> Var;

Var DoLeftSide(vector<Var> &res) {
  // cout << "-> Entrou no DoLeftSide" << endl << endl;

  // printVector(res);

  string type = string(res[0].text, res[0].length);
  string name = string(res[1].text, res[1].length);

  trimString(type);
  trimString(name);

  variables.push_back(Variable(type, name));

  return Var(res.front(), res.back());
}

Var DoRightSide(vector<Var> &res) {
  // cout << "-> Entrou no DoRightSide" << endl << endl;

  // printVector(res);

  string value = string(res[0].text, res[0].length);

  trimString(value);

  variables.back().value = value;

  return Var(res.front(), res.back());
}

const char *vars =
    "   string      nome     =      Gustavo Cesar     ;\n"
    "                 int idade      =  20;\n"
    "char     letraInicial =    G   ;\n"
    " bool         seraQueIssoFunciona                    = true;\n"
    "          double         \n"
    "     numero  =  223.32;";

int main() {
  Token space(" \t");
  Token delimiter(" \t\n\r");

  Token name('a', 'z');
  name.Add('A', 'Z');

  Token value('a', 'z');
  value.Add('A', 'Z');
  value.Add('0', '9');
  value.Add(" .");

  Lexem _int = "int";
  Lexem _bool = "bool";
  Lexem _char = "char";
  Lexem _double = "double";
  Lexem _float = "float";
  Lexem _string = "string";

  Lexem Space = *space;
  Lexem Semicolon = Space + ";" + Space;
  Lexem Equal = Space + "=" + Space;

  Lexem Type = (_int | _bool | _char | _double | _float | _string);
  Lexem Name = 1 * name;
  Lexem Value = 1 * value;

  Lexem Delimiter = *delimiter;

  Rule LeftSide = Delimiter + Type + Name;
  Rule RightSide = Value + Semicolon;

  Rule Declaration = Delimiter + *(LeftSide + Equal + RightSide + Delimiter);

  Bind(LeftSide, DoLeftSide);
  Bind(RightSide, DoRightSide);

  Var var;

  int res = Analyze(Declaration, vars, var);

  if (res > 0) {
    cout << "Found " << variables.size() << " variables declaration!" << endl
         << endl;
    for (int i = 0; i < variables.size(); i++) {
      cout << "Type (" << variables[i].type.length()
           << "): " << variables[i].type << endl;
      cout << "Name (" << variables[i].name.length()
           << "): " << variables[i].name << endl;
      cout << "Value (" << variables[i].value.length()
           << "): " << variables[i].value << endl;
      cout << endl;
    }
    return 0;
  }

  cout << "Deu errado (" << res << ")" << endl;
  return -1;
}