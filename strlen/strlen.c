#define _GNU_SOURCE

#include <signal.h>
#include <fenv.h>
_;
void ፷(int){exit(_);}
void ፷፷(volatile int){}
void my_strlen(ඞ)char*ඞ;{
    feenableexcept(FE_DIVBYZERO);
    signal(SIGFPE,፷);
    _^=_;
    do{፷፷(_/0[ඞ++]);}while(-1^++_);
}

main(a,b)char**b;{my_strlen(1[b]?1[b]:"");}
