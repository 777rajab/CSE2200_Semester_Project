#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 11
#define MAX_NAME_LENGTH 50
#define MAX_TEAM_LENGTH 50

struct CricketPlayer {
    int id;
    char team[MAX_TEAM_LENGTH];
    char name[MAX_NAME_LENGTH];
    int Runs_S, Runs_C;
    int Balls_F, Balls_B;
    int Wickets;
    float Strike_R;
    float Econ_R;
};

struct Team_1 {
    char name[25];
    int score;
};

struct Team_2 {
    char name[25];
    int score;
};

struct Match_Event {
    int Wickets;
    int Boundaries;
    struct CricketPlayer *player; // Pointer to CricketPlayer struct
};

struct Over {
    struct CricketPlayer *player; // Pointer to CricketPlayer struct
    int over_num;
    int Balls_B;
    int Runs;
    int Wickets;
};

struct Match {
    struct Team_1 T1;
    struct Team_2 T2;
    int Curr_Over;
    int Curr_Runs;
    struct Match_Event M_Event;
    int Match_Results;
};

struct Sponsor {
    char name[25];
    char slogan[75];
};

int readPlayersFromFile(FILE *file, struct CricketPlayer players[], char teamName[]) {
    int numPlayers = 0;
    fscanf(file, "Team: %[^\n]\n", teamName);
    while (fscanf(file, "%d %[^\n]\n", &players[numPlayers].id, players[numPlayers].name) == 2) {
        strcpy(players[numPlayers].team, teamName);
        numPlayers++;
    }
    return numPlayers;
}

void printPlayers(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    printf("%s:\n", teamName);
    for (int i = 0; i < numPlayers; i++) {
        printf("ID: %d Team: %s Name: %s\n", players[i].id, players[i].team, players[i].name);
    }
}

int main() {
    FILE *file1 = fopen("team1.txt", "r");
    if (file1 == NULL) {
        perror("Error opening file1");
        return 1;
    }

    FILE *file2 = fopen("team2.txt", "r");
    if (file2 == NULL) {
        perror("Error opening file2");
        fclose(file1);
        return 1;
    }

    // Create arrays of structures to hold player information for both teams
    struct CricketPlayer players1[MAX_PLAYERS];
    struct CricketPlayer players2[MAX_PLAYERS];
    char teamName1[MAX_TEAM_LENGTH];
    char teamName2[MAX_TEAM_LENGTH];

    int numPlayers1 = readPlayersFromFile(file1, players1, teamName1);
    int numPlayers2 = readPlayersFromFile(file2, players2, teamName2);

    fclose(file1);
    fclose(file2);

    printPlayers(players1, numPlayers1, teamName1);
    printPlayers(players2, numPlayers2, teamName2);

    return 0;
}
