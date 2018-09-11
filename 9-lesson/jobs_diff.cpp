/*
In this programming problem and the next you'll code up the greedy algorithms from lecture for minimizing the weighted sum of completion times..

Download the text file below.

This file describes a set of jobs with positive and integral weights and lengths. It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length]

...

For example, the third line of the file is "74 59", indicating that the second job has weight 74 and length 59.

You should NOT assume that edge weights or lengths are distinct.

Your task in this problem is to run the greedy algorithm that schedules jobs in decreasing order of the difference (weight - length). Recall from lecture that this algorithm is not always optimal. IMPORTANT: if two jobs have equal difference (weight - length), you should schedule the job with higher weight first. Beware: if you break ties in a different way, you are likely to get the wrong answer. You should report the sum of weighted completion times of the resulting schedule --- a positive integer --- in the box below.

ADVICE: If you get the wrong answer, try out some small test cases to debug your algorithm (and post your test cases to the discussion forum).
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

namespace mirazabal {
template<typename T>
std::vector<std::pair<T,T>> readAndFillVectorFromFile(std::string const& filePath)
{
 std::ifstream file(filePath);
  std::string str;
  std::getline(file,str);
  uint64_t lenght;
  std::istringstream iss(str);
  iss >> lenght;
  std::vector<std::pair<T,T>> vec;
  vec.reserve(lenght);
  while(std::getline(file,str)){
    std::istringstream iss(str);
    T  weight, lenght;
    iss >> weight >> lenght;
    vec.emplace_back(std::make_pair(weight,lenght));
  }
  return vec;
};


} // end namepsane mirazabal


int main()
{
  auto vec = mirazabal::readAndFillVectorFromFile<int64_t>("jobs.txt");
  std::sort(std::begin(vec),std::end(vec),[](auto const& p1, auto const& p2)
      { 
        auto diff1 = p1.first-p1.second;
        auto diff2 = p2.first-p2.second;
        if(diff1 > diff2)
          return true;
        if(diff1 == diff2){
          if(p1.first > p2.first)
            return true;
        }
        return false;
      });
  uint64_t totalLenght{0};
  uint64_t functionCost{0};
  for(auto const& p : vec){
    totalLenght += p.second;
    functionCost += totalLenght*p.first; 
  
  }
  std::cout << functionCost << '\n';


  return 0;
}

