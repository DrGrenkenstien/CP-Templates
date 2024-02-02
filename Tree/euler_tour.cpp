#include <bits/stdc++.h>

using namespace std;

class EluerTour{

    vector<int> start, end, euler_tour, property;
    vector<vector<int> > tree;
    int timer = 0;

    public:

        EluerTour(vector<vector<int> > &tree, int n){

            this->tree = tree;
            start.resize(n + 1);
            end.resize(n + 1);
            property.resize(n + 1);
            euler_tour.resize(n + 1);
        }

        void Euler_tour(int at = 0, int prev = -1) {
            start[at] = timer;
            euler_tour[timer++] = at;
            for (int n : tree[at]) {
                if (n != prev) { Euler_tour(n, at); }
            }
            end[at] = timer;
        }

        vector<int> getStart(){
            return start;
        }

        vector<int> getEnd(){
            return end;
        }

        vector<int> getEulerTour(){
            return euler_tour;
        }

};

int main(){

    int n;
    cin>>n;

    vector<vector<int> > graph(n + 1);

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin>>u>>v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    EluerTour ET = EluerTour(graph, n);
    ET.Euler_tour(2);
    
    auto euler = ET.getEulerTour();

    for(auto e : euler)cout<<e<<" ";

}