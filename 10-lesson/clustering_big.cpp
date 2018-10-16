/*
In this question your task is again to run the clustering algorithm from lecture, but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) are only defined implicitly, rather than being provided as an explicit list.

The data set is below.
clustering_big.txt

The format is:

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes uuu and vvv in this problem is defined as the Hamming distance--- the number of differing bits --- between the two nodes' labels. For example, the Hamming distance between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of kkk such that there is a kkk-clustering with spacing at least 3? That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly, let alone sort the edges by cost. So you will have to be a little creative to complete this part of the question. For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?
 */
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

uint32_t hammingDistance(uint32_t a, uint32_t b)
{
  uint32_t val = a^b;
  uint32_t dist{0};
  while(val){
    val &= val -1;
    ++dist;
  }
  return dist;
}

std::vector<uint64_t> getAllVertex(std::string const & filePath)
{
  std::ifstream file(filePath); 
  std::string str;
  std::getline(file,str);
  std::istringstream issFirst(str);
  uint64_t numVertex{0};
  uint64_t representation{0};
  issFirst >> numVertex >> representation;
  
  std::vector<uint64_t> vEdges;
  std::cout << "num vertex = "<< numVertex << '\n';
  vEdges.reserve(numVertex);
  while(std::getline(file,str)){
    std::istringstream iss(str);
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    auto number = static_cast<uint64_t>(std::bitset<64>{ str }.to_ulong( ));
    vEdges.emplace_back(number);
  }
  return vEdges;
}

uint32_t getHead(uint64_t pos, std::vector<uint64_t> const& vHeads)
{
  while(pos != vHeads[pos])
    pos = vHeads[pos];

  return pos;
}

void mergeHeads(uint64_t h1, uint64_t h2, std::vector<uint64_t>& vHeads ){
  vHeads[h1] = vHeads[h2];
}

// brute force approach
uint64_t numClustersMinDist(std::vector<uint64_t> const& vVertex, uint32_t minDistance)
{
  std::vector<uint64_t> heads(vVertex.size());
  std::iota(std::begin(heads), std::end(heads), 0);
  uint64_t numClusters{vVertex.size()};
  for(auto it = std::begin(vVertex); it != std::end(vVertex)-1 ; ++it ){
  //  std::cout <<"Iteration =  " <<  (int)(std::distance(std::begin(vVertex),it))  << std::endl;
    for(auto it2 = it + 1; it2 != std::end(vVertex); ++it2 ){
      auto dist = hammingDistance(*it,*it2);
      if(dist <= minDistance /* && dist != 0 */ ){
        auto h1 = getHead(std::distance(std::begin(vVertex),it) , heads);
        auto h2 = getHead(std::distance(std::begin(vVertex),it2), heads);
        if(h1 != h2){
          mergeHeads(h1,h2, heads);
          --numClusters;
        }
      }
    }
  }
  return numClusters;
}


int main()
{
  auto vVertex = getAllVertex("clustering_big.txt");
  std::cout << numClustersMinDist(vVertex, 2) << '\n';
  return 0;
}

