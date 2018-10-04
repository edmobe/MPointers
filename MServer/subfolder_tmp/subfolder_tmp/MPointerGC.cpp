#include "MPointerGC.h"

template<>
bool MPointerGC<int>::initialized = false;

template<>
int MPointerGC<int>::current_id = 0;