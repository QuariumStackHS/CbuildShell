#include <iostream>

#include <cstring>
#include <string>

#include <fstream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;
namespace BrainFuckInterpreter {
char Matrix[30000] = {0};
map<unsigned long long, unsigned long long> FTmap;
int PTR = 0;
void Reset() {
  for (int i = 0; i < sizeof(Matrix); i++)
    Matrix[i] = 0;
  PTR = 0;
}
int Execute(string Code) {
  vector<int> Fting;
  for (int i = 0; i < Code.size(); i++) {
    if (Code[i] == '[')
      Fting.push_back(i);
    else if (Code[i] == ']')
      FTmap[i] = Fting[Fting.size() - 1], FTmap[Fting[Fting.size() - 1]] = i,
      Fting.pop_back();
  }
  for (int i = 0; i < Code.size(); i++) {
    if (Code[i] == '>')
      ++PTR;
    if (Code[i] == '<')
      --PTR;
    if (Code[i] == '.')
      cout << Matrix[PTR];
    if (((Code[i] == '[') && Matrix[PTR] == 0) ||
        ((Code[i] == ']') && Matrix[PTR] != 0))
      i = FTmap[i];
    if (Code[i] == ',')
      Matrix[PTR] = getchar();
    if (Code[i] == '+')
      ++Matrix[PTR];
    if (Code[i] == '-')
      --Matrix[PTR];
  }
}
}; // namespace BrainFuckInterpreter

#define S2Seq(a, b) (strcmp(a.c_str(), b.c_str()) == 0)
#define S2Ceq(a, b) (strcmp(a.c_str(), b) == 0)
vector<string> LastWords;
int Cursor = 0;
string GetfromuntilEnd() {
  string Conc = "";

  // cout<<Cursor<<" "<<LastWords.size()<<endl;
  while (Cursor < LastWords.size() - 1)
    Conc += (LastWords[Cursor] + " "), Cursor++;
  Conc.pop_back();
  return Conc;
}
string fromUntil(string s, int a, int b) {
  string CP = "";
  for (int i = a; i <= b; i++)
    CP.push_back(s[i]);
  return CP;
}
int main(int argc, char **argv) {
  string LastWord = "";

  while (!S2Ceq(LastWord, "!exit")) {
    while (!S2Ceq(LastWord, "$!") && !S2Ceq(LastWord, "!")&&!S2Ceq(LastWord, "b!")) {
      cin >> LastWord;
      LastWords.push_back(LastWord);
    }

    if (S2Ceq(LastWord, "$!")) {
      system(GetfromuntilEnd().c_str());
    }
    if (S2Ceq(LastWord, "b!")) {
      BrainFuckInterpreter::Execute(GetfromuntilEnd());
      BrainFuckInterpreter::Reset();
    }

    LastWord = "";
    Cursor++;
  }
}