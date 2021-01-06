// board.hh
// This header ensures C linkage is enforced when running C++ unit tessts on C code.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

#ifdef __cplusplus
}
#endif
