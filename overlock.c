#include "tsa.h"

tsa_mutex mut;

int main()
{
#ifndef TSA_PASS
    tsa_mutex_lock(&mut);
    tsa_mutex_lock(&mut);
#else
    tsa_mutex_lock(&mut);
#endif
    tsa_mutex_unlock(&mut);
}
