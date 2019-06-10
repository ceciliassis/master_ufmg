#include <iostream>
#include <vector>
#include <cstdio>

// Mochila com repetição

using namespace std;

struct Toy {
    int grade;
    int duration;
};

int sixflags(vector<Toy> &toys, int N, int T) {
    int M[N+1][T+1]; // Add linha 0 e coluna 0

    for(int toy = 0; toy <= N; toy++) { // Até N
       for(int duration = 0; duration <= T; duration++) { // Até T
            Toy t = toys[toy - 1];
            if(toy == 0 || duration == 0) {
                M[toy][duration] = 0;
            }else if (duration < t.duration) {
                M[toy][duration] = M[toy - 1][duration];
            } else {
                M[toy][duration] = max(M[toy][duration - t.duration] + t.grade,
                                   M[toy - 1][duration]);
            }
        }
    }

    return M[N][T]; // Pode usar todos os itens até a "capacidade" maxima
}

int main()
{
    int N = 1, T;
    int i = 1;
    while(scanf("%d %d", &N, &T) == 2 && N != 0) {
        printf("Instancia %d\n", i++);
        vector<Toy> toys(N);

        for(int g = 0; g < N; g++) {
            Toy toy;
            scanf("%d %d", &toy.duration, &toy.grade);
            toys[g] = toy;
        }

        printf("%d\n\n", sixflags(toys, N, T));
    }

    return 0;
}
