#pragma once

#include "phys_serv.h"

namespace horos{
namespace mem {
    template<typename ValueType, int count = 100>
    class SlabAlloc {
        struct Ledger {
            char inUse[count/8];
            char values[count * sizeof(ValueType)];
        }
        static_assert(PageSize > sizeof(ValueType), "value must");
        static_assert(sizeof(Ledger) < PageSize, "slab ledger must be less then PageSize");
        
        Ledger * root = nullptr;

        static Offset calcSize(int elements = 0) {
            const int currSize = sizeof(ValueType) * elements + bitsRequired(elements);
            return calcSize(elements + (elements / 2)) > PageSize : currSize: calcSize(elements + (elements / 2)));
        }

        static int bitsRequired(int numElements) {
            return numElements / 8 > 0 ? numElements / 8 : 1;
        }

    public:
        ValueType * alloc();
        void free(ValueType *);
    };

    template<typename ValueType, int count> 
    ValueType* SlabAlloc<ValueType, count>::alloc() {
        
    }

    template<typename ValueType, int count> 
    void SlabAlloc<ValueType, count>::free(ValueType *  ptr) {
        
    }

}
}

