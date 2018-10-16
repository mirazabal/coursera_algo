#include <cstddef>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <functional>
#include <utility>

namespace mirazabal
{

  template<typename T, typename Comp = std::less<T> >
  class BinHeap
  {
    Comp comp;
    T* arr_;
    size_t capacity_;
    size_t size_;
  
    size_t parentIndex(size_t index)
    {
     return (index-1)/2;
    }
    
    size_t rightIndex(size_t index)
    {
      return (index+1)*2;
    }
    
    size_t leftIndex(size_t index)
    {
      return index*2+1;
    }

    void heapify(size_t index)
    {
      size_t left_ind = leftIndex(index);
      if(left_ind >= size_ -1)
        return;
     size_t index_comp_val = index;
      if( comp(arr_[left_ind],arr_[index]) )
        index_comp_val = left_ind;

      size_t right_ind = rightIndex(index);
      if(right_ind >= size_ -1){
        if( comp(arr_[right_ind],arr_[index_comp_val]) ){
          index_comp_val = right_ind;
        } 
      }
      
      if(index_comp_val != index){
        std::swap(arr_[index], arr_[index_comp_val]);
        heapify(index_comp_val);
      }
       
    }

    public:
    explicit BinHeap(size_t capacity) : capacity_(capacity), size_(0)
    {
     arr_ = new T[size_];
    }

    ~BinHeap()
    {
      while(size_ != 0){
        std::cout << "pos = " << size_ -1 << " val = "  << arr_[size_-1] << '\n';
        --size_;
      }
      delete[] arr_;
    } 

    void push(T&& element)
    {
      if(size_ == capacity_)
      {
        throw;
      }

     size_t index = size_;
     arr_[index] = element; 
     while(index != 0 &&  comp(arr_[index],arr_[parentIndex(index)])  ){
       std::swap( arr_[index], arr_[parentIndex(index)] );
       index = parentIndex(index);
     }
     size_++;
    }

    T const& front()
    {
      return arr_[0];
    }
    
    void pop()
    {
      if(size_ == 0) throw;
      std::swap(arr_[0], arr_[size_-1]);
      --size_; 
      ~arr_[size_];
      if(size_ == 0) return;
      heapify(0);
    }
  };

  template<typename T>
  BinHeap<T, std::less<T>> fillBinaryHeap(std::string const& filePath)
  {
    std::ifstream file(filePath);
    std::string str; 
    std::getline(file, str);
    std::istringstream issVert(str);
    T numElements;
    issVert >> numElements; 
    BinHeap<T, std::less<T>> b(numElements);

    while (std::getline(file, str)){
      std::istringstream iss(str);
      T weight;
      if (!(iss >> weight)) { break; } // error	
      b.push(std::move(weight));	
    }
    return b;
  }


  // C implementation
  //
  
  struct HuffmanNode
  {
    uint64_t val_;
    int64_t weight_;
    struct HuffmanNode* left_;
    struct HuffmanNode* right_;
  };

  HuffmanNode* createNode(uint64_t val, int64_t weight)
  {
    HuffmanNode* n = (struct HuffmanNode*)(malloc(sizeof(HuffmanNode)));
    n->left_ = NULL;
    n->right_ = NULL;
    n->val_ = val;
    n->weight_ = weight;
    return n;
  }

  struct HuffmanTree
  {
    size_t capacity_;
    size_t size_;
    struct HuffmanNode** array_; 
  };

  struct HuffmanTree* buildHuffmanTree(size_t capacity)
  {
    struct HuffmanTree* tree = (struct HuffmanTree*)(malloc(sizeof(HuffmanTree)) );
    tree->array_ = (struct HuffmanNode**)(malloc(capacity * sizeof(HuffmanNode*)));
    tree->size_ = 0;
    tree->capacity_ = capacity;
    return tree; 
  }
   
  size_t parentIndex(size_t index)
  {
   return (index-1)/2;
  }
    
  size_t rightIndex(size_t index)
  {
    return (index+1)*2;
  }
    
  size_t leftIndex(size_t index)
  {
    return index*2+1;
  }

  
  void swapHuffmann(HuffmanNode* n0, HuffmanNode* n1)
  {
    HuffmanNode* temp = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    *temp = *n0;
    *n0 = *n1;
    *n1 = *temp;
    free(temp);
  }

  void pushHuffmanTree(HuffmanTree* tree, HuffmanNode* n)
  {
    uint64_t idx = tree->size_;    
    ++tree->size_;
    
    while(idx != 0 && n->weight_ < tree->array_[parentIndex(idx)]->weight_ ){
    tree->array_[idx] = tree->array_[parentIndex(idx)];
    idx = parentIndex(idx);
    }
    tree->array_[idx] = n;
}
 
