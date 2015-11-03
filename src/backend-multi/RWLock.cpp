#include "RWLock.h"

/* IMPORTANTE: Se brinda una implementación básica del Read-Write Locks
que hace uso de la implementación provista por pthreads. Está dada para
que puedan utilizarla durante la adaptación del backend de mono a multi
jugador de modo de poder concentrarse en la resolución de un problema
a la vez. Una vez que su adaptación esté andando DEBEN hacer su propia
implementación de Read-Write Locks utilizando únicamente Variables de
Condición. */

RWLock :: RWLock() {
  pthread_mutex_init(&_mCantLecturas,NULL);
  pthread_mutex_init(&_mEscribiendo,NULL);
  pthread_mutex_init(&_mEstanEscribiendo,NULL);
  pthread_cond_init(&_cond_cantLecturas, NULL);
  pthread_cond_init(&_cond_escribiendo, NULL);
  _cantLecturas = 0;
  _cantLecturasHasta = 0;
  _escribiendo = false;
}

void RWLock :: rlock() {
  pthread_mutex_lock(&_mCantLecturas);
    _cantLecturas++;
  pthread_mutex_unlock(&_mCantLecturas);

  pthread_mutex_lock(&_mEstanEscribiendo);
  while (_escribiendo) {
    pthread_cond_wait(&_cond_escribiendo, &_mEstanEscribiendo); 
  }

  pthread_mutex_unlock(&_mEstanEscribiendo);

}

void RWLock :: wlock() {

  pthread_mutex_lock(&_mEscribiendo);

  pthread_mutex_lock(&_mCantLecturas);

    _cantLecturasHasta = _cantLecturas;

  while (_cantLecturasHasta > 0) { 
//    std::cout << "cantLecturasHasta: " << _cantLecturasHasta << std::endl;
    pthread_cond_wait(&_cond_cantLecturas, &_mCantLecturas); 
  }
  pthread_mutex_lock(&_mEstanEscribiendo);
    _escribiendo = true;
  pthread_mutex_unlock(&_mEstanEscribiendo);

  pthread_mutex_unlock(&_mCantLecturas);
}

void RWLock :: runlock() {
  pthread_mutex_lock(&_mCantLecturas);
  if (_cantLecturasHasta > 0)
    _cantLecturasHasta--;

  if (_cantLecturasHasta == 0)
    pthread_cond_broadcast(&_cond_cantLecturas);

//  std::cout << "cantLecturas en unlockr: " << _cantLecturas << std::endl;
//  std::cout << "cantLecturasHasta en unlockr: " << _cantLecturasHasta << std::endl;
  _cantLecturas--;
  pthread_mutex_unlock(&_mCantLecturas);

}

void RWLock :: wunlock() {
  pthread_mutex_lock(&_mEstanEscribiendo);
    _escribiendo = false;

  pthread_cond_broadcast(&_cond_escribiendo);

  pthread_mutex_unlock(&_mEstanEscribiendo);

  pthread_mutex_unlock(&_mEscribiendo);
}

/*
void RWLock :: wlock() {

  std::cout << "estoy es lo ultimo E1" << std::endl;
  pthread_mutex_lock(&_mEscribiendo);

  std::cout << "estoy es lo ultimo E2" << std::endl;
  pthread_mutex_lock(&_mCantLecturas);

    _cantLecturasHasta = _cantLecturas;

  std::cout << "estoy es lo ultimo E3" << std::endl;
  while (_cantLecturasHasta > 0) { 
    std::cout << "cantLecturasHasta: " << _cantLecturasHasta << std::endl;
    pthread_cond_wait(&_cond_cantLecturas, &_mCantLecturas); 
  }
  std::cout << "estoy es lo ultimo E4" << std::endl;
  pthread_mutex_lock(&_mEstanEscribiendo);
  std::cout << "estoy es lo ultimo E5" << std::endl;
    _escribiendo = true;
  pthread_mutex_unlock(&_mEstanEscribiendo);

  std::cout << "estoy es lo ultimo E6" << std::endl;
  pthread_mutex_unlock(&_mCantLecturas);
}

void RWLock :: runlock() {
  pthread_mutex_lock(&_mCantLecturas);
  if (_cantLecturasHasta > 0) {
    _cantLecturasHasta--;
  } else {
    pthread_cond_signal(&_cond_cantLecturas);
  }
  std::cout << "estoy rdesbloqueando " << _cantLecturasHasta << std::endl;
    _cantLecturas--;
  pthread_mutex_unlock(&_mCantLecturas);

}

void RWLock :: wunlock() {
  std::cout << "estoy rdesafawefbloqueando " << std::endl;
  _escribiendo = false;
  pthread_mutex_unlock(&_mEscribiendo);
}
*/
