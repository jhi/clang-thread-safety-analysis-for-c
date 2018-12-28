#include "tsa.h"

tsa_mutex mut;

int main()
{
#ifndef TSA_PASS
#else
    tsa_mutex_lock(&mut);
#endif
    tsa_mutex_unlock(&mut);
}
