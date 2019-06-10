#include <bits/stdc++.h>

#define MAXN 1010
#define C first
#define L second

using namespace std;

typedef pair<int,int> ii;

int rooms[MAXN], ncols, nrows, houseplanthist[MAXN][MAXN], ntables;

int calculate_rooms(int hist[]) {
    stack<int> s;
    int length, l, c;
    for (length = 0; length < ncols; ) {
        if (s.empty() || hist[length] >= hist[s.top()]) {
            s.push(length++);
        } else {
            c = hist[s.top()]; s.pop();
            l = length;

            if(!s.empty()){
                l = l - s.top() - 1;
            }

            if (l > rooms[c]) {
                rooms[c] = l;
            }
        }
    }

    while(!s.empty()) {
        c = hist[s.top()]; s.pop();
        l = length;

        if(!s.empty()){
            l = l - s.top() - 1;
        }

        if (l > rooms[c]) {
            rooms[c] = l;
        }
    }
}

void houseplant() {
    for (int i = 0; i < nrows; i++) {
        calculate_rooms(houseplanthist[i]);
    }

    scanf("%d", &ntables);

    int l, c, tbarea, area;
    ii biggest = ii(0,0);
    for(int i = 0; i < ntables; i++) {
        scanf("%d %d", &c, &l);

        tbarea = l * c;

        if (rooms[c] * c >= tbarea || rooms[l] * l >= tbarea) {
            if ((tbarea > biggest.C * biggest.L) ||
                (tbarea ==  biggest.C * biggest.L && l > biggest.L)) {
                biggest = ii(c,l);
            }
        }
    }

   printf("%d %d", biggest.C, biggest.L);
}

int main()
{
    scanf("%d %d\n", &nrows, &ncols);

    char pos;
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            scanf("%c", &pos);
            while(pos != '.' && pos != '#'){
                scanf("%c", &pos);
            }

            if (i == 0) {
                if(pos == '.') {
                    houseplanthist[i][j] = 1;
                } else {
                    houseplanthist[i][j] = 0;
                }
            } else {
                if(pos == '.') {
                    houseplanthist[i][j] = houseplanthist[i-1][j] + 1;
                }
            }

        }
    }

    houseplant();
    printf("\n");

    return 0;
}