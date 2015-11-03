#include "RWLock.h"

RWLock lock;
int var = 0;

void escribir() {

  for (int i = 0; i < 3 ; ++i) {
    lock.wlock();
    var++;
    lock.wunlock();
 //   std::cout << "termine de unlock escribir" << std::endl;
    //sleep(1);
  }
  
}

void leer() {

  for (int j = 0; j < 3 ; ++j) {
    lock.rlock();
    std::cout << "var: " << var << std::endl;
    lock.runlock();
 //   std::cout << "termine de unlock" << std::endl;
  }
  
}

int main(int argc, char* argv[]) {

  
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
 
  pthread_create(&tid2, NULL,(void* (*)(void*)) leer, NULL);
  pthread_create(&tid1, NULL,(void* (*)(void*)) escribir, NULL);
  pthread_create(&tid3, NULL,(void* (*)(void*)) leer, NULL);


  pthread_join(tid2, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid3, NULL);

  return 0;
}



