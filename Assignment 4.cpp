#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct pair_value
{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Graph
{
public:
    unordered_map<string, list<pair<string, int>>> edges;
    unordered_map<pair<string, string>, int, pair_value> weights;

    void add_edge(string from_node, string to_node, int weight)
    {
        edges[from_node].push_back(make_pair(to_node, weight));
        edges[to_node].push_back(make_pair(from_node, weight));
        weights[make_pair(from_node, to_node)] = weight;
        weights[make_pair(to_node, from_node)] = weight;
    }
};

vector<string> dijkstra(Graph& graph, const string& initial, const string& end, int& total_cost)
{
    unordered_map<string, pair<string, int>> shortest_paths;
    shortest_paths[initial] = make_pair("", 0);
    auto cmp = [&shortest_paths](const string& a, const string& b)
    {
        return shortest_paths[a].second > shortest_paths[b].second;
    };
    priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
    pq.push(initial);
    unordered_set<string> visited;

    while (!pq.empty())
    {
        string current_node = pq.top();
        pq.pop();

        if (current_node == end) break;
        if (visited.count(current_node)) continue;
        visited.insert(current_node);

        for (auto it = graph.edges[current_node].begin(); it != graph.edges[current_node].end(); ++it)
        {
            string next_node = it->first;
            int weight = it->second;
            int new_weight = shortest_paths[current_node].second + weight;
            if (!shortest_paths.count(next_node) || new_weight < shortest_paths[next_node].second)
            {
                shortest_paths[next_node] = make_pair(current_node, new_weight);
                pq.push(next_node);
            }
        }
    }

    if (!shortest_paths.count(end)) return { "Route Not Possible" };

    vector<string> path;
    total_cost = shortest_paths[end].second;
    for (string at = end; !at.empty(); at = shortest_paths[at].first)
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    Graph graph;
    vector<tuple<string, string, int>> edges = {
        make_tuple("X", "A", 7), make_tuple("X", "B", 2), make_tuple("X", "C", 3), make_tuple("X", "E", 4),
        make_tuple("A", "B", 3), make_tuple("A", "D", 4), make_tuple("B", "D", 6), make_tuple("B", "H", 5),
        make_tuple("C", "L", 2), make_tuple("D", "F", 3), make_tuple("F", "H", 3), make_tuple("G", "H", 2),
        make_tuple("G", "Y", 2), make_tuple("I", "J", 6), make_tuple("I", "K", 4), make_tuple("I", "L", 4),
        make_tuple("J", "L", 1), make_tuple("K", "Y", 5)
    };

    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        string from_node = get<0>(*it);
        string to_node = get<1>(*it);
        int weight = get<2>(*it);
        graph.add_edge(from_node, to_node, weight);
    }

    int total_cost = 0;
    string start;
    string end;
    cout << "Input Starting Node: ";
    cin >> start;
    cout << "Input Destionation: ";
    cin >> end;
    vector<string> path = dijkstra(graph, start, end, total_cost);
    for (const string& node : path)
    {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total cost: " << total_cost << endl;

    return 0;
}