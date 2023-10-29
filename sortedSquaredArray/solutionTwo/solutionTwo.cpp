#include <vector>
using namespace std;

vector<int> sortedSquaredArray(vector<int> array) {
  vector<int> sortedSquares(array.size(), 0);

  int smallerValueIdx = 0;
  int largerValueIdx = array.size() - 1;
  int smallerValue = 0;
  int largerValue = 0;

  for (int idx = array.size() - 1; idx >= 0; idx --) {
    smallerValue = array[smallerValueIdx];
    largerValue = array[largerValueIdx];

    if(abs(smallerValue) > abs(largerValue)) {
      sortedSquares[idx] = smallerValue * smallerValue;
      smallerValueIdx ++;
    } else {
      sortedSquares[idx] = largerValue * largerValue;
      largerValueIdx --;
    }
  }
  // Write your code here.
  return sortedSquares;
}
