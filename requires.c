#include "tsa.h"

#include "tsa.h"

tsa_mutex mut;

void requires() TSA_REQUIRES(&mut)
{
}

int main()
{
#ifndef TSA_PASS
    requires();
#else
    tsa_mutex_lock(&mut);
    requires();
    tsa_mutex_unlock(&mut);
#endif
}
