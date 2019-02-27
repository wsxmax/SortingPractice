#include "marray.h"


void printArray(DATATYPE* array, int length){
  std::cout << array[0];
  for(int i=1;i<length;i++){
    std::cout<< ", "<< array[i];
  }
  std::cout << "\n";
}
void swap(DATATYPE &first, DATATYPE &second){
  DATATYPE temp = first;
  first = second;
  second = temp;
}

void insertElementTo(DATATYPE* array,int to,int from){
  if(to==from) return;
  DATATYPE temp = array[from];
  for(int i=from;i>to;i--){
    array[i] = array[i-1];
  }
  array[to] = temp;
}

void selectionSort(DATATYPE* array, int length){
  std::cout << "do SelectionSort:" << '\n';
  for(int i=0;i<length;i++){
    for(int j=i+1;j<length;j++){
      if(array[j]<array[i]) swap(array[i],array[j]);
    }
  }
}
//---------------------------Selection Sort-------------------------------------------------------

void insertionSort(DATATYPE* array, int length){
  std::cout << "do insertionSort:" << '\n';
  for(int i=1;i<length;i++){
    int j=0;
    for(j=0;j<i;j++){
      if(array[i]<array[j]) break;
    }
    insertElementTo(array,j,i);
  }
}
//----------------------------Insertion Sort----------------------------------------------------------------

void bubbleSort(DATATYPE* array, int length){
  std::cout << "do BubbleSort" << "\n";
  int swaped = 1;
  while(swaped){
    swaped = 0;
    for(int i=1;i<length;i++){
      if(array[i]<array[i-1]) {
        swap(array[i],array[i-1]);
        swaped = 1;
      }
    }
  }
}
//---------------------Bubbke sort-------------------------------------------------------------
void merge(DATATYPE* first, int firstLength, DATATYPE* second, int secondLength, DATATYPE* out){
  int i=0, j=0, k=0;
  std::cout<<"--------------------begin merge----------------------------------\n";
  std::cout<<"the arrays are: ";
  printArray(first,firstLength);
  std::cout<<" and ";
  printArray(second,secondLength);
  while(i<firstLength&&j<secondLength){
    if(first[i]<second[j]){
      out[k] = first[i];
      i+=1;
    }else{
      out[k] = second[j];
      j+=1;
    }
    k+=1;
  }
  if(i == firstLength){
    while(k< firstLength+secondLength){
      out[k] = second[j];
      j++; k++;
    }
  } else
  while(k< firstLength+secondLength){
    out[k] = first[i];
    i++; k++;
  }
  std::cout<< "merged array is: ";
  printArray(out,firstLength+secondLength);
}

void mergeSort(DATATYPE* array,int length){
  std::cout << "do MergeSort" << "\n";
  int currentLength = 1;
  int cycle = length/2;
  int theRemainder = length%2;
  DATATYPE* swapArray =(DATATYPE*)malloc(length*sizeof(DATATYPE));
  DATATYPE* currentOutArray = swapArray;
  DATATYPE* currentArray = array;
  int changeArray = 1;
  while(cycle>0){
    switch(changeArray){
      case 1: currentOutArray = swapArray; currentArray = array; std::cout<<"current outArray is swapArray\n";
      break;
      case -1: currentOutArray = array; currentArray = swapArray; std::cout<<"current outArray is Array\n";
    }

    std::cout<<"current length is: "<< currentLength <<" current cycle is: "<< cycle <<" current remainder is: " << theRemainder << std::endl;
    if(theRemainder==0){
      for(int index=0;index<cycle-1;index++){
        merge(&(currentArray[2*index*currentLength]),currentLength,&(currentArray[2*index*currentLength+currentLength]),currentLength,&(currentOutArray[2*index*currentLength]));
      }
      merge(&(currentArray[2*(cycle-1)*currentLength]),currentLength,&(currentArray[2*(cycle-1)*currentLength+currentLength]),length-2*(cycle-1)*currentLength-currentLength,&(currentOutArray[2*(cycle-1)*currentLength]));
      std::cout<< "before last merge current outArray looks like: ";
      printArray(currentOutArray,length);

    }else{
      for(int index=0;index<cycle;index++){
        merge(&(currentArray[2*index*currentLength]),currentLength,&(currentArray[2*index*currentLength+currentLength]),currentLength,&(currentOutArray[2*index*currentLength]));
      }
      std::cout<< "before last merge current outArray looks like: ";
      printArray(currentOutArray,length);
      DATATYPE* temp = (DATATYPE*)malloc(sizeof(DATATYPE)*(length-2*(cycle-1)*currentLength));
      merge(&(currentOutArray[2*(cycle-1)*currentLength]),2*currentLength,&(currentArray[2*cycle*currentLength]),length-2*cycle*currentLength,temp);
      for(int i=2*(cycle-1)*currentLength;i<length;i++){
        currentOutArray[i] = temp[i-2*(cycle-1)*currentLength];
      }
      free(temp);

    }
    std::cout<< " after last merge current outArray looks like: ";
    printArray(currentOutArray,length);
    currentLength*=2;
    theRemainder = cycle%2;
    cycle/=2;
    changeArray = -changeArray;
  }
  for(int i=0;i<length;i++){
    array[i] = currentOutArray[i];
  }
  free(swapArray);
}
//-------------------------------Merge Sort---------------------------------------------------------------------------------

void sortInSubArrayOfInterval(DATATYPE* array, int length, int interval){
  if(interval>length/2) std::cout << "meaningless interval: "<<interval <<" with length: "<< length << std::endl;
  DATATYPE temp;
  for (int i=0;i<interval;i++){
    for(int j=i+interval;j<length&&j>0;j+=interval){
      if(array[j]<array[j-interval]) {
        temp = array[j]; array[j] = array[j-interval]; array[j-interval]=temp;
        j-=interval*2;
      }
    }
  }
}

int shellSort(DATATYPE* array, int length){
  std::cout << "do shellSort with length :"<< length  << '\n';
  for(int i=length/2;i>0;i/=2){
    sortInSubArrayOfInterval(array,length,i);
  }
}
//----------------------------------Shell Sort-------------------------------------------------------------------

int partArray(DATATYPE* array, int length){
  int left, right, pos;
  left=0;
  right=length-1;
  std::cout<<"------------------------------------------------------------\n";
  while(left<=right){
    std::cout<<"left: "<<left<<" right: "<<right<<std::endl;
    if(array[left]>array[0]&&array[right]<array[0]) {
      swap(array[left],array[right]);
      std::cout<< "swap "<<array[right]<<" and "<<array[left]<<" by "<<array[0]<<std::endl;
      left++; right--;
    }else{
      if(array[left]<=array[0]) left++;
      if(array[right]>=array[0]) right--;
    }
  }
  swap(array[0],array[right]);
  return right;
}

void quickSort(DATATYPE* array, int length){
  if(length<3){
    insertionSort(array,length);
  }else{
    int pivotIndex = partArray(array,length);
    quickSort(array,pivotIndex);
    quickSort(array+pivotIndex+1,length-pivotIndex-1);
  }
}
//-------------------------------Quick Sort--------------------------------

int checkChild(DATATYPE* array, int length, int index){
  if(index>=length) std::cout<<"unreasonable index"<<std::endl;
  int swaped = 0;
  if(index<<1<length-1){
    if(array[index]<array[(index<<1)+1]){
      swap(array[index],array[(index<<1)+1]);
      swaped = 1;
    }
    if(index<<1<length-2){
      if(array[index]<array[(index<<1)+2]){
        swap(array[index],array[(index<<1)+2]);
        if(swaped==1) {
          swap(array[(index<<1)+1],array[(index<<1)+2]);
        }
        swaped = 2;
      }
    }
  }
  return swaped;
}


void checkAsRoot(DATATYPE* array, int length, int index){
  std::cout<<"checkAsRoot at length: "<<length<< " and index: "<< index <<std::endl;
  int nextIndex;
  if(index>=length){
    std::cout<<"you are abuout to get an segment fault error cuz you are passing an unreasonable index" <<std::endl;
  }
  nextIndex=checkChild(array,length,index)-1;
  if(nextIndex!=-1) {
    checkAsRoot(array,length,(index<<1)+1+nextIndex);
  }
}

void checkHeap(DATATYPE* array, int length){
  int swaped = 0;
  for(int i=0;i<length;i++){
    swaped = checkChild(array,length,i);
    if(swaped!=0&&i!=0) checkChild(array,length,(i-1)>>1);
  }
}

void heapSort(DATATYPE* array,int length){
  std::cout<<"do heapSort"<<std::endl;
  checkHeap(array,length);
  std::cout<<"sorted heap as: ";
  printArray(array,length);
  std::cout<<"----------------------------------------------------------------";
  int swaped;
  for(int i=length-1;i>0;i--){
    swap(array[0],array[i]);
    checkAsRoot(array,i,0);
  }
}


int main(int argc, char** argv){
  using namespace std;
  DATATYPE array[10] = {0,3,6,7,4,5,9,2,8,1};
  printArray(array,sizeof(array)/sizeof(array[0]));
  heapSort(array,sizeof(array)/sizeof(array[0]));
  printArray(array,sizeof(array)/sizeof(array[0]));
}
