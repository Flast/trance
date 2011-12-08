#include <trance/as_const.hpp>

int v = 0;
int &cv = trance::as_const( v );
