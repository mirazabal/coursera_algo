

/*
In this programming problem and the next you'll code up filePath clustering algorithm from lecture for computing a max-spacing kkk-clustering.

Download the text file below.
clustering1.txt

This file describes a distance function (equivalently, a complete graph with edge costs). It has the following format:

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...

There is one edge (i,j)(i,j)(i,j) for each choice of 1≤i<j≤n1 \leq i \lt j \leq n1≤i<j≤n, where nnn is the number of nodes.

For example, the third line of the file is "1 3 5250", indicating that the distance between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250. You can assume that distances are positive, but you should NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on this data set, where the target number kkk of clusters is set to 4. What is the maximum spacing of a 4-clustering?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!
*/

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

struct Edge
{
  uint64_t src_;
  uint64_t dst_;
  uint64_t weight_;
  Edge(uint64_t src, uint64_t dst, uint64_t weight) : src_{src}, dst_{dst}, weight_{weight}
  {

  }
};

class Graph
{
  uint64_t numberVertex_;
  std::vector<uint64_t> vHeads_;

  public:
  explicit Graph(uint64_t numVertex) : numberVertex_{numVertex}, vHeads_(numVertex)
  {
    std::iota(std::begin(vHeads_), std::end(vHeads_), 0);
  }

  void add_edge(uint64_t src, uint64_t dst, uint64_t weight)
  {
    vEdges_.emplace_back(Edge(src,dst,weight));
  }

  uint64_t getNumVertex() const
  {
    return numberVertex_;
  }

  uint64_t getHead(uint64_t num)
  {
    while(vHeads_[num] != num ){
      num = vHeads_[num];
    }
    return num;
  }

  void setHead(uint64_t h1, uint64_t h2)
  {
     vHeads_[h1] = h2;
  }

  std::vector<Edge> vEdges_;
};

Graph fillGraph(std::string const& filePath)
{
  std::ifstream file(filePath);
  std::string str; 
  std::getline(file, str);
  std::istringstream issVert(str);
  uint64_t numVertex;
  issVert >> numVertex; 
  Graph g(numVertex);
  
  while (std::getline(file, str)){
    std::istringstream iss(str);
    uint64_t src, dest , weight;
    if (!(iss >> src >> dest >> weight)) { break; } // error	
    g.add_edge(src-1,dest-1,weight);	
  }
  return g;
}
uint64_t kruskalMST(Graph& g, uint64_t stopCluster)
{
  std::sort(std::begin(g.vEdges_),std::end(g.vEdges_), [](Edge const& e1, Edge const& e2) { return e1.weight_ < e2.weight_; }  );
  
  uint64_t numberClusters = g.getNumVertex();
  for(auto const& e : g.vEdges_){
    auto h1 = g.getHead(e.src_);
    auto h2 = g.getHead(e.dst_);
    if(h1 != h2){
      if(numberClusters == stopCluster)
        return e.weight_;
      
      g.setHead(h1,h2);
      --numberClusters; 
    }
  }
}


int main()
{
  auto g = fillGraph("clustering1.txt");
  std::cout << kruskalMST(g,4) << '\n';
  return 0;
}

