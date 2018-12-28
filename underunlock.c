#include "tsa.h"

tsa_mutex mut;

int main()
{
    tsa_mutex_lock(&mut);
#ifndef TSA_PASS
#else
    tsa_mutex_unlock(&mut);
#endif
}
