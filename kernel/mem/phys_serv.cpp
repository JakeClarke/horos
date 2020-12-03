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


        return false;
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
            ledgerByte &= 0xff ^ (1 << bitOffset);
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
    s_physMem = value;
    kmemset(s_ledger, 0, sizeof(s_ledger));

    Offset allocated;
    if (!allocatePhysical(kernel_virtual_start, goodSize(kernel_virtual_size), allocated)) 
    {
        panic("failed to allocate kernel space");
    }

    if (allocated != kernel_virtual_start)
    {
        panic("allocated did not match kernel start");
    }
}

bool horos::mem::allocatePhysical(Offset start, Offset size, Offset& out) {
    if(goodSize(size) != size) {
        panic("size must be in page size");
    }

    if(start != 0 && goodSize(start) != start) {
        panic("start must be aligned to the page size");
    }


    const auto requiredPages = size / PageSize;

    for (Offset current = start; current < s_physMem; current += PageSize)
    {
        if(pageInUse(current)) {
            continue;
        }

        Offset start = current;

        while(current - start != 0 && !pageInUse(current)){
            current += PageSize;
        }

        // found a good page
        if (current - start == 0)
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
