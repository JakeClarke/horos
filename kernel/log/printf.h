#pragma once

#include "../display.h"
#include "../panic.h"

namespace horos {
namespace logging {

int toString(char * buff, int remaining, const char* p) {
    int c = 0;
    while (p[c] != '\0') {
        if(c < remaining) {
            buff[c] = p[c];
        }
        c++;
    }
    
    return c;
}

int toString(char * buff, int remaining, unsigned int p) {
    const int base = 10;
    int c = 0;
    do
    {        
        int r = p % base;
        if (c < remaining) buff[c] = '0' + r;
        p /= base;
        c++;

    } while (p > 0);
    // reverse the string
    for (int i = 0; i < c /2; i++)
    {
        char tmp = buff[i];
        int r = c-(i+1);
        buff[i] = buff[r];
        buff[r] = tmp;
    }
    
    return c;
}

int toString(char * buff, int remaining, int p) {
    BREAK_PT;
    
    int negative = 0;
    if (p < 0)
    {
        *buff = '-';
        buff++;
        p = -p;
        remaining--;
        negative = 1;
    }

    return toString(buff, remaining, (unsigned int)p) +  negative;
}



enum class Lvl {
    info,
    error,
    fatal
};


template<typename ... Params>
void info(const char * fmt, Params... args) {
    printLvl(Lvl::info, fmt, args...);
}

inline int tsprintf(char *buff, int remaining, const char* fmtStr) {
    BREAK_PT;
    int cnt = 0;
    while (fmtStr[cnt] != '\0')
    {
        if (cnt < remaining)
        {
            buff[cnt] = fmtStr[cnt];
        }
        cnt++;
    }
    buff[cnt++] = '\0';
    return cnt;
}

template<typename P1, typename... Params>
int tsprintf(char *buff, int remaining, const char* fmtStr, P1 pArg, Params... args) {
    int cnt = 0;
    while(remaining > 1 && *fmtStr != '\0')
    {
        if (*fmtStr == '{' && *(fmtStr + 1) == '}')
        {
            int c = toString(buff, remaining, pArg);
            buff = buff + c;
            fmtStr = fmtStr + 2;
            remaining -= c;
            cnt += c;
            return cnt + tsprintf(buff, remaining, fmtStr, args...);
        }

        *buff = *fmtStr;
        fmtStr++;
        remaining--;
        buff++;
    }

    *buff = 0;
    buff++;
    return cnt;
}



template<typename ... Params>
void printLvl(Lvl, const char * fmt, Params... args){
    char buff[1024];
    tsprintf(buff, sizeof(buff), fmt, args...);

    display::fbWriteString(buff);
}

}
}