//ALGO2 IS1 222A LAB08
//Łukasz Kasztelan
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

struct Node {
    float x, y;
};

struct Edge {
    int first, second;
    double third;
};

struct Graph {
    vector<Node> nodes;
    vector<Edge> edges;
};

bool edgeCompare(Edge a, Edge b) {
    return a.third < b.third;
}

int counter_f = 0;

int find(int* parent, int x) {
    counter_f++;
    while (parent[x] != x) {
        x = parent[x];
        counter_f++;
    }
    return x;
}

int find_path(int* parent, int x) {
    counter_f++;
    if (parent[x] != x) {
        parent[x] = find_path(parent, parent[x]);
    }
    return parent[x];
}

void union_op(int* parent, int x, int y, int k) {
    int x_root, y_root;
    if (k == 1) {
        x_root = find(parent, x);
        y_root = find(parent, y);
    }
    else {
        x_root = find_path(parent, x);
        y_root = find_path(parent, y);
    }
    parent[x_root] = y_root;
}

void unionSets(int* parent, int* rank, int x, int y, int k) {
    int xRoot, yRoot;
    if (k == 1) {
        xRoot = find(parent, x);
        yRoot = find(parent, y);
    }
    else {
        xRoot = find_path(parent, x);
        yRoot = find_path(parent, y);
    }

    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    }
    else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    }
    else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

Graph read_data(const string& filename) {
    Graph g;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    int n, e;
    file >> n;
    g.nodes.resize(n);
    for (int i = 0; i < n; i++)
    {
        file >> g.nodes[i].x >> g.nodes[i].y;
    }
    file >> e;
    g.edges.resize(e);
    for (int i = 0; i < e; i++) {
        file >> g.edges[i].first >> g.edges[i].second >> g.edges[i].third;
    }
    file.close();
    return g;
}

Graph kruskal(Graph g, int k, int p) {
    Graph mst;
    int x, y;
    counter_f = 0;
    sort(g.edges.begin(), g.edges.end(), edgeCompare);
    double mst_weight = 0;
    int* parent = new int[g.nodes.size() + 1];
    int* rank = new int[g.nodes.size() + 1];
    for (int i = 0; i < g.nodes.size(); i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    auto t1 = chrono::system_clock::now();
    for (int i = 0; i < g.edges.size(); i++) {
        if (k == 1) {
            x = find(parent, g.edges[i].first);
            y = find(parent, g.edges[i].second);
        }
        else {
            x = find_path(parent, g.edges[i].first);
            y = find_path(parent, g.edges[i].second);
        }       
        if (x != y) {
            mst.nodes.push_back(g.nodes[g.edges[i].first]);
            mst.nodes.push_back(g.nodes[g.edges[i].second]);
            mst.edges.push_back(g.edges[i]);
            if (p == 1) {
                union_op(parent, x, y, k);
            }
            else {
                unionSets(parent, rank, x, y, k);
            }
            mst_weight += g.edges[i].third;
        }
    }
    auto t2 = chrono::system_clock::now();
    chrono::duration<double, milli> elapsed_time = t2 - t1;   
    //cout << "Edges in MST:" << endl;
    //for (const auto& edge : mst.edges)
    //    cout << edge.first << " - " << edge.second << " : " << edge.third << endl;
    cout << "Number of edges in MST: " << mst.edges.size() << endl;
    cout << "Count of find: " << counter_f << endl;
    cout << "Time: " << elapsed_time.count() << endl;
    cout << "Weight of MST: " << mst_weight << endl;
    delete[] parent;
    delete[] rank;
    return mst;
}

int main() {
    int menu;
    cout << "Wybierz plik: (1,2,3)" << endl;
    cin >> menu;
    Graph g, mst;
    switch (menu)
    {
    case 1:
        g = read_data("g1.txt");
        break;
    case 2:
        g = read_data("g2.txt");
        break;
    case 3:
        g = read_data("g3.txt");
        break;
    }
    /*int pick, pick1;
    cout << "Wariant find: (1. bez kompresji, 2. z kompresją) " << endl;
    cin >> pick;
    cout << "Wariant union f_bez: (1. bez, 2. z) " << endl;
    cin >> pick1;*/
    mst = kruskal(g, 1, 1);
    mst = kruskal(g, 1, 2);
    mst = kruskal(g, 2, 1);
    mst = kruskal(g, 2, 2);
    return 0;
}