  void heapifyHuffman(HuffmanTree* tree, uint64_t index)
  {
    uint64_t left_ind = leftIndex(index);
    if(left_ind >=  tree->size_) return;

    uint64_t temp_index = index;
    if(tree->array_[left_ind]->weight_ <  tree->array_[index]->weight_  )
      temp_index = left_ind;

    uint64_t right_ind = rightIndex(index);
    if(right_ind < tree->size_)
    {
      if(tree->array_[right_ind]->weight_ < tree->array_[temp_index]->weight_)
        temp_index = right_ind;
    }
    if(temp_index != index)
    {
      swapHuffmann(tree->array_[index], tree->array_[temp_index] );
      heapifyHuffman(tree,temp_index);
    } 
  }

  HuffmanNode* extractMin(HuffmanTree* tree)
  {
    HuffmanNode* minNode = tree->array_[0];
    tree->array_[0] = tree->array_[tree->size_-1];
    --tree->size_;
    heapifyHuffman(tree,0);
    return minNode;
  }
  
  HuffmanTree* fillHuffmanTreeFromFile(const char* filePath)
  {
    FILE* fp;
    char buffer[255];

    fp = fopen(filePath, "r");
    fgets(buffer, 255, (FILE*) fp);
    int64_t  numElements = atoi(buffer);
    HuffmanTree* tree = buildHuffmanTree(numElements);
    uint64_t val = 0;
    while(fgets(buffer, 255, (FILE*) fp)) {
         HuffmanNode* n0 = createNode(val,atoi(buffer));
         pushHuffmanTree(tree, n0); 
         ++val;
    }
    fclose(fp);
    return tree;
  }

  HuffmanNode* mergeNodes(HuffmanNode* n0, HuffmanNode* n1)
  {
    HuffmanNode* n2 = createNode(-1, n0->weight_ + n1->weight_);
    n2->left_ = n0;
    n2->right_ = n1;
    return n2;
  }

  HuffmanTree* generateHuffmanCode(HuffmanTree* tree)
  {
    while(tree->size_ > 1){
      HuffmanNode* n0 = extractMin(tree);
      HuffmanNode* n1 = extractMin(tree);
      HuffmanNode* n2 = mergeNodes(n0,n1);
      pushHuffmanTree(tree, n2);
    }
  return tree;
  }
  bool isNodeALeaf(HuffmanNode* n)
  {
    return (n->left_ == NULL && n->right_ == NULL);
  }

  void getLength(HuffmanNode* n, size_t  actualLevel, size_t* deepestLevel, size_t* surfaceLevel)
  {
    if(n->left_ != NULL){
      getLength(n->left_, actualLevel + 1, deepestLevel, surfaceLevel );
    }
    if(n->right_ != NULL){
      getLength(n->right_, actualLevel + 1, deepestLevel, surfaceLevel );
    }

    if( isNodeALeaf(n) ){
      if(actualLevel > *deepestLevel)
        *deepestLevel = actualLevel;

      if(actualLevel < *surfaceLevel )
        *surfaceLevel = actualLevel ;
    }
  }

  struct MaxMin
  {
    size_t max;
    size_t min;
  };

  struct MaxMin lenghtsPathHuffmanCode(HuffmanTree* tree)
  {
    size_t maxLenghtLeaf{0};
    size_t minLenghtLeaf{10000000};
    getLength(tree->array_[0], 0, &maxLenghtLeaf, &minLenghtLeaf);
    MaxMin maxmin;
    maxmin.max = maxLenghtLeaf;
    maxmin.min = minLenghtLeaf;
    return maxmin;
  }

 
  void freeHuffmanTree( HuffmanTree* tree){
    int i = 0;
    for(i = 0; i < tree->size_; i++){
       tree->array_[i];



    }

  }
}; // end namespace mirazabal


int main()
{

  mirazabal::HuffmanTree* tree = mirazabal::fillHuffmanTreeFromFile("huffman.txt");
  mirazabal::HuffmanTree* treeHuffman = mirazabal::generateHuffmanCode(tree);
  mirazabal::MaxMin maxmin = mirazabal::lenghtsPathHuffmanCode(treeHuffman);
  printf("max lenght = %ld\n", maxmin.max);
  printf("min lenght = %ld\n", maxmin.min);

 freeHuffmanTree(tree);
//  auto b = mirazabal::fillBinaryHeap<uint64_t>("huffman.txt");


  return 0;
}
