#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
using namespace std;
const int HOME_TEAM_WON = 1;
void updateScores(string team, int points, unordered_map<string, int>& scores);

string tournamentWinner(
  vector<vector<string>> competitions, vector<int> results
) {
  string currentBestTeam = "";
  unordered_map<string, int> scores = {{currentBestTeam, 0}};
  

  for(int idx = 0; idx < results.size(); idx++) {
    auto result = results[idx];
    auto competition = competitions[idx];
    auto homeTeam = competition[0];
    auto awayTeam = competition[1];
    

    auto winningTeam = (result == HOME_TEAM_WON) ? homeTeam : awayTeam;
    updateScores(winningTeam, 3, scores);

    if(scores[winningTeam] > scores[currentBestTeam]) {
      currentBestTeam = winningTeam;
    }
    
  }
  
  // Write your code here.
  return currentBestTeam;
}
// & - to use original unoredered_map not a copy
void updateScores(string team, int points, unordered_map<string, int>& scores) {
  
  if(scores.find(team) == scores.end())
  scores[team] = 0;

  scores[team] += points;
}
int main(){
  vector<vector<string>> competitions = {
    {"Team A", "Team B"},
    {"Team C", "Team D"},
    {"Team K", "Team L"}
  };
  vector<int> results = {1,0,1};

  cout<<tournamentWinner(competitions, results)<<endl;
}
