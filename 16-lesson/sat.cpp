/*
 *

In this assignment you will implement one or more algorithms for the 2SAT problem. Here are 6 different 2SAT instances:

The file format is as follows. In each instance, the number of variables and the number of clauses is the same, and this number is specified on the first line of the file. Each subsequent line specifies a clause via its two literals, with a number denoting the variable and a "-" sign denoting logical "not". For example, the second line of the first data file is "-16808 75250", which indicates the clause ¬x16808∨x75250\neg x_{16808} \vee x_{75250}¬x16808​∨x75250​.

Your task is to determine which of the 6 instances are satisfiable, and which are unsatisfiable. In the box below, enter a 6-bit string, where the ith bit should be 1 if the ith instance is satisfiable, and 0 otherwise. For example, if you think that the first 3 instances are satisfiable and the last 3 are not, then you should enter the string 111000 in the box below.

DISCUSSION: This assignment is deliberately open-ended, and you can implement whichever 2SAT algorithm you want. For example, 2SAT reduces to computing the strongly connected components of a suitable graph (with two vertices per variable and two directed edges per clause, you should think through the details). This might be an especially attractive option for those of you who coded up an SCC algorithm in Part 2 of this specialization. Alternatively, you can use Papadimitriou's randomized local search algorithm. (The algorithm from lecture is probably too slow as stated, so you might want to make one or more simple modifications to it --- even if this means breaking the analysis given in lecture --- to ensure that it runs in a reasonable amount of time.) A third approach is via backtracking. In lecture we mentioned this approach only in passing; see Chapter 9 of the Dasgupta-Papadimitriou-Vazirani book, for example, for more details.

 * */
#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

namespace GeeksForGeeks
{
  // C++ implementation to find if the given 
  // expression is satisfiable using the 
  // Kosaraju's Algorithm 
//#include <bits/stdc++.h> 
  using namespace std; 

  const int MAX = 100000; 

  // data structures used to implement Kosaraju's 
  // Algorithm. Please refer 
  // http://www.geeksforgeeks.org/strongly-connected-components/ 
  std::vector<int> adj[MAX]; 
  std::vector<int> adjInv[MAX]; 
  bool visited[MAX]; 
  bool visitedInv[MAX]; 
  std::stack<int> s; 

  // this array will store the SCC that the 
  // particular node belongs to 
  int scc[MAX]; 

  // counter maintains the number of the SCC 
  int counter = 1; 

  // adds edges to form the original graph 
  void addEdges(int a, int b) 
  { 
    adj[a].push_back(b); 
  } 

  // add edges to form the inverse graph 
  void addEdgesInverse(int a, int b) 
  { 
    adjInv[b].push_back(a); 
  } 

  // for STEP 1 of Kosaraju's Algorithm 
  void dfsFirst(int u) 
  { 
    if(visited[u]) 
      return; 

    visited[u] = 1; 

    for (int i=0;i<adj[u].size();i++) 
      dfsFirst(adj[u][i]); 

    s.push(u); 
  } 

  // for STEP 2 of Kosaraju's Algorithm 
  void dfsSecond(int u) 
  { 
    if(visitedInv[u]) 
      return; 

    visitedInv[u] = 1; 

    for (int i=0;i<adjInv[u].size();i++) 
      dfsSecond(adjInv[u][i]); 

    scc[u] = counter; 
  } 

