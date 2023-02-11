#define lol 2
#define kek 6
#define cheburek lol + kek

#if lol == kek
    #define ohh "ohh"
#else
    #define ohmy "oh, my"
#endif

#undef kek
#undef lol

#ifndef kek
    #define kek 123
#endif