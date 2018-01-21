#include <iostream>
#include "window.h"
#include <memory>

using namespace std;

int main() {
     Xwindow first(199,199);
      first.drawBigString(0, 50, "caonima",  Xwindow::Black);
  while(1) {
    string cmd;
    cin >> cmd;
    if (cmd == "stop") break;
    else if (cmd == "replace") {
      first.fillRectangle(0,0,199,199, Xwindow::White);
      first.drawBigString(0,50, "replace", Xwindow::Black);
    } 
  }
}

