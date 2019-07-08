#include <random>
#include <vector>
#include "ex5.cpp"

const int expr = 10;

bool NotNormal(std::vector<double> ran, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int s = ran[i] * ran[i] + ran[j] * ran[j];
            if (s > 1 || s == 0)
                return false;
        }
    }
    return true;
}

void generate(std::vector<double> ran, int N) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (int i = 0; i < N; i++) {
        float myrand = normal_distribution(generator);
        ran.push_back(myrand);
    }
}

int main() {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    std::vector<double> ran;

    for (int N = 2; N <= 10; N++) {
        for (int i = 0; i < expr; i++) {
            do {
                generate(ran, N);
            } while (NotNormal(ran, N));

            DSU dsu(N);
            std::deque < std::pair < double, std::pair < int, int > > > edges;
            for (int j = 0; j < N; j++) {
                for (int k = 1 + j; k < N; k++) {
                    int w = ran[i] * ran[i] + ran[j] * ran[j];
                    int v1 = j, v2 = k;
                    std::pair<int, int> edge(v1, v2);
                    edges.push_back(std::pair < double, std::pair < int, int > > (w, edge));
                }
            }
            std::deque<std::pair<std::pair<int, int> > ost_edges = dsu.Kruskal(edges);
            int opt = dsu.Optimal(ost_edges, ran);
            //int best = dsu.Best(ost_edges, ran);
            std::cout << "Optimal = " << opt << std::endl;
            //std::cout << "Best = " << best << std::endl;
            std::cout << "Deviation = " << (double)opt / best << std::endl;
            std::cout << std::endl;
        }
    }
}
