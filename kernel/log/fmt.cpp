#include "fmt.h"

using namespace horos;

int strconv::toString(char * buff, int remaining, StringView fmtSpec, StringView p) {
    int c = 0;
    for (auto curr : p)
    {
        if(c < remaining) {
            buff[c] = curr;
        }
        c++;
    }
    
    return c;
}

int strconv::toString(char * buff, int remaining, StringView fmtSpec, unsigned int p) {
    BREAK_PT;
    
    bool isHex = false;
    bool altForm = false;
    bool capsHex = false;
    for(auto flag: fmtSpec) {
        capsHex |= (flag == 'X');
        isHex |= (flag == 'x');
        isHex |= capsHex;
        altForm |= (flag == '#');
    }

    int prefix = 0;
    if (altForm)
    {
        prefix = toString(buff, remaining, nullptr, capsHex ? "0X": "0x");
        buff += prefix;
        remaining -= prefix;
    }
    
    const int base = isHex ? 16 : 10;
    const char hexBase = capsHex ? 'A': 'a';
    int c = 0;
    auto charHex = capsHex ? "0123456789ABCDEF" : 
            "0123456789abcdef";
    do
    {        
        int r = p % base;
        if (c < remaining) {
            buff[c] = charHex[r];
        }
        
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
    
    return c + prefix;
}

int strconv::toString(char * buff, int remaining, StringView fmtSpec, int p) {
    bool isHex = false;
    for (auto c : fmtSpec) {
        isHex |= (c == 'x');
        isHex |= (c == 'X');
    }
       
    int negative = 0;
    if (!isHex && p < 0)
    {
        *buff = '-';
        buff++;
        p = -p;
        remaining--;
        negative = 1;
    }

    return toString(buff, remaining, fmtSpec, *reinterpret_cast<unsigned int*>(&p)) +  negative;
}

int ::horos::sfmt(char *buff, int remaining, StringView fmtStr) {
    int cnt = 0;
    for (auto curr : fmtStr) {
        if (cnt < remaining)
        {
            buff[cnt] = curr;
        }
        cnt++;
    }
    buff[cnt++] = '\0';
    return cnt;
}
