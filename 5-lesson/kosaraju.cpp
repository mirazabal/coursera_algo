/*
The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex). So for example, the 11th11^{th}11th row looks liks : "2 47646". This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646

Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.

Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, separated by commas (avoid any spaces). So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100" (without the quotes). If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0" (without the quotes). (Note also that your answer should not have any spaces in it.)

WARNING: This is the most challenging programming assignment of the course. Because of the size of the graph you may have to manage memory carefully. The best way to do this depends on your programming language and environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.

*/


////////////////////////////////////////////////   https://www.geeksforgeeks.org/strongly-connected-components/   /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C++ Implementation of Kosaraju's algorithm to print all SCCs

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

#include <iostream>
#include <list>
#include <stack>
using namespace std;

namespace GeeksForGeeks
{ 
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists
 
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing 
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);
 
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    void addEdge(int v, int w);
 
    // The main function that finds and prints strongly connected
    // components
    void printSCCs();
 
    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
 
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);
 
    // All vertices reachable from v are processed by now, push v 
    Stack.push(v);
}
 
// The main function that finds and prints all strongly connected 
// components
void Graph::printSCCs()
{
    stack<int> Stack;
 
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
 
    // Create a reversed graph
    Graph gr = getTranspose();
 
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();
 
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

/* 
// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
 
    cout << "Following are strongly connected components in "
            "given graph \n";
    g.printSCCs();
 
    return 0;
}
*/
} // end of namespace
////////////////////////////////////////////////   https://www.geeksforgeeks.org/strongly-connected-components/   /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace mirazabal
{
	class Graph{
	

		public:
			explicit Graph(uint64_t vertices) : vEdges_(vertices)
			{
							
			}	

			void add_edge(uint64_t src, uint64_t dest)
			{
				vEdges_[src].emplace_back(dest);
			}
	
			std::vector<std::vector<uint64_t>> vEdges_;
	};

	void DFS_first(uint64_t pos, Graph const &g, std::vector<bool>& visited, std::stack<uint64_t>& sta)
	{
		visited[pos] = true;
		for(auto dest : g.vEdges_[pos]){
			if(!visited[dest]){
				DFS_first(dest,g,visited,sta);
			}
		}	
		sta.push(pos);
	}

	std::stack<uint64_t> kosaraju_first(Graph const & g)
	{
		std::stack<uint64_t> sta;
		std::vector<bool> visited(g.vEdges_.size());
		std::fill(std::begin(visited), std::end(visited), false);
		for(int i = 0; i < g.vEdges_.size(); ++i){
			if(!visited[i] ) 
				DFS_first(i,g,visited,sta);
		}
		return sta;
	}

	uint64_t DFS_second(uint64_t pos, Graph const & g, std::vector<bool>& visited)
	{
			uint64_t retVal = 1;
			visited[pos] = true;
			for(auto dest: g.vEdges_[pos]){
				if(!visited[dest] ){
					retVal +=  DFS_second(dest,g,visited);
				}
			}
			return retVal;
	}

	std::vector<uint64_t> kosaraju_second(Graph const & g, std::stack<uint64_t>& sta)
	{
		std::vector<bool> visited(g.vEdges_.size());
		std::fill(std::begin(visited), std::end(visited), false);
		std::vector<uint64_t> retVec;
		while(!sta.empty()){
			auto v = sta.top();
			sta.pop();
			if(!visited[v]){
			 auto retVal = 	DFS_second(v,g,visited);
			 retVec.emplace_back(retVal);
			}
		}
		return retVec;
	}
} // end of namespace mirazabal

int main()
{
	constexpr uint64_t numberOfVertices {875714};
	mirazabal::Graph g1(numberOfVertices);
	mirazabal::Graph g2(numberOfVertices);
	std::ifstream file("SCC.txt");
	std::string str; 
	while (std::getline(file, str)){
		std::istringstream iss(str);
		uint64_t src, dest;
   	if (!(iss >> src >> dest)) { break; } // error	
		g1.add_edge(src-1,dest-1);	
		g2.add_edge(dest-1,src-1);	
	}

	std::stack<uint64_t> st = kosaraju_first(g1);
	std::cout << "stack size = " << st.size() << std::endl;
	auto retVec = kosaraju_second(g2,st);
	std::sort(std::begin(retVec), std::end(retVec), std::greater<uint64_t>());
	for(auto i = 0; i < 5; ++i)
		std::cout << retVec[i] << '\n';
	return 0;
}
