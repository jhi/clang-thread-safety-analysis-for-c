#include "tsa.h"

tsa_mutex mut;

int g TSA_GUARDED_BY(&mut);

int main()
{
#ifndef TSA_PASS
    g = 1;
#else
    tsa_mutex_lock(&mut);
    g = 1;
    tsa_mutex_unlock(&mut);
#endif
}
