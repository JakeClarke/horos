#include "phys_serv.h"
#include "mem.h"
#include "../panic.h"
#include "../utils.h"

namespace {
    struct Ledger {
        Ledger * next;
        static constexpr Offset numLedgerBytes = (horos::mem::PageSize - sizeof(Ledger*));
        static constexpr Offset numLedgerPages = numLedgerBytes * 8;
        static constexpr Offset numLedgerSize = numLedgerPages * horos::mem::PageSize;
        unsigned char pages[numLedgerBytes];
    };


    char s_ledger [((1*1024*1024*1024) / horos::mem::PageSize) / 8];

    bool pageInUse(Offset off) {
        Offset pageIdx = horos::mem::PageSize;
        Offset bitOffset = pageIdx % 8;
        Offset byteOffset = (pageIdx - bitOffset) / 8;

        char ledgerByte = s_ledger[byteOffset];

        return (ledgerByte & (1 << bitOffset)) != 0;
    }

    Offset pageAlign(Offset off) {
        return off - (off % horos::mem::PageSize);
    }

    void markPage(Offset page, bool inUse) {
        Offset pageIdx = horos::mem::PageSize;
        Offset bitOffset = pageIdx % 8;
        Offset byteOffset = (pageIdx - bitOffset) / 8;

        char ledgerByte = s_ledger[byteOffset];
        if (inUse)
        {
            ledgerByte |= 1 << bitOffset;
        } else {
            ledgerByte &= ~(1 << bitOffset);
        }
        s_ledger[byteOffset] = ledgerByte;
    }

    void markPage(Offset start, Offset len, bool inUse) {
        for (Offset curr = start; curr < len; curr += horos::mem::PageSize) {
            markPage(curr, true);
        }
    }

    static_assert(horos::mem::PageSize == sizeof(Ledger), "expected tracking ledger to be one page");

    Ledger* s_physRoot;
    Offset s_physMem;
}

void horos::mem::init(Offset value) {
    s_physMem = -1;
    kmemset(s_ledger, 0, sizeof(s_ledger));

    Offset allocated = 0;
    Offset kernelMemStart = pageAlign(kernel_virtual_start);
    Offset KerenlRange = goodSize((kernel_virtual_start - kernelMemStart) + kernel_virtual_size);
    bool success = allocatePhysical(kernelMemStart, KerenlRange, allocated);
    ASSERT(success && "failed to reserve kernel space");
    ASSERT(allocated == kernelMemStart && "allocated did not match kernel start");
}

bool horos::mem::allocatePhysical(Offset start, Offset size, Offset& out) {
    ASSERT(goodSize(size) == size && "size must be in page size");
    ASSERT(pageAlign(start) == start && "start must be aligned to the page size");

    for (Offset current = start; current < s_physMem; current += PageSize)
    {
        Offset start = current;

        while(current - start != size && !pageInUse(current)){
            current += PageSize;
        }

        // found a good page range
        if (current - start == size)
        {
            // mark range as used
            markPage(start, size, true);

            // return range
            out = start;
            return true;
        }
        
    }
    
    return false;
}
