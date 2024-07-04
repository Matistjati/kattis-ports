#include "validator.h"
#include <set>

void run() {
    int t = Int(1, int(1e5));
    Endl();
    int totn= 0;
    while (t--)
    {
        int n = Int(2, int(2e5));
        totn+=n;
        Endl();
        SpacedInts(n, 1, n);
    }
    assert(totn<=(int)Arg("maxn"));
    
    Eof();
}
