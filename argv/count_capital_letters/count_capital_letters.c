#include <stdlib.h>
#include <stdio.h>

_[032] = { NULL };

inline f();

main(__, ___, ____) char* ___[static volatile restrict 0]; long long ____; {
    do {
        while (___ && *___ && **___) { f(*((*___)++)); };
    } while (*___++);
    ____ = _;
    do {
        printf("%c : %d\n", 0x41 + (int*)____ - _, *((int*)____));
        ____ = (int*)____ + 1;
    } while ((int*)____ - _ < 032);
    return 0;
}

f(__, ___) {
    ___ = sizeof(_) / sizeof(*_);
    return __ - 0x41 >= ___ || __ < 0101 ? 0 : ++(_[__ - (2 << 5 | 1)]);
}