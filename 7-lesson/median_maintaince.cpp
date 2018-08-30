/*
The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 3 lecture on heap applications). The text file contains a list of the integers from 1 to 10000 in unsorted order; you should treat this as a stream of numbers, arriving one by one. Letting xix_ixi​ denote the iiith number of the file, the kkkth median mkm_kmk​ is defined as the median of the numbers x1,…,xkx_1,\ldots,x_kx1​,…,xk​. (So, if kkk is odd, then mkm_kmk​ is ((k+1)/2)((k+1)/2)((k+1)/2)th smallest number among x1,…,xkx_1,\ldots,x_kx1​,…,xk​; if kkk is even, then mkm_kmk​ is the (k/2)(k/2)(k/2)th smallest number among x1,…,xkx_1,\ldots,x_kx1​,…,xk​.)

In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). That is, you should compute (m1+m2+m3+⋯+m10000)mod10000(m_1+m_2+m_3 + \cdots + m_{10000}) \bmod 10000(m1​+m2​+m3​+⋯+m10000​)mod10000.

OPTIONAL EXERCISE: Compare the performance achieved by heap-based and search-tree-based implementations of the algorithm.
 */

#include <algorithm>
#include <cmath>
#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>



int main()
{

  double result{0};
  std::priority_queue<uint64_t,std::vector<uint64_t>, std::less<uint64_t> > q_less;
  std::priority_queue<uint64_t,std::vector<uint64_t>, std::greater<uint64_t> > q_greater;

  std::ifstream file("Median.txt");
  std::string str; 
  uint64_t med_val = std::numeric_limits<uint64_t>::max();
  while (std::getline(file, str)){
    std::istringstream iss(str);
    uint64_t val;//, dest, val;
    iss >> val;
    if(val < med_val){
      q_less.push(val);
    } else {
      q_greater.push(val);
    }
    
    if(q_greater.size() > q_less.size() + 1){
      auto val = q_greater.top();
      q_greater.pop();
      q_less.push(val);
    }
    if(q_less.size() > q_greater.size() +1 ){
      auto val = q_less.top();
      q_less.pop();
      q_greater.push(val);
    }
    med_val = q_less.top();


    if(q_less.size() >= q_greater.size()){
      auto top =  q_less.top();
      std::cout << "top value in less > " << top << std::endl;
      result += top;
      if(result > 10000) result -= 10000;
    }
    else if (q_less.size() < q_greater.size()){
      auto top =  q_greater.top();
      std::cout << "top value in less < " << top << std::endl;
      result += top;
      if(result > 10000) result -= 10000;
    }
    
/*    else{
      result += (q_greater.top() + q_less.top()) / 2;
      if(result > 10000) result -= 10000;
    }*/
    std::cout << "partial resul = " << result << '\n';
  }

  std::cout << "end result = " << result << '\n';
  return 0;
}
