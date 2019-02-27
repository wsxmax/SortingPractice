#ifndef MARRAY_H
#define MARRAY_H
#define DATATYPE float
#include <iostream>
#include <stdlib.h>
#define status int
class mArray {
public:
  mArray();
  mArray(int dim, int* bounds, DATATYPE* data);
  ~mArray();
  DATATYPE getElement(int givenIndex);
  DATATYPE getElement(int* indices);
  status setElement(int givenIndex, DATATYPE element);
  status setElement(int* indices, DATATYPE element);
  int getLength();
private:
  int dim;
  int* bound;
  int length;
  int* index;
  int calculateIndex(int* indices);
  DATATYPE* data;
};

//deefine the class

mArray::mArray(){
  dim = 0;
  bound = nullptr;
  length = 0;
  index = nullptr;
  data = nullptr;
}
mArray::mArray(int newdim, int* newbound, DATATYPE* newdata){
  dim = newdim;
  if (dim == 0){
    bound = nullptr;
    index = nullptr;
    data = nullptr;
  }
  else{
    bound = (int*)malloc(dim*sizeof(int));
    length = 1;
    index = (int*)malloc(dim*sizeof(int));
    int current_index = 1;
    for(int i = dim-1; i >= 0; i--){
      bound[i] = newbound[i];
      index[i] = current_index;
      current_index *= bound[i];
    }
    length = current_index;
    for (int i = 0; i < length; i++){
      data[i] = newdata[i];
    }
  }
}

mArray::~mArray(){
  if(this->bound!=nullptr) free(this->bound);
  if(this->index!=nullptr) free(this->index);
}

int mArray::getLength(){
  return length;
}

int mArray::calculateIndex(int* indices){
  for (int i = 0; i < dim; i++){
    if (indices[i]>=bound[i]) std::cout << "illeagel indices will segment fault" << std::endl;}
    int pos = 0;
    for(int i = 0; i < dim; i++){
      pos += index[i]*indices[i];
    }
    return pos;
  }

  DATATYPE mArray::getElement(int givenIndex){
    if (givenIndex<length) return data[givenIndex];
    else std::cout<< "illeagle index to get" << std::endl;
  }
  DATATYPE mArray::getElement(int* indices){
    return getElement(calculateIndex(indices));
  }

  status mArray::setElement(int givenIndex, DATATYPE element){
    if (givenIndex<length) {
      data[givenIndex] = element;
      return 1;
    }else{
      std::cout << "illeagle index" << std::endl;
      return 0;
    }
  }

  status mArray::setElement(int* indices, DATATYPE element){
    data[calculateIndex(indices)] = element;
  }



  #endif
