#include <bits/stdc++.h>

using namespace std;

class MinimumQueue{

    stack<pair<int, int>> s1, s2;

    public:
        void add(int new_elem){

            int minimum = s1.empty() ? new_elem : min(new_elem, s1.top().second);
            s1.push({new_elem, minimum});
        }

       int remove(){
            if (s2.empty()) {
                while (!s1.empty()) {
                    int element = s1.top().first;
                    s1.pop();
                    int minimum = s2.empty() ? element : min(element, s2.top().second);
                    s2.push({element, minimum});
                }
            }
            int remove_element = s2.top().first;
            s2.pop();
            return remove_element;
        }

       int find(){
            int minimum;
            if (s1.empty() || s2.empty()) 
                minimum = s1.empty() ? s2.top().second : s1.top().second;
            else
                minimum = min(s1.top().second, s2.top().second);
            return minimum;
       }
};

int main(){

    MinimumQueue MQ = MinimumQueue();

}