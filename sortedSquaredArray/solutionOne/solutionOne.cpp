#include <vector>
using namespace std;

vector<int> sortedSquaredArray(vector<int> array) {
  vector<int> sortedSquares(array.size(), 0);

  for(int idx = 0; idx < array.size(); idx++ ) {
    int value = array[idx];
    sortedSquares[idx] = value * value;
  }

  sort(sortedSquares.begin(), sortedSquares.end());
  
  // Write your code here.
  return sortedSquares;
}
