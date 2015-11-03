#include "RWLock.h"

void escribir(int &var) {

  var++;
  
}

void leer(int var) {

  std::cout << "var: " << var << std::endl;
  
}

int main(int argc, char* argv[]) {

  int var = 0;
  
  pthread_t tid
  pthread_create(&tid, NULL, escribir, NULL);
  pthread_create(&tid, NULL, leer, NULL);


    return 0;
}


