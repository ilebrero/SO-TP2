#include "RWLock.h"

/* IMPORTANTE: Se brinda una implementación básica del Read-Write Locks
que hace uso de la implementación provista por pthreads. Está dada para
que puedan utilizarla durante la adaptación del backend de mono a multi
jugador de modo de poder concentrarse en la resolución de un problema
a la vez. Una vez que su adaptación esté andando DEBEN hacer su propia
implementación de Read-Write Locks utilizando únicamente Variables de
Condición. */

RWLock :: RWLock() {
  pthread_mutex_init(_mCantLecturas,1);
  pthread_mutex_init(_mEscribiendo,1);
  _cantLecturas;
  _cantLecturasHasta;
  pthread_rwlock_init(&(this->rwlock),NULL);
}

void RWLock :: rlock() {
  pthread_mutex_lock(_mCantLecturas);
    _cantLecturas++;
  pthread_mutex_unlock(_mCantLecturas);

  while (_escribiendo)

}

void RWLock :: wlock() {
  pthread_mutex_lock(_mEscribiendo);
  
  pthread_mutex_lock(_mCantLecturas);

    _cantLecturasHasta = _cantLecturas;

  while (_cantLecturasHasta != 0) { 
    pthread_cond_wait( &cond_cantLecturas , &_mCantLecturas); 
  }
  _escribiendo = true;
  pthread_mutex_unlock(_mEscribiendo);
  pthread_mutex_unlock(_mCantLecturas);
}

void RWLock :: runlock() {
}

void RWLock :: wunlock() {
  _escribiendo = false;
}
