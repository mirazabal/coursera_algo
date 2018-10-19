/*
In this programming problem and the next you'll code up the knapsack algorithm from lecture.

Let's start with a warm-up. Download the text file below.
knapsack1.txt

This file describes a knapsack instance, and it has the following format:

[knapsack_size][number_of_items]

[value_1] [weight_1]

[value_2] [weight_2]

...

For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. And then post them to the discussion forum!
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace mirazabal
{

struct Node
{
  int64_t value;
  int64_t weight;
};

std::vector<Node> readFile(const char* filePath)
{
  std::ifstream ifs(filePath);
  std::string str1;
  std::vector<Node> vec;
  if(!std::getline(ifs,str1))
    return vec;
  
  std::istringstream iss(str1);
  uint64_t max_weight; 
  uint64_t size;
  iss >> max_weight >> size;
  vec.reserve(size);
  
  std::string str;
 while(std::getline(ifs,str)){
  std::istringstream iss(str);
  Node n0;
  iss >> n0.value >> n0.weight;
  vec.emplace_back(n0);
 } 
 return vec; 
}

uint64_t knapsack(std::vector<Node> const& vec, uint64_t max_weight)
{
  std::vector<std::vector<uint64_t>> arr( vec.size() + 1 , std::vector<uint64_t>(max_weight +1 ));
  for(auto w = 0; w < max_weight; ++w)
    arr[0][w] = 0;

  for(auto i = 1; i < vec.size() + 1; ++i){
    for(auto w = 1; w < max_weight; ++w){
      if( w-vec[i-1].weight > -1)
        arr[i][w] = std::max(arr[i-1][w], vec[i-1].value +  arr[ i-1][w-vec[i-1].weight] );
      else
        arr[i][w] = arr[i-1][w];
    }
  }

  return arr[vec.size()][max_weight-1];
}

} //  end namespace mirazabal

int main()
{
  auto vecNode = mirazabal::readFile("knapsack_big.txt");
  std::cout << mirazabal::knapsack(vecNode, 2000000 ) << '\n'; 
  return 0;
}
