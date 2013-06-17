#include <iostream>
using namespace std;

template <typename T>
struct PtrLess
{     
  bool operator()(const T* a, const T* b) const     
  {
    return *a < *b;
  } 
}; 

//http://stackoverflow.com/questions/5103682/how-to-sort-qlistmyclass-using-qt-library-maybe-qsort
int my_function(int *arr,int len, bool(*fn)(int,int))
{
    int res = arr[0];
 
    for(int i = 1; i < len; ++i)
        if(fn(res,arr[i]))
            res = arr[i];
 
    return res;
}
 
bool max_(int i, int j) { return i < j; }
bool min_(int i, int j) { return i > j; }
 
int main()
{
    int arr[5] = {0,-1,2,3,5};
 
    cout<<"Max elem: "<<my_function(arr,5,max_)<<endl;
    cout<<"Min elem: "<<my_function(arr,5,min_)<<endl;
 
	system("pause");
    return 0;
}