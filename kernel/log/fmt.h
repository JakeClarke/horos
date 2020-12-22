#pragma once

#include "../panic.h"

namespace horos {
class StringView {
    public:
    using CharType = const char;
    using CharPtrType = CharType*;
    using SizeType = int;
    constexpr StringView() = default;
    constexpr StringView(CharPtrType str) : _start(str), _len(str ? _strLen(str): 0)  {}
    constexpr StringView(CharPtrType start, CharPtrType end) : _start(start), _len(end-start){}
    constexpr StringView(CharPtrType start, SizeType n) : _start(start), _len(n) {}

    CharPtrType begin() const {
        return _start;
    }

    CharPtrType end() const {
        return _start + _len;
    }

    SizeType size() const {
        return _len;
    }

    SizeType length() const {
        return size();
    }

    private:
    static constexpr SizeType _strLen(const char * str) {
        return __builtin_strlen(str);
    }
    CharPtrType _start = 0;
    SizeType _len = 0;
};

namespace strconv{

int toString(char * buff, int remaining, StringView spec, StringView p);

int toString(char * buff, int remaining, StringView spec, unsigned int p);

int toString(char * buff, int remaining, StringView spec, int p);
}



int sfmt(char *buff, int remaining, StringView fmtStr);

template<typename P1, typename... Params>
int sfmt(char *buff, int remaining, StringView fmtStr, P1 pArg, Params... args) {
    BREAK_PT;
    int cnt = 0;
    auto curr = fmtStr.begin();
    while(remaining > 1 && curr != fmtStr.end())
    {
        if (*curr == '{')
        {
            // represents the start of the fmt spec ex: {#x} -> #
            curr++;
            // represents the closing brace of the fmt spec ex: {#x} -> }
            int len = 0;
            while (curr[len] != '}')
            {
                len++;
            }

            StringView fmtSpec(curr, len);

            int c = strconv::toString(buff, remaining, fmtSpec, pArg);
            buff = buff + c;
            fmtStr = StringView(fmtSpec.end() + 1, fmtStr.end());
            remaining -= c;
            cnt += c;
            return cnt + horos::sfmt(buff, remaining, fmtStr, args...);
        }

        *buff = *curr;
        curr++;
        remaining--;
        buff++;
    }

    *buff = 0;
    buff++;
    return cnt;
}

}
