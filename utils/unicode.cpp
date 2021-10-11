#include <vector>
#include "unicode.h"

const wchar_t CONTROL_BIT = 0x80;


std::wstring convert_from_utf8(const std::wstring& raw) {
    std::vector<wchar_t> vec;
    vec.reserve(raw.size());
    std::vector<bool> bin;
    int count;
    for (wchar_t c : raw) {
        if (0 == (c & CONTROL_BIT)) {
            vec.push_back(c);
            continue;
        }
        if (0 == count) {
            for (count = 0; count < 7;++count) {
                if (0 == (c & (CONTROL_BIT >> (count + 1)))) {
                    bin.clear();
                    for(int i = 5 - count;i >= 0;--i) {
                        bin.push_back(0 != (c & (1 << i)));
                    }
                    break;
                }
            }
            continue;
        }
        for(int i = 5;i >= 0;--i) {
            bin.push_back(0 !=  (c & (1 << i)));
        }
        --count;
        if (0 == count) {
            wchar_t new_c = 0;
            for (bool b : bin) {
                new_c = new_c << 1;
                new_c += b ? 1 : 0;
            }
            vec.push_back(new_c);
        }
    }
    return std::move(std::wstring(vec.data(), vec.size()));
}
