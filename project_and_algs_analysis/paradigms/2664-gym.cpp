#include <iostream>
#include <cstdio>

#define ll long long
#define mod 1000000007ll

using namespace std;

ll normalize (ll value) {
    if(value < mod) return value;
    return value % mod;
}

ll gym (int minutes, int minimum, int maximum) {
    int tam = maximum - minimum + 1, i = 0, j = 0;
    ll progs[tam][2], sum = 0;
    bool op = true;

    for(i = 0; i < tam; i++){
        for(j = 0; j < 2; j++){
            progs[i][j] = 1ll; // beginning cost
        }
    }

    for(j = 0; j < minutes; j++) {
        for(i = 0; i < tam; i++){
            if(i - 1 < 0) {           // base case 1
                progs[i][op] = normalize(progs[i+1][!op]);
            } else if(i + 1 == tam) { // base case 2
                progs[i][op] = normalize(progs[i-1][!op]);
            } else {
                progs[i][op] = normalize(progs[i-1][!op] + progs[i+1][!op]);
            }
        }
        op = !op; // flip the operation
    }

    for(i = 0; i < tam; i++){
        sum += progs[i][op]; // seen all changes
    }

    return normalize(sum);
}

int main()
{
    int minutes, minimum, maximum;
    scanf("%d %d %d", &minutes, &minimum, &maximum);
    printf("%lld\n", gym(minutes, minimum, maximum));
    int s = 0;
    return 0;
}
