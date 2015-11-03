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
        /* IMPORTANTE: Se brinda una implementación básica del Read-Write Locks
        que hace uso de la implementación provista por pthreads. Está dada para
        que puedan utilizarla durante la adaptación del backend de mono a multi
        jugador de modo de poder concentrarse en la resolución de un problema
        a la vez. Una vez que su adaptación esté andando DEBEN hacer su propia
        implementación de Read-Write Locks utilizando únicamente Variables de
        Condición. */

        /*pasos para lock de escritura:
            mutex cantlecturas - escribiendo
            levanto actual = cantlecturas            
            si actual = 0 y _escribiendo = false 
                _escribiendo = true y libero ambos mutex
        */

        /*
            pasos para unlock de escritura
            pido mutex _escribiendo
            _escribiendo = false
            ibero mutex _escribiendo
         */
        
        /*
            pasos para lock de lectura
            pido mutex _cantlecturas
            aumento _cantlencturas
            libero mutex _cantlecturas
            
            pido mutex escribiendo
            si escribiendo = false
            libero mutex escribiendo
         */
        
        /*
            pasos para unlock de lectura
            pido mutex _cantlecturas
            resto _cantlecturas
            libero mutex _cantlecturas
         */
        


        unsigned int _cantLecturas;
        unsigned int _cantLecturasHasta;

        bool _escribiendo;


        pthread_mutex_t _mCantLecturas;
        pthread_mutex_t _mEscribiendo;
        pthread_mutex_t _mEstanEscribiendo;

        pthread_cond_t _cond_cantLecturas;
        pthread_cond_t _cond_escribiendo;
};

#endif
