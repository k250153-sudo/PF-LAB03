#include <stdio.h>

int totalscore(int rounds, int scores[][100], int team) {
    if (rounds == -1) return 0;
    return scores[team][rounds] + totalscore(rounds - 1, scores, team);
}

int main() {
    printf("Enter total teams: ");
    int teams;
    scanf("%d",&teams);
    printf("Enter total rounds: ");
    int rounds;
    scanf("%d",&rounds);
    int scores[teams][100]; // Using 100 instead of rounds due to compiler issues.
    for (int team = 0; team < teams; team++) {
        for (int round = 0; round < rounds; round++) {
            printf("Enter score for team %d of round %d: ", team+1, round+1);
            scanf("%d", &scores[team][round]);
        }
    }
    printf("Enter the score threshold: ");
    int threshold;
    int score;
    scanf("%d",&threshold);
    for (int team = 0; team < teams; team++) {
        score=totalscore(rounds-1,scores,team);
        printf("Team %d score:%d \n",team+1,score);
        if (score<threshold) {
            printf("Team %d is below threshold.\n",team+1);
        }
    }
}


