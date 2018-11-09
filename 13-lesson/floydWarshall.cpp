/*
 *
In this assignment you will implement one or more algorithms for the all-pairs shortest-path problem. Here are data files describing three graphs:

g1.txt
g2.txt
g3.txt

The first line indicates the number of vertices and edges, respectively. Each subsequent line describes an edge (the first two numbers are its tail and head, respectively) and its length (the third number). NOTE: some of the edge lengths are negative. NOTE: These graphs may or may not have negative-cost cycles.

Your task is to compute the "shortest shortest path". Precisely, you must first identify which, if any, of the three graphs have no negative cycles. For each such graph, you should compute all-pairs shortest paths and remember the smallest one (i.e., compute min⁡u,v∈Vd(u,v)\min_{u,v \in V} d(u,v)minu,v∈V​d(u,v), where d(u,v)d(u,v)d(u,v) denotes the shortest-path distance from uuu to vvv).

If each of the three graphs has a negative-cost cycle, then enter "NULL" in the box below. If exactly one graph has no negative-cost cycles, then enter the length of its shortest shortest path in the box below. If two or more of the graphs have no negative-cost cycles, then enter the smallest of the lengths of their shortest shortest paths in the box below.

OPTIONAL: You can use whatever algorithm you like to solve this question. If you have extra time, try comparing the performance of different all-pairs shortest-path algorithms!

OPTIONAL: Here is a bigger data set to play with.
large.txt

For fun, try computing the shortest shortest path of the graph in the file above.
 *
 */

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream> 
#include <string>
#include <vector>

namespace mirazabal
{

  using matrix = std::vector<std::vector<int64_t>>;
  static constexpr int64_t identityMin = std::numeric_limits<int64_t>::max();

  matrix getGraphFromFile(const char* filePath)
  {
    std::ifstream ifstr(filePath);
    std::string str;
    std::getline(ifstr,str);
    std::istringstream iss(str);
    int64_t vertices, edges;
    iss >> vertices >> edges;  
    
    matrix graph(vertices,std::vector<int64_t>(vertices, identityMin));
 
    while(std::getline(ifstr, str)){
      std::istringstream iss(str);
     int64_t tail, head, lenght;
     iss >> tail >> head >> lenght;  
     graph[tail-1][head-1] = lenght;
    }
    for(auto i = 0; i < vertices; ++i)
      graph[i][i] = 0;
    return graph;
  }

  
  matrix floydWarshall(matrix const& mat)
  {
    matrix dist{mat};
    uint64_t matSize = dist.size();
    for(uint64_t k = 0; k < matSize; ++k){
      for(uint64_t i = 0; i < matSize; ++i){
        for(uint64_t j = 0; j < matSize; ++j){
          if(dist[i][k] == identityMin || dist[k][j] == identityMin)
            continue; 
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    return dist; 
  } 

  void printMinVal(matrix const& mat)
  {
    for(auto i = 0; i < mat.size(); ++i){
      if(mat[i][i] < 0){
        std::cout << "Negative cycle in graph " << '\n';
        return; 
      }
    }

    int64_t minVal = mirazabal::identityMin;
     for(auto const& v1 : mat){
      for(auto val : v1){
        if(val < minVal) minVal = val; 
      }
    }
    std::cout << "g = " <<  minVal << '\n';
  }

} // end namespace mirazabal

int main()
{
  auto graph1 = mirazabal::getGraphFromFile("g1.txt");
  auto mat1 = mirazabal::floydWarshall(graph1);
  mirazabal::printMinVal(mat1);

  auto graph2 = mirazabal::getGraphFromFile("g2.txt");
  auto mat2 = mirazabal::floydWarshall(graph2);
  mirazabal::printMinVal(mat2);
  
  auto graph3 = mirazabal::getGraphFromFile("g3.txt");
  auto mat3 = mirazabal::floydWarshall(graph3);
  mirazabal::printMinVal(mat3);

  return 0;
}
