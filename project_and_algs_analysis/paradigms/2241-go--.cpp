#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    int blacks[n][n], whites[n][n], subblacks=0, subwhites=0;
    memset(blacks, 0, n * n * sizeof(int));
    memset(whites, 0, n * n * sizeof(int));

    for(int i = 0; i < p; i++){
        int l, c;
        scanf("%d %d", &l, &c);
        blacks[l-1][c-1] =  1;
        whites[l-1][c-1] = -1;
        subblacks++;
    }

    for(int i = 0; i < p; i++){
        int l, c;
        scanf("%d %d", &l, &c);
        blacks[l-1][c-1] = -1;
        whites[l-1][c-1] =  1;
        subwhites++;
    }

    for(int d = 2; d <= n; d++){
        for(int i = 0; i <= n-d; i++) {
            for(int j = 0; j<= n-d; j++) {
                int sum = blacks[i][j] + blacks[i+1][j] + blacks[i][j+1] +
                            blacks[i+1][j+1];

                if(blacks[i][j] != -1 && blacks[i+1][j] != -1 &&
                   blacks[i][j+1] != -1 && blacks[i+1][j+1] != -1 ) {
                   if (sum > 0) {
                     blacks[i][j] = 1;
                    subblacks++;
                   }
                } else {
                    blacks[i][j] = -1;
                }

                sum = whites[i][j] + whites[i+1][j] + whites[i][j+1] +
                            whites[i+1][j+1];

                if(whites[i][j] != -1 && whites[i+1][j] != -1 &&
                   whites[i][j+1] != -1 && whites[i+1][j+1] != -1 ) {
                   if (sum > 0) {
                     whites[i][j] = 1;
                    subwhites++;
                   }
                } else {
                    whites[i][j] = -1;
                }
            }
        }
    }

    printf("%d %d\n", subblacks, subwhites);

    return 0;
}
