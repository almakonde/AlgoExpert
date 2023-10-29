#include <vector>
#include <unordered_set>
using namespace std;

const int HOME_TEAM_WON = 1;

void updateScores(string team, int points, unordered_set<string>& teams, unordered_set<string>& currentBestTeams) {
    teams.insert(team);

    for (const string& t : teams) {
        if (t != team) {
            currentBestTeams.erase(t);
        }
    }
}

string tournamentWinner(
    vector<vector<string>> competitions, vector<int> results
) {
    unordered_set<string> teams;
    unordered_set<string> currentBestTeams = {""};

    for (int idx = 0; idx < competitions.size(); idx++) {
        auto result = results[idx];
        auto competition = competitions[idx];
        auto homeTeam = competition[0];
        auto awayTeam = competition[1];
        auto winningTeam = (result == HOME_TEAM_WON) ? homeTeam : awayTeam;

        updateScores(winningTeam, 3, teams, currentBestTeams);
    }

    return *currentBestTeams.begin();
}
