#include "tsa.h"

tsa_mutex mut;

int main()
{
    tsa_mutex_lock(&mut);
#ifndef TSA_PASS
    tsa_mutex_unlock(&mut);
    tsa_mutex_unlock(&mut);
#else
    tsa_mutex_unlock(&mut);
#endif
}
