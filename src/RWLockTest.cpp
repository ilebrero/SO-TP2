#include "RWLock.h"

RWLock lock;
int var = 0;

void escribir() {

  for (int i = 0; i < 300 ; ++i) {
    lock.wlock();
    var++;
    lock.wunlock();
  }
  
}

void leer() {

  for (int j = 0; j < 300 ; ++j) {
    lock.rlock();
    std::cout << "var: " << var << std::endl;
    lock.runlock();
  }
  
}

void test1() {
  // Este test chequea que escriba bien todos los threads
  pthread_t tid[100];
  pthread_t p;

  for (int i = 0 ; i < 100 ; ++i) {
    pthread_create(&tid[i], NULL, (void* (*)(void*)) escribir, NULL);
    pthread_join(tid[i], NULL);
  }

  pthread_create(&p, NULL, (void* (*)(void*)) leer , NULL);
  pthread_join(p, NULL);
}

void test2() {
  // Este test chequea la falta de deadlock e inanicion por fuerza bruta
  pthread_t tid[152];
  for (int i = 0 ; i < 152 ; i+=4) {
    pthread_create(&tid[i], NULL, (void* (*)(void*)) leer, NULL);
    pthread_create(&tid[i+1], NULL,(void* (*)(void*)) escribir, NULL);
    pthread_create(&tid[i+2], NULL,(void* (*)(void*)) leer, NULL);
    pthread_create(&tid[i+3], NULL,(void* (*)(void*)) escribir, NULL);
    pthread_join(tid[i], NULL);
    pthread_join(tid[i+1], NULL);
    pthread_join(tid[i+2], NULL);
    pthread_join(tid[i+3], NULL);
  }
}

void test3() {
  // Este test chequea la falta de deadlock e inanicion por fuerza bruta
  pthread_t tid[152];
  for (int i = 0 ; i < 152 ; i+=4) {
    pthread_create(&tid[i], NULL, (void* (*)(void*)) leer, NULL);
    pthread_create(&tid[i+1], NULL,(void* (*)(void*)) escribir, NULL);
    pthread_create(&tid[i+2], NULL,(void* (*)(void*)) leer, NULL);
    pthread_create(&tid[i+3], NULL,(void* (*)(void*)) escribir, NULL);
  }

  for (int j = 0 ; j < 152 ; j+=4) {
    pthread_join(tid[j], NULL);
    pthread_join(tid[j+1], NULL);
    pthread_join(tid[j+2], NULL);
    pthread_join(tid[j+3], NULL);
  }
}

int main(int argc, char* argv[]) {

  test1();
  var = 0;
  test2();
  std::cout << "ultima var" << var << std::endl;
  var = 0;
  test3();
  std::cout << "ultima var" << var << std::endl;
  
  return 0;
}
