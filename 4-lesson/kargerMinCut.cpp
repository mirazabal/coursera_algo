#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <random>
#include <unordered_map>
#include <vector>

//////////////////////////// https://www.geeksforgeeks.org/kargers-algorithm-for-minimum-cut-set-1-introduction-and-implementation//////////////////////////////////////////////
//
//


// a structure to represent a unweighted edge in graph
struct Edge_geeks
{
    int src, dest;
};
 
// a structure to represent a connected, undirected
// and unweighted graph as a collection of edges.
struct Graph_geeks
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge_geeks* edge;
};
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
 
// Function prototypes for union-find (These functions are defined
// after kargerMinCut() )
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
 
// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always
int kargerMinCut(struct Graph_geeks* graph)
{
    // Get data of given graph
    int V = graph->V, E = graph->E;
    Edge_geeks *edge = graph->edge;
 
    // Allocate memory for creating V subsets.
    struct subset *subsets = new subset[V];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Initially there are V vertices in
    // contracted graph
    int vertices = V;
 
    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices > 2)
    {
       // Pick a random edge
       int i = rand() % E;
 
       // Find vertices (or sets) of two corners
       // of current edge
       int subset1 = find(subsets, edge[i].src);
       int subset2 = find(subsets, edge[i].dest);
 
       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
         continue;
 
       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
          printf("Contracting edge %d-%d\n",
                 edge[i].src, edge[i].dest);
          vertices--;
          Union(subsets, subset1, subset2);
       }
    }
 
    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2)
          cutedges++;
    }
 
    return cutedges;
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent =
             find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Creates a graph with V vertices and E edges
struct Graph_geeks* createGraph(int V, int E)
{
    Graph_geeks* graph = new Graph_geeks;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge_geeks[E];
    return graph;
}

/*
// Driver program to test above functions
int main()
{
    // Let us create following unweighted graph
    //    0------1
    //    | \    |
    //    |   \  |
    //    |     \|
    //    2------3   
    int V = 4;  // Number of vertices in graph
    int E = 5;  // Number of edges in graph
    struct Graph_geeks* graph = createGraph(V, E);
 
    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
 
    // add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
 
    // add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
 
    // add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
 
    // add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
 
    // Use a different seed value for every run.
    srand(time(NULL));
 
    printf("\nCut found by Karger's randomized algo is %d\n",
           kargerMinCut(graph));
 
    return 0;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
std::vector<uint64_t> separateString(std::string const & sentence)
{
	std::istringstream iss(sentence);
	std::vector<uint64_t> tokens;
	std::copy(std::istream_iterator<uint64_t>(iss), std::istream_iterator<uint64_t>(),std::back_inserter( tokens ));
	return tokens;
}

class UndirectedGraph
{
	struct Edge
	{
		uint64_t src_;
		uint64_t des_;
		Edge(uint64_t src, uint64_t des) : src_{src}, des_{des}
		{
		
		}
	};

	std::vector<uint64_t> subsetVertex_;
	uint64_t numberOfSubsets_;

	public:
	std::vector<Edge> vEdges_;
	
	explicit UndirectedGraph ( uint64_t numberOfVertex) : numberOfSubsets_{numberOfVertex}, subsetVertex_(numberOfVertex)
 	{
		std::iota(std::begin(subsetVertex_), std::end(subsetVertex_), 0);
	};

	void add_edge(Edge const& e)
 	{
		vEdges_.emplace_back(e);
	}

	uint64_t find_parent(uint64_t vertexPos)
	{
		while( subsetVertex_[vertexPos] != vertexPos)	vertexPos =  subsetVertex_[vertexPos]; 
		return vertexPos;
	}

	void union_edge(uint64_t edgePos)
	{
		auto parent_1 = find_parent( vEdges_[edgePos].src_);
		auto parent_2 = find_parent( vEdges_[edgePos].des_);
		if(parent_1 == parent_2) return; // same vertex

		subsetVertex_[parent_2] = subsetVertex_[parent_1];
		--numberOfSubsets_;	
	}

	uint64_t get_number_subsets() const
	{
		return numberOfSubsets_;
	}
};
 
int main()
{
	constexpr uint64_t numberTries{100};
	uint64_t minCuts = std::numeric_limits<uint64_t>::max();
	for(auto i = 0; i < numberTries; ++i){
		constexpr auto numberVertex{200};
		UndirectedGraph uG(numberVertex);
		std::ifstream file("kargerMinCut.txt");
		std::string str; 
		while (std::getline(file, str)){
			auto vec = separateString(str);
			auto first = std::begin(vec);
			for(auto it = std::begin(vec)+1; it != std::end(vec); ++it ){
					if(*it > *first) // only add one since undirectional graph
							uG.add_edge({*first-1 ,*it-1 }); 
			}
		}

		while(uG.get_number_subsets() > 2 ){
						std::mt19937 rng;
						rng.seed(std::random_device()());
						std::uniform_int_distribution<std::mt19937::result_type> dist(0,uG.vEdges_.size()-1); // distribution in range [1, 6]
						auto edgeNumber = dist(rng);			
						uG.union_edge(edgeNumber);	
		}

		uint64_t numberCuts{0};
		for(auto const & e : uG.vEdges_)
		{
				auto parent_1 = uG.find_parent(e.src_);
				auto parent_2 = uG.find_parent(e.des_);
				if(parent_1 != parent_2) ++numberCuts;
		}
		if(minCuts > numberCuts) minCuts = numberCuts;
	}

	std::cout << "Min number of cuts = " << minCuts << '\n';  
	
	return 0;
};
