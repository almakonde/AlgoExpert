//* Function to calculate x raised to the power y in
// * O(logn)*/
#include <vector>
#include <cmath>
using namespace std;
int power(int x, unsigned int y)
{
    int temp;
    if (y == 0)
        return 1;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
        return x * temp * temp;
}
vector<int> sortedSquaredArray(vector<int> array) {
  vector<int> sortedSquares(array.size(), 0);

  int idxBegin = 0;
  int idxEnd = array.size() - 1;
  //cycle from the end
  for(int i = array.size() - 1; i >= 0; i --) { 
    if (abs(array[idxBegin]) > abs(array[idxEnd])) {
      sortedSquares[i] = power(array[idxBegin],2);
      idxBegin ++;
    }
    else {
      sortedSquares[i] = power(array[idxEnd], 2);
      idxEnd --;
    }
    
  }
  // Write your code here.
  return sortedSquares;
}
int main() {
    vector<int> input = {1,2,3,5,6,8,9};
    vector<int> result = sortedSquaredArray(input);
}
