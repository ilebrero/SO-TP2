#include "RWLock.h"

RWLock lock;
int var = 0;

void escribir() {

  for (int i = 0; i < 300 ; ++i) {
    lock.wlock();
    var++;
    lock.wunlock();
//    std::cout << "termine de unlock escribir" << std::endl;
    //sleep(1);
  }
  
}

void leer() {

  for (int j = 0; j < 300 ; ++j) {
    lock.rlock();
    std::cout << "var: " << var << std::endl;
    lock.runlock();
 //   std::cout << "termine de unlock leer" << std::endl;
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
  /*

  for (int i = 0 ; i < 149 ; i+=2) {
    pthread_create(&tid[i], NULL, (void* (*)(void*)) leer, NULL);
    pthread_create(&tid[i+1], NULL,(void* (*)(void*)) escribir, NULL);
    pthread_join(tid[i], NULL);
    pthread_join(tid[i+1], NULL);
  
  }
 */
  /*
  pthread_create(&tid2, NULL,(void* (*)(void*)) leer, NULL);
  pthread_create(&tid1, NULL,(void* (*)(void*)) escribir, NULL);
  pthread_create(&tid3, NULL,(void* (*)(void*)) leer, NULL);
  pthread_create(&tid4, NULL,(void* (*)(void*)) leer, NULL);
  pthread_create(&tid5, NULL,(void* (*)(void*)) escribir, NULL);
  pthread_create(&tid6, NULL,(void* (*)(void*)) leer, NULL);


  pthread_join(tid2, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);
  pthread_join(tid5, NULL);
  pthread_join(tid6, NULL);
*/
