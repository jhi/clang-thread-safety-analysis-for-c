#include "tsa.h"

#include "tsa.h"

tsa_mutex mut;

void acquire() TSA_ACQUIRE(&mut)
{
#ifndef TSA_PASS
#else
    tsa_mutex_lock(&mut);
#endif
}

int main()
{
    acquire();
    tsa_mutex_unlock(&mut);
}
