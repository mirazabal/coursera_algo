/*
In this programming problem you'll code up Prim's minimum spanning tree algorithm.

Download the text file below.

edges.txt

This file describes an undirected graph with integer edge costs. It has the format

[number_of_nodes] [number_of_edges]

[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]

...

For example, the third line of the file is "2 3 -8874", indicating that there is an edge connecting vertex #2 and vertex #3 that has cost -8874.

You should NOT assume that edge costs are positive, nor should you assume that they are distinct.

Your task is to run Prim's minimum spanning tree algorithm on this graph. You should report the overall cost of a minimum spanning tree --- an integer, which may or may not be negative --- in the box below.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation of Prim's algorithm should work fine. OPTIONAL: For those of you seeking an additional challenge, try implementing a heap-based version. The simpler approach, which should already give you a healthy speed-up, is to maintain relevant edges in a heap (with keys = edge costs). The superior approach stores the unprocessed vertices in the heap, as described in lecture. Note this requires a heap that supports deletions, and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap
*/
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mirazabal
{

template<typename T>
std::vector<std::vector<T>> createGraph(std::string const & filePath) 
{
  std::ifstream file(filePath);
  std::string str;
  std::getline(file,str);
  T nVertex, nEdges;
  std::istringstream iss(str);
  iss >> nVertex >> nEdges; 
  std::vector<std::vector<T>> vec;
  for(uint64_t i = 0; i < nVertex; ++i){
    vec.emplace_back(std::vector<T>());
    for(uint64_t j = 0; j < nVertex; ++j){
      vec[i].emplace_back(std::numeric_limits<T>::max());
    }
  }

  while(std::getline(file,str)){
    std::istringstream iss2(str);
    T vertex1, vertex2, value;
    iss2 >> vertex1 >> vertex2 >> value;
    vec[vertex1-1][vertex2-1]=value;
    vec[vertex2-1][vertex1-1]=value;
  }
  return vec;
}

template<typename T>
std::pair<T,T> getMinNodeEdge(std::vector<std::vector<T>> const& graph, std::vector<bool> const& nodesAnalized)
{
  T node,edge;
  edge = std::numeric_limits<T>::max();
  for(int i = 0; i < nodesAnalized.size(); ++i){
    if(nodesAnalized[i]){
      for(int j = 0; j < graph[i].size(); ++j){
       if(graph[i][j] < edge && !nodesAnalized[j]){
        edge = graph[i][j];
        node = j;
       }
      }
    }
  }
  assert(edge != std::numeric_limits<T>::min());
  return {node,edge};
}

template<typename T>
void primMST(std::vector<std::vector<T>> const& graph)
{
  std::vector<bool> nodesAnalized(graph.size());
  std::fill(std::begin(nodesAnalized), std::end(nodesAnalized),false);
  nodesAnalized[0] = true;
  int64_t totalValue = {0};
  for(int i = 0; i < graph.size() -1; ++i){
    auto p = getMinNodeEdge<T>(graph, nodesAnalized);
    nodesAnalized[p.first] = true;
    totalValue += p.second;
  }
  std::cout << totalValue << '\n';
}


} // end namespace mirazabal

int main()
{
  auto graph = mirazabal::createGraph<int64_t>("edges.txt");
  mirazabal::primMST<int64_t>(graph);
  return 0;
}
