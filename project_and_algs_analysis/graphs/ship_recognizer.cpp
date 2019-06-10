// --- Includes
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

// --- Helpful defines
#define INF 0x3f3f3f3f
#define pb push_back
#define ll long long

using namespace std;

// --- Helpful types definitions
typedef vector<int> vi;
typedef vector<vi>  vvi;

// --- Ship structure definition
struct Ship {
    int paths  = 0;    // # of edges
    int leaves = 0;    // # of leaves ( 1 degree vertex )
    vector<int> stations; // combating stations
};

// --- Fleet construction
void make_graph(vvi &graph, int &edges) {
    while ( edges-- ) {
        int from, to;
        scanf("%d %d", &from, &to);

        from--; to--;

        graph[from].pb(to);
        graph[to].pb(from);
    }
}

// ---  Fleet Recognition
bool is_leaf(int &neighbors) {
    return neighbors == 1;
}

bool is_transporter(Ship &ship) {
    return ship.stations.size() == ship.paths;
}

bool is_bomber(Ship &ship) {
    return ship.stations.size() < ship.paths;
}

bool is_recognizer(Ship &ship) {
    return ship.leaves == 2;
}

void update_ship(Ship &ship, int &station, int &neighbors) {
     if (is_leaf(neighbors))
        ship.leaves++;

     ship.paths += neighbors;
     ship.stations.pb(station);
}

// --- --- Ship classification
void recognize_ship(Ship &ship, vector<Ship> &recognizers,
                    vector<Ship> &frigates, vector<Ship> &bombers,
                    vector<Ship> &transporters) {
    ship.paths /= 2;

    if (is_transporter(ship)) {
        transporters.pb(ship);
    } else if (is_bomber(ship)) {
        bombers.pb(ship);
    } else if (is_recognizer(ship)) {
        recognizers.pb(ship);
    } else {
        frigates.pb(ship);
    }
}

// --- --- (DFS) Connected component detection, inner loop
void analyze_station(vvi &graph, int station, vector<Ship> &recognizers,
                     vector<Ship> &frigates, vector<Ship> &bombers,
                     vector<Ship> &transporters, Ship &ship, int *partitions,
                     int *parents, int *depths) {
        int neighbors = graph[station].size();
        update_ship(ship, station, neighbors);

        for (int neighbor = 0; neighbor < neighbors; neighbor++) {
            int next = graph[station][neighbor];
            if (depths[next] == INF) {
                depths[next]     = depths[station] + 1;
                parents[next]    = station;
                partitions[next] = !partitions[station];

                analyze_station(graph, next, recognizers, frigates, bombers,
                            transporters, ship, partitions, parents, depths);
            }
        }
}

// --- --- (DFS) Connected component detection, main loop
void recognize_ships(vvi &graph, int verts,
                     vector<Ship> &recognizers, vector<Ship> &frigates,
                     vector<Ship> &bombers, vector<Ship> &transporters,
                     int *partitions, int *parents, int *depths) {
    int station;

    for (station = 0; station < verts; station++) {
        parents[station] = -1;
        depths[station]  = INF;
    }

    for (station = 0; station < verts; station++) {
        if (depths[station] == INF) {
            Ship ship;

            depths[station]     = 0;
            partitions[station] = 0;

            analyze_station(graph, station, recognizers, frigates, bombers,
                            transporters, ship, partitions, parents, depths);
            recognize_ship(ship, recognizers, frigates, bombers,
                            transporters);
        }
    }
}

// --- Advantage time calculation

// --- --- Store station changes
void store_changes(int *changes, int &verts) {
    for (int change = 0; change < verts; change++) {
        int from, to;
        scanf("%d %d", &from, &to);

        from--; to--;

        changes[from] = to;
    }
}

// --- --- Calculate recognizer advantage
ll recognizer_advantage(Ship &ship, int *changes) {
    ll distance = 0LL;
    int from, to;

    for (int change = 0; change < ship.stations.size(); change++) {
        from = ship.stations[change];
        to   = changes[from];

        distance += abs(from - to); // Trivial distance between neighbors
    }

    return distance;
}

// --- --- Calculate frigate advantage => LCA
// --- --- --- thanks to: http://www.codcad.com/lesson/52
ll frigate_advantage(Ship &ship, int *parents, int *depths, int *changes) {
    ll distance = 0LL;
    int from, to, copy_from, copy_to;

    for (int change = 0; change < ship.stations.size(); change++) {
        copy_from = from = ship.stations[change];
        copy_to   = to   = changes[from];

        while (copy_from != copy_to) {
            if (depths[copy_from] > depths[copy_to])
                copy_from = parents[copy_from];
            else
                copy_to = parents[copy_to];
        }

        distance += (ll) (depths[from] + depths[to] - 2 * depths[copy_from]);
    }

    return distance;
}

// --- --- Calculate bomber advantage
ll bomber_advantage(Ship &ship, int *partitions, int *changes) {
    ll distance = 0LL;
    int from, to;

    for (int change = 0; change < ship.stations.size(); change++) {
        from = ship.stations[change];
        to   = changes[from];

        if (from != to)
            distance += (partitions[from] == partitions[to]) ? 2 : 1;
    }

    return distance;
}

// --- --- Calculate transporter advantage
ll transporter_advantage(Ship &ship, int *changes) {
    ll distance = 0LL;
    int from, to, with_cycle, without_cycle, stations = ship.stations.size();

    for (int change = 0; change < stations; change++) {
        from = ship.stations[change];
        to   = changes[from];

        without_cycle = abs(from  - to);    // Travel as if it was a recognizer
        with_cycle    = abs(stations - to); // Use the cycle to cut some
                                            // distance
        distance += min(with_cycle, without_cycle);
    }

    return distance;
}

// --- --- Advantage calculation
ll their_advantage(vector<Ship> &recognizers,
                   vector<Ship> &frigates, vector<Ship> &bombers,
                   vector<Ship> &transporters, int *partitions, int *parents,
                   int *depths, int *changes) {
    ll distance, AD = INF;
    int ship;

    for(ship = 0; ship < recognizers.size(); ship++) {
        distance = recognizer_advantage(recognizers[ship], changes);
        AD = min(AD, distance);
    }

    for(ship = 0; ship < frigates.size(); ship++) {
        distance = frigate_advantage(frigates[ship], parents, depths, changes);
        AD = min(AD, distance);
    }

    for(ship = 0; ship < bombers.size(); ship++) {
        distance = bomber_advantage(bombers[ship], partitions, changes);
        AD = min(AD, distance);
    }

    for(ship = 0; ship < transporters.size(); ship++) {
        distance = transporter_advantage(transporters[ship], changes);
        AD = min(AD, distance);
    }

    return AD / 2;
}

// --- Knowledge sharing
void expose_fleet(vector<Ship> &recognizers, vector<Ship> &frigates,
                  vector<Ship> &bombers, vector<Ship> &transporters,
                  ll &AD) {
    printf("%d %d %d %d\n%lld\n", recognizers.size(), frigates.size(),
                                  bombers.size(), transporters.size(),
                                  AD);
}

// -- MAIN

int main() {
    int verts, edges;
    scanf("%d %d", &verts, &edges);

    // --- Fleet construction
    vvi graph(verts);
    make_graph(graph, edges);

    // ---  Fleet Recognition and preparation for advantage time calculation
    vector<Ship> recognizers, frigates, bombers, transporters;
    int partitions[verts], parents[verts], depths[verts];
    recognize_ships(graph, verts, recognizers, frigates, bombers, transporters,
                    partitions, parents, depths);

    // --- Advantage time calculation
    int changes[verts];
    store_changes(changes, verts);

    ll AD = their_advantage(recognizers, frigates, bombers, transporters,
                            partitions, parents, depths, changes);

    // --- Knowledge sharing
    expose_fleet(recognizers, frigates, bombers, transporters, AD);

    return 0;
}
