#include "stack.h"
#include <iostream>
using namespace std;
bool is_pair(char b, char p) {

  switch (b) {
  case '(':
    return p == ')';
  case '{':
    return p == '}';
  case '[':
    return p == ']';
  default:
    return false;
  }
}

int main() {
  const int N = 11;
  char str[N] = "(((][)){})"; // (((][)){}) , ({}[({})])
  Stack K(N);
  for (int i = 0; i < N - 1; i++) {
    if (str[i] == '{' || str[i] == '(' || str[i] == '[') {
      K.push(str[i]);
    }
    if (str[i] == '}' || str[i] == ')' || str[i] == ']') {
      if (is_pair(K.top(), str[i])) {
        K.pop();
      } else {
        cout << "NO \n";
        return 0;
      }
    }
  }
  if (K.get_size() == 0) {
    cout << "OK \n";
  }
}