class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<pair<int, int>>> adjList; //adjList: every node has a vector of pairs<neighbour, weight to neighbour>
        vector<int> visited(n, INT_MAX); //if node has been visited and smaller distance is found, new distance will be updated
        visited[src] = 0;

        for(vector<int> flight : flights){
            adjList[flight[0]].push_back({flight[1], flight[2]}); //flights is of form vector<fromNode, toNode, weight>
        }
        queue<pair<int, int>> BFSqueue; //BFS used because only going k nodes from src
        BFSqueue.push({src, 0});
        k++;
        while(k--){ //runs k times
            int size = BFSqueue.size();
            while(size--){
                int currentPrice = BFSqueue.front().second; //cost of reaching current node
                for(pair<int, int> adj : adjList[BFSqueue.front().first]){ //if cost of reaching neighbour through current node is cheaper, update
                    int newPrice = adj.second + currentPrice;
                    if(newPrice < visited[adj.first]){
                        visited[adj.first] = newPrice;
                        BFSqueue.push({adj.first, newPrice}); //push neighbour of current node with updated cost onto queue
                    }
                }
                BFSqueue.pop();
            }
        }
        return (visited[dst] == INT_MAX) ? -1 : visited[dst];
    }
};