  // function to check 2-Satisfiability 
  void is2Satisfiable(int n, int m, int a[], int b[]) 
  { 
    // adding edges to the graph 
    for(int i=0;i<m;i++) 
    { 
      // variable x is mapped to x 
      // variable -x is mapped to n+x = n-(-x) 

      // for a[i] or b[i], addEdges -a[i] -> b[i] 
      // AND -b[i] -> a[i] 
      if (a[i]>0 && b[i]>0) 
      { 
	addEdges(a[i]+n, b[i]); 
	addEdgesInverse(a[i]+n, b[i]); 
	addEdges(b[i]+n, a[i]); 
	addEdgesInverse(b[i]+n, a[i]); 
      } 

      else if (a[i]>0 && b[i]<0) 
      { 
	addEdges(a[i]+n, n-b[i]); 
	addEdgesInverse(a[i]+n, n-b[i]); 
	addEdges(-b[i], a[i]); 
	addEdgesInverse(-b[i], a[i]); 
      } 

      else if (a[i]<0 && b[i]>0) 
      { 
	addEdges(-a[i], b[i]); 
	addEdgesInverse(-a[i], b[i]); 
	addEdges(b[i]+n, n-a[i]); 
	addEdgesInverse(b[i]+n, n-a[i]); 
      } 

      else
      { 
	addEdges(-a[i], n-b[i]); 
	addEdgesInverse(-a[i], n-b[i]); 
	addEdges(-b[i], n-a[i]); 
	addEdgesInverse(-b[i], n-a[i]); 
      } 
    } 

    // STEP 1 of Kosaraju's Algorithm which 
    // traverses the original graph 
    for (int i=1;i<=2*n;i++) 
      if (!visited[i]) 
	dfsFirst(i); 

    // STEP 2 pf Kosaraju's Algorithm which 
    // traverses the inverse graph. After this, 
    // array scc[] stores the corresponding value 
    while (!s.empty()) 
    { 
      int n = s.top(); 
      s.pop(); 

      if (!visitedInv[n]) 
      { 
	dfsSecond(n); 
	counter++; 
      } 
    } 

    for (int i=1;i<=n;i++) 
    { 
      // for any 2 vairable x and -x lie in 
      // same SCC 
      if(scc[i]==scc[i+n]) 
      { 
        std::cout << "The given expression "
	  "is unsatisfiable." << std::endl; 
	return; 
      } 
    } 

    // no such variables x and -x exist which lie 
    // in same SCC 
    std::cout << "The given expression is satisfiable."
      << std::endl; 
    return; 
  } 

  //  Driver function to test above functions 
  int main() 
  { 
    // n is the number of variables 
    // 2n is the total number of nodes 
    // m is the number of clauses 
    int n = 5, m = 7; 

    // each clause is of the form a or b 
    // for m clauses, we have a[m], b[m] 
    // representing a[i] or b[i] 

    // Note: 
    // 1 <= x <= N for an uncomplemented variable x 
    // -N <= x <= -1 for a complemented variable x 
    // -x is the complement of a variable x 

    // The CNF being handled is: 
    // '+' implies 'OR' and '*' implies 'AND' 
    // (x1+x2)*(x2’+x3)*(x1’+x2’)*(x3+x4)*(x3’+x5)* 
    // (x4’+x5’)*(x3’+x4) 
    int a[] = {1, -2, -1, 3, -3, -4, -3}; 
    int b[] = {2, 3, -2, 4, 5, -5, 4}; 

    // We have considered the same example for which 
    // Implication Graph was made 
    is2Satisfiable(n, m, a, b); 

    return 0; 
  } 
} // end namespace geeks for geeks 


namespace mirazabal {
  class Graph
  {

    public:
    explicit Graph(uint64_t vertices) : vEdges_(vertices)
    {

    }	

      void addEdge(int64_t src, int64_t dest)
      {
	vEdges_[src].emplace_back(dest);
      }

      std::vector<std::vector<int64_t>> vEdges_;
  };

  void DFS_first(uint64_t pos, Graph const &g, std::vector<bool>& visited, std::stack<int64_t>& sta)
  {
    visited[pos] = true;
    sta.push(pos);
    for(auto dest : g.vEdges_[pos]){
      if(!visited[dest]){
	DFS_first(dest,g,visited,sta);
      }
    }	
  }

  std::stack<int64_t> kosaraju_first(Graph const & g)
  {
    std::stack<int64_t> sta;
    std::vector<bool> visited(g.vEdges_.size());
    std::fill(std::begin(visited), std::end(visited), false);
    for(int i = 0; i < g.vEdges_.size(); ++i){
      if(!visited[i] ) 
	DFS_first(i,g,visited,sta);
    }
    return sta;
  }

