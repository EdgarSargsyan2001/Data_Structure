#include <iostream>
using namespace std;
#include "Point.h"
#include "Queue.h"

int main() {

  try {
    const int N = 10;
    Queue<Point> Q(N * N);
    int x = 3;
    int y = 9;
    Q.enqueue(Point(x, y));
    int arr[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 1, 1, 1}, 
        {0, 0, 0, 1, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, 
        {0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1, 0, 0}, 
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    };
    int steps[N][N];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        steps[i][j] = -1;
      }
    }
    steps[x][y] = 0;
    int positionArr[4][2] = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1},
    };

    while (!Q.empty()) {

      int x = Q.fromt().get_X();
      int y = Q.fromt().get_Y();

      for (int i = 0; i < 4; i++) {
        int delX = x + positionArr[i][0];
        int delY = y + positionArr[i][1];
        bool isExist = (delX >= 0 && delX < N) && (delY >= 0 && delY < N);

        if (isExist && arr[delX][delY] == 0 && steps[delX][delY] == -1) {
          steps[delX][delY] = steps[x][y] + 1;
          Q.enqueue(Point(delX, delY));
        }
      }

      Q.dequeue();
    };

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (steps[i][j] == -1) {
          cout << steps[i][j] << "  ";
        } else {
          if (steps[i][j] >= 10 && steps[i][j] < 100) {
            cout << " " << steps[i][j] << " ";
          } else {
            cout << " " << steps[i][j] << "  ";
          }
        }
      }
      cout << endl;
    }
  } catch (int k) {
    switch (k) {
    case 1:
      cerr << "Queis full, can't add new item.\n";
    case 2:
      cerr << "there is no element.\n";
    }
  }
}
