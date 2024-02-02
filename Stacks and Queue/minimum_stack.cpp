#include <bits/stdc++.h>

using namespace std;

class MinimumStack{

    stack<pair<int, int>> st;

    public:
        void add(int new_elem){

            int new_min = st.empty() ? new_elem : min(new_elem, st.top().second);
            st.push({new_elem, new_min});
        }

       int remove(){
            int removed_element = st.top().first;
            st.pop();
            return removed_element;
        }

       int find(){
            int minimum = st.top().second;
            return minimum;
       }
};

int main(){

    MinimumStack MS = MinimumStack();

}