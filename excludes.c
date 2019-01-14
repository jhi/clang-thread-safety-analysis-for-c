#include "tsa.h"

tsa_mutex mut;

void excludes(void) TSA_EXCLUDES(&mut)
{
}

int main()
{
#ifndef TSA_PASS
    tsa_mutex_lock(&mut);
    excludes();
    tsa_mutex_unlock(&mut);
#else
    excludes();
#endif
}
