#pragma once

using Offset = unsigned int;

namespace horos {
namespace mem {
    constexpr Offset PageSize = 4096;
    void init(Offset size);
    constexpr Offset goodSize(Offset size) {
        return size % PageSize == 0 ? size : size + (PageSize-size);
    }

    bool allocatePhysical(Offset start, Offset size, Offset& out);
}
}