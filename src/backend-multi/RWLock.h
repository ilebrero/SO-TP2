#ifndef RWLock_h
#define RWLock_h
#include <iostream>
#include <unistd.h>

class RWLock {
    public:
        RWLock();
        void rlock();
        void wlock();
        void runlock();
        void wunlock();

    private:
        unsigned int _cantLecturas;
        unsigned int _cantLecturasHasta;

        pthread_mutex_t _mCantLecturas;
        pthread_mutex_t _mEscribiendo;

        pthread_cond_t _cond_cantLecturas;
};

#endif
