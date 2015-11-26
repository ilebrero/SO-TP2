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
  pthread_cond_init(&_cond_cantLecturas, NULL);
  _cantLecturas = 0;
  _cantLecturasHasta = 0;
}

void RWLock :: rlock() {
  pthread_mutex_lock(&_mEscribiendo);

  pthread_mutex_lock(&_mCantLecturas);
    _cantLecturas++;
  pthread_mutex_unlock(&_mCantLecturas);

  pthread_mutex_unlock(&_mEscribiendo);
}

void RWLock :: wlock() {
  pthread_mutex_lock(&_mEscribiendo);

  pthread_mutex_lock(&_mCantLecturas);

    _cantLecturasHasta = _cantLecturas;

  while (_cantLecturasHasta > 0) { 
    pthread_cond_wait(&_cond_cantLecturas, &_mCantLecturas); 
  }

  pthread_mutex_unlock(&_mCantLecturas);
}

void RWLock :: runlock() {
  pthread_mutex_lock(&_mCantLecturas);
  if (_cantLecturasHasta > 0)
    _cantLecturasHasta--;

  if (_cantLecturasHasta == 0)
    pthread_cond_signal(&_cond_cantLecturas);

  _cantLecturas--;
  pthread_mutex_unlock(&_mCantLecturas);
}

void RWLock :: wunlock() {
  pthread_mutex_unlock(&_mEscribiendo);
}
