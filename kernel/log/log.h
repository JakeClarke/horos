#pragma once

#include "../display.h"
#include "fmt.h"

namespace horos {
namespace log {

enum class Lvl {
    info,
    error,
    fatal
};

template<typename ... Params>
void info(const char * fmt, Params... args) {
    printLvl(Lvl::info, fmt, args...);
}


template<typename ... Params>
void printLvl(Lvl, const char * fmt, Params... args){
    char buff[1024];
    sfmt(buff, sizeof(buff), fmt, args...);

    display::fbWriteString(buff);
}

}
}