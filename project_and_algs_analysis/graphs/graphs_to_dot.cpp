#include <fstream>
#include <sstream>

void display_graphs(vvi &graphs, vector<Ship> &ships) {

    for (int ship = 0; ship < ships.size(); ship++) {
        ofstream f;
        stringstream str;
        str << "graphs/2in/ship_" << ship << ".graph";

        f.open(str.str());

        f << "strict graph ship_" << ship << " {" << endl;
        f << "    graph [ splines = false ]" << endl;

        for (int post = 0; post < ships[ship].stations.size(); post++) {
            int u = ships[ship].stations[post];
            f << "    " << u  << " -- { ";
            for (int n = 0; n < graphs[u].size();n++) {
                f << graphs[u][n] << " ";
            }
            f << "}" << endl;
        }
        f << "}" << endl;

        f.close();
    }
}
