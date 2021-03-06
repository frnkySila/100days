#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>

int main()
{
    struct Graph
    {
    private:
        int num_nodes;

        std::vector<std::unordered_set<int>> adj_lists;

    public:
        Graph(int n) : num_nodes(n), adj_lists(n) { }

        void add_edge(int u, int v)
        {
            adj_lists[u].insert(v);
            adj_lists[v].insert(u);
        }

        /**
         * Puts one node in between two other previously adjacent nodes, making both of them adjacent to the node, but
         * not to each other
         * @param rock A node adjacent to @param hard_place
         * @param u The node to be but in between two other odes
         * @param hard_place A node adjacent to @param rock
         */
        void put_in_between(int rock, int u, int hard_place)
        {
            /**
             * Disconnect the two nodes
             */
            adj_lists[rock].erase(hard_place);
            adj_lists[hard_place].erase(rock);

            /**
             * Connect the new node to the old two
             */
            add_edge(rock, u);
            add_edge(u, hard_place);
        }

        /**
         * @return Vector of all the edges in the graph (as pairs of adjacent nodes), each edge mentioned only once
         */
        std::vector<std::pair<int, int>> get_edges()
        {
            std::vector<std::pair<int, int>> edges;

            for(int u = 0; u < num_nodes; u++) {
                for(int v : adj_lists[u]) {
                    if(u < v) {
                        edges.push_back(std::make_pair(u, v));
                    }
                }
            }

            return edges;
        }
    };

    int n, k;

    std::cin >> n >> k;

    Graph g(n);

    std::deque<int> free_nodes;

    for(int i = 1; i < n; i++) {
        free_nodes.push_back(i);
    }

    /**
     * Select one node as the root of the tree
     */
    int root_node = 0;

    /**
     * Select `k` nodes as leaves
     */
    std::vector<int> branch_ends;

    for(int i = 0; i < k; i++) {
        int free_node = free_nodes.front();

        branch_ends.push_back(free_node);

        free_nodes.pop_front();
    }

    /**
     * Connect leaf nodes to the root
     */
    for(int leaf : branch_ends) {
        g.add_edge(root_node, leaf);
    }

    /**
     * Extend the branch between each leaf and the root in turn until there are no free nodes left, resulting in the
     * difference between the shortest and the longest branch being less than or equal to one
     */
    for(size_t i = 0; !free_nodes.empty(); i = (i + 1) % branch_ends.size()) {
        int free_node = free_nodes.front();

        g.put_in_between(root_node, free_node, branch_ends[i]);

        branch_ends[i] = free_node;

        free_nodes.pop_front();
    }

    /**
     * Print the maximum distance between leaves in the resulting tree, which is double the length of the longest branch
     * — 2 * ceil((n - 1) / k), subtract one if there's only one longest branch — (n - 1) % k == 1
     */
    std::cout << 2 * ((n - 1) / k + ((n - 1) % k != 0)) - ((n - 1) % k == 1) << std::endl;

    /**
     * Print the edges of the resulting graph
     */
    for(std::pair<int, int> edge : g.get_edges()) {
        std::cout << edge.first + 1 << " " << edge.second + 1 << std::endl;
    }
}
