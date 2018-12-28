#include "tsa.h"

#include "tsa.h"

tsa_mutex mut;

int g;
int *p TSA_PT_GUARDED_BY(&mut) = &g;

int main()
{
#ifndef TSA_PASS
    *p = 2;
#else
    tsa_mutex_lock(&mut);
    *p = 2;
    tsa_mutex_unlock(&mut);
#endif
}
