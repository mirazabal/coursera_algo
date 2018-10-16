/*

In this programming problem you'll code up the dynamic programming algorithm for computing a maximum-weight independent set of a path graph.

Download the text file below.
mwis.txt

This file describes the weights of the vertices in a path graph (with the weights listed in the order in which vertices appear in the path). It has the following format:

[number_of_vertices]

[weight of first vertex]

[weight of second vertex]

...

For example, the third line of the file is "6395702," indicating that the weight of the second vertex of the graph is 6395702.

Your task in this problem is to run the dynamic programming algorithm (and the reconstruction procedure) from lecture on this data set. The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997, which ones belong to the maximum-weight independent set? (By "vertex 1" we mean the first vertex of the graph---there is no vertex 0.) In the box below, enter a 8-bit string, where the ith bit should be 1 if the ith of these 8 vertices is in the maximum-weight independent set, and 0 otherwise. For example, if you think that the vertices 1, 4, 17, and 517 are in the maximum-weight independent set and the other four vertices are not, then you should enter the string 10011010 in the box below.

*/
#include <cstddef>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace mirazabal
{

template<typename T>
std::optional<T> getLine(std::ifstream& ifs)
{
  std::string str;
  if(!std::getline(ifs,str))
    return std::nullopt;
  T val;
  std::istringstream iss(str);
  iss >> val;
  return val; 
}

template<typename T>
std::vector<T> fillGraph(const char* filePath)
{
  std::ifstream ifstr(filePath);  	
  std::vector<T> graph;
  auto res = getLine<uint64_t>(ifstr);
  if(!res.has_value())
    return graph;

  graph.reserve(res.value());
  while(true){
    res = getLine<uint64_t>(ifstr);
    if(!res.has_value()) break;

    graph.emplace_back(res.value());
  }
  return graph;
}

  std::vector<uint64_t> createMWISArray(std::vector<uint64_t> const& vec)
  {
    std::vector<uint64_t> memoizationVec;
    memoizationVec.emplace_back(0);
    memoizationVec.emplace_back(vec[0]);
    for(uint64_t i = 2; i < vec.size(); ++i){
      memoizationVec.emplace_back(std::max(memoizationVec[i-1],memoizationVec[i-2] + vec[i-1]   )   );
    }
    std::cout << memoizationVec[2] << '\n';
  return memoizationVec;
  } 

  std::vector<uint64_t> reconstructionMWIS(std::vector<uint64_t> const& memoizationVec, std::vector<uint64_t> const& graph)
  {
    std::vector<uint64_t> reconstructionVec;
    size_t i = memoizationVec.size();
    while(i >= 2){
      if(memoizationVec[i-1] >= memoizationVec[i-2] + graph[i-1])
        --i;
      else{
        reconstructionVec.emplace_back(i);
        i = i -2;
      }
    }
    if(i == 1)
        reconstructionVec.emplace_back(i);
    return reconstructionVec;
  }

}; // end namespace mirazabal


int main()
{
  auto graph = mirazabal::fillGraph<uint64_t>("mwis.txt");
  auto memoizationVec = mirazabal::createMWISArray(graph);
  auto reconstructionVec = mirazabal::reconstructionMWIS(memoizationVec,graph);
  for(auto i : reconstructionVec)
    std::cout << i << '\n'; 
  return 0;
}