  void DFS_second(uint64_t pos, Graph const & g, std::vector<bool>& visited, std::vector<int64_t>& scc)
  {
    visited[pos] = true;
    for(auto dest: g.vEdges_[pos]){
      if(!visited[dest] ){
	scc.push_back(dest);
        DFS_second(dest,g,visited,scc);
      }
    }
  }

  std::vector<std::vector<int64_t>> kosaraju_second(Graph const & g, std::stack<int64_t>& sta)
  {
    std::vector<bool> visited(g.vEdges_.size());
    std::fill(std::begin(visited), std::end(visited), false);
    std::vector<std::vector<int64_t>> sccVec;
    while(!sta.empty()){
      auto v = sta.top();
      sta.pop();
      if(!visited[v]){
        std::vector<int64_t> scc;
        scc.push_back(v);
	DFS_second(v,g,visited,scc);
	sccVec.emplace_back(scc);
      }
    }
    return sccVec;
  }

  struct Nodes
{
  std::vector<int64_t> src;
  std::vector<int64_t> dest;
};



Nodes readFromFilePath(const char* filePath)
{
  std::ifstream file(filePath);
  std::string str; 
  std::getline(file, str);
  std::istringstream iss(str);
  uint64_t numberOfVertices;
  iss >> numberOfVertices;
  
  Nodes vertices;
  vertices.src.reserve(numberOfVertices);
  vertices.dest.reserve(numberOfVertices);
  
  while (std::getline(file, str)){
    std::istringstream iss(str);
    int64_t src, dest;
    if (!(iss >> src >> dest)) { break; } // error	
    if(src < 0) src = (-1)*src + numberOfVertices;
    if(dest < 0) dest = (-1)*dest + numberOfVertices;
    vertices.src.push_back(src-1);
    vertices.dest.push_back(dest-1);
  }
  return vertices;
}

struct ConjunctiveNormalForm
{
  int64_t src;
  int64_t dest;
};

int64_t getNegate(int64_t val, int64_t negateFlag)
{
  if(val >= negateFlag)
    val -= negateFlag;
  else 
    val += negateFlag;

  return val;
}

std::array<ConjunctiveNormalForm,2> convertVertices(int64_t src, int64_t dest, int64_t negateFlag)
{
  int64_t first = getNegate(src,negateFlag);
  int64_t second = getNegate(dest,negateFlag);

  std::array<ConjunctiveNormalForm,2> convertedVertices;
  convertedVertices[0].src = first;
  convertedVertices[0].dest = dest;
  convertedVertices[1].src = src;
  convertedVertices[1].dest = second;

  return convertedVertices;
}

}// end namespace mirazabal


#include <fstream>

int main()
{
  auto vert = mirazabal::readFromFilePath("2sat1.txt");
  mirazabal::Graph g1(vert.src.size()*2);
  mirazabal::Graph g2(vert.src.size()*2);
  for(int i=0; i < vert.src.size(); ++i){
    auto convertedVertices = mirazabal::convertVertices(vert.src[i], vert.dest[i], vert.src.size());
    g1.addEdge(convertedVertices[0].src, convertedVertices[0].dest);
    g1.addEdge(convertedVertices[1].dest, convertedVertices[1].src);

    g2.addEdge(convertedVertices[0].dest, convertedVertices[0].src);
    g2.addEdge(convertedVertices[1].src, convertedVertices[1].dest);
  }

  std::stack<int64_t> st = kosaraju_first(g1);
  auto sccVec = kosaraju_second(g2,st);

  for(auto scc : sccVec){
    std::sort(std::begin(scc), std::end(scc));
    for(auto val : scc){
      if(val > vert.src.size())
        val = val - vert.src.size();
      else
        val += vert.src.size(); 
      if(std::binary_search(std::begin(scc),std::end(scc),val)){
        std::cout << "Impossible to meet the requirements in this 2 SAT problem" << '\n';
        return -1;
      }
    }
  }

  std::cout << "Possible to meet the requirements in this 2 SAT problem" << '\n';
  return 0;
}
