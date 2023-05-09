#include "bnflite.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace bnf;

template <typename T> void printVec(vector<T> vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << i << ": " << vec[i].text << " (" << vec[i].length << ")" << endl;
  }
  cout << endl;
}

struct Section {
  string name;
  vector<pair<string, string>> values;
  Section(string name) : name(name) {}
};

typedef Interface<int> Var;

vector<Section> sections;

Var DoSection(vector<Var> &res) {

  // cout << "Entrou section" << endl;

  // printVec(res);

  string name = string(res[1].text, res[1].length);

  sections.push_back(Section(name));

  return Var(res.front(), res.back());
}

Var DoEntry(vector<Var> &res) {

  // cout << "Entrou entry" << endl;

  // printVec(res);

  string key = string(res[0].text, res[0].length);
  string value = string(res[2].text, res[2].length);

  sections.back().values.push_back(make_pair(key, value));

  return Var(res.front(), res.back());
}

const char *in = "    [             Person       ]   \n"
                 "   Name|Adalberto Junior Neto\n"
                 "   Idade   |   64 years old\n"
                 "   CPF     |                  111.111.111-11\n"
                 "   [ LibraryClasses  ] \n"
                 " AnythingElse| nope, go ahead...\n";

int main() {
  Token delimiter(" \t\n\r");
  Token space(" \t");

  Token name('a', 'z');
  name.Add('A', 'Z');

  Token value(1, 255);
  value.Remove("\n");

  Lexem Delimiter = *delimiter;

  Lexem Value = 1 * value;

  Lexem Name = 1 * name;
  Lexem Left = *space + "[" + *space;
  Lexem Right = *space + "]" + *space;

  Lexem Pipe = *space + "|" + *space;

  Rule Section = Left + Name + Right;
  Rule Entry = Name + Pipe + Value;

  Rule Program = Delimiter + *(Section + Delimiter + *(Entry + Delimiter));

  Bind(Section, DoSection);
  Bind(Entry, DoEntry);

  Var var;

  int res = Analyze(Program, in, var);

  if (res > 0) {

    for (int i = 0; i < sections.size(); i++) {
      cout << "-> " << sections[i].name << endl;
      for (int j = 0; j < sections[i].values.size(); j++) {
        cout << "\t" << sections[i].values[j].first << " = "
             << sections[i].values[j].second << endl;
      }
      cout << endl;
    }

    cout << "Done :)" << endl;
    return 0;
  }

  cout << "Something went wrong :/" << endl;

  return -1;
}