#include "BankSystemMain.hpp"

int main() {
  Facade facade;
  Interface interface(facade);
  interface.Run();
  return 0;
}