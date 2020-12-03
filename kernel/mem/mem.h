#pragma once

#include "types.h"

namespace horos{
extern "C" {

extern Offset kernel_virtual_start;
extern Offset kernel_virtual_end;
extern Offset kernel_virtual_size;
extern Offset kernel_physical_start;
extern Offset kernel_physical_end;
extern Offset kernel_physical_size;
}
}
