// big shoutout to chat for helping me write this, couldnt have done it without you <3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 11
#define MAX_NAME_LENGTH 50
#define MAX_TEAM_LENGTH 50
#define MAX_SPONSORS 5

struct CricketPlayer {
  int id;
  char team[MAX_TEAM_LENGTH];
  char name[MAX_NAME_LENGTH];
  int runsS, runsC;
  int ballsF, ballsB;
  int boundaries;
  int wickets;
  float strikeR;
  float econR;
};

struct Team {
  char name[25];
  int score;
};

struct Match_Event {
  int wickets;
  int boundaries;
  struct CricketPlayer *player;
};

struct Over {
  int overNum;
  int balls;
  int Runs;
  int Wickets;
};

struct Match {
  struct Team battingTeam;
  struct Team bowlingTeam;
  int currOver;
  int currRuns;
  struct Match_Event mEvent;
  int matchResults;
  struct Over over;
};

struct Sponsor {
  char name[25];
  char slogan[75];
};

// batting and bowling team
void initializeTeams(struct Match *match) {
  strcpy(match->battingTeam.name, "Team A");
  match->battingTeam.score = 0;

  strcpy(match->bowlingTeam.name, "Team B");
  match->bowlingTeam.score = 0;
}

// players of each team
void initializePlayers(struct CricketPlayer players[], const char *teamName) {
  for (int i = 0; i < MAX_PLAYERS; i++) {
    players[i].id = i + 1;
    strcpy(players[i].team, teamName);
    
    players[i].runsS = 0;
    players[i].runsC = 0;
    players[i].ballsF = 0;
    players[i].ballsB = 0;
    players[i].boundaries = 0;
    players[i].wickets = 0;
    players[i].strikeR = 0.0;
    players[i].econR = 0.0;
    
    if (strcmp(teamName, "Team A") == 0) {
      switch (i) {
      case 0:
        strcpy(players[i].name, "John Smith");
        break;
      case 1:
        strcpy(players[i].name, "David Johnson");
        break;
      case 2:
        strcpy(players[i].name, "Michael Williams");
        break;
      case 3:
        strcpy(players[i].name, "James Brown");
        break;
      case 4:
        strcpy(players[i].name, "Robert Jones");
        break;
      case 5:
        strcpy(players[i].name, "William Miller");
        break;
      case 6:
        strcpy(players[i].name, "Joseph Davis");
        break;
      case 7:
        strcpy(players[i].name, "Daniel Garcia");
        break;
      case 8:
        strcpy(players[i].name, "Charles Rodriguez");
        break;
      case 9:
        strcpy(players[i].name, "Thomas Martinez");
        break;
      case 10:
        strcpy(players[i].name, "Christopher Hernandez");
        break;
      }
    } else if (strcmp(teamName, "Team B") == 0) {
      switch (i) {
      case 0:
        strcpy(players[i].name, "Matthew Wilson");
        break;
      case 1:
        strcpy(players[i].name, "Andrew Anderson");
        break;
      case 2:
        strcpy(players[i].name, "Edward Taylor");
        break;
      case 3:
        strcpy(players[i].name, "Joshua Moore");
        break;
      case 4:
        strcpy(players[i].name, "Benjamin Jackson");
        break;
      case 5:
        strcpy(players[i].name, "Samuel Harris");
        break;
      case 6:
        strcpy(players[i].name, "Jonathan Martin");
        break;
      case 7:
        strcpy(players[i].name, "Nathan Thompson");
        break;
      case 8:
        strcpy(players[i].name, "Ryan White");
        break;
      case 9:
        strcpy(players[i].name, "Timothy Lee");
        break;
      case 10:
        strcpy(players[i].name, "Adam Scott");
        break;
      }
    }
  }
}

// sponsors
void initializeSponsors(struct Sponsor sponsors[]) {
  strcpy(sponsors[0].name, "Banks Beer");
  strcpy(sponsors[0].slogan, "The beer of champions!");

  strcpy(sponsors[1].name, "Riaz Computer");
  strcpy(sponsors[1].slogan, "Your tech partner!");

  strcpy(sponsors[2].name, "Digicel");
  strcpy(sponsors[2].slogan, "Connecting you, anywhere!");

  strcpy(sponsors[3].name, "Bounty Supermarket");
  strcpy(sponsors[3].slogan, "More savings, every day!");

  strcpy(sponsors[4].name, "Exxon Mobil");
  strcpy(sponsors[4].slogan, "Energy lives here!");
}

// random sponsor generator
void printSponsor(struct Sponsor sponsors[]) {
  srand(time(NULL));
  int sponsorIndex = rand() % MAX_SPONSORS;

  printf("Sponsored by: %s\n", sponsors[sponsorIndex].name);
  printf("Slogan: %s\n", sponsors[sponsorIndex].slogan);
}

// menu
void printMenu(struct Match *match) {
  printf("/===========================================/\n");
  printf("         CPL 2024 Interactive Scoreboard\n");
  printf("/===========================================/\n");
  printf("Batting Team: %s\t\tBowling Team: %s\n", match->battingTeam.name, match->bowlingTeam.name);
  printf("Current Over: %d\t\t\tBalls Bowled: %d\n", match->over.overNum, match->over.balls);
  printf("Runs in Over: %d\t\t\tWickets in Over: %d\n", match->over.Runs, match->over.Wickets);
  printf("/===========================================/\n");
  printf("                MENU                \n");
  printf("/===========================================/\n");
  printf("1. Start New Over\n");
  printf("2. Show Player Statistics\n");
  printf("3. Show Team Statistics\n");
  printf("4. Show Batting Team Scoreboard\n");
  printf("5. Show Bowling Team Scoreboard\n");
  printf("6. End Match\n");
  printf("Enter your choice: ");
}

// Function to display player statistics for the batting team
void showBattingPlayerStatistics(struct CricketPlayer players[], int numPlayers, struct Match *match) {
    printf("Select player from the Batting Team:\n");
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, match->battingTeam.name) == 0) {
            printf("%d\t%s\n", players[i].id, players[i].name);
        }
    }

    int playerID;
    printf("Enter the ID of the player: ");
    scanf("%d", &playerID);

    // Display player statistics based on player ID
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == playerID && strcmp(players[i].team, match->battingTeam.name) == 0) {
            printf("Player Name: %s\n", players[i].name);
            printf("Runs Scored: %d\n", players[i].runsS);
            printf("Balls Faced: %d\n", players[i].ballsF);
            printf("Boundaries: %d\n", players[i].boundaries);
            printf("Strike Rate: %.2f\n", players[i].strikeR);
            break;
        }
    }
}

// Function to display player statistics for the bowling team
void showBowlingPlayerStatistics(struct CricketPlayer players[], int numPlayers, struct Match *match) {
    printf("Select player from the Bowling Team:\n");
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, match->bowlingTeam.name) == 0) {
            printf("%d\t%s\n", players[i].id, players[i].name);
        }
    }

    int playerID;
    printf("Enter the ID of the player: ");
    scanf("%d", &playerID);

    // Display player statistics based on player ID
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == playerID && strcmp(players[i].team, match->bowlingTeam.name) == 0) {
            printf("Player Name: %s\n", players[i].name);
            printf("Runs Conceded: %d\n", players[i].runsC);
            printf("Balls Bowled: %d\n", players[i].ballsB);
            printf("Wickets: %d\n", players[i].wickets);
            printf("Economy Rate: %.2f\n", players[i].econR);
            break;
        }
    }
}

// Function to display team statistics
void showTeamStats(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    int totalRuns = 0;
    int totalWickets = 0;
    int totalOvers = 0;

    // Calculate total runs, wickets, and overs
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            totalRuns += players[i].runsS;
            totalWickets += players[i].wickets;
            // Assuming each player has bowled 6 balls in an over
            totalOvers += players[i].ballsB / 6;
        }
    }

    // Display team statistics
    printf("Team: %s\n", teamName);
    printf("Total Runs: %d\n", totalRuns);
    printf("Total Wickets: %d\n", totalWickets);
    printf("Total Overs Bowled: %d\n", totalOvers);
}

// Function to print batting team scoreboard inline
void printBattingTeamScoreboard(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    printf("Batting Team Scoreboard: %s\n", teamName);
    int totalRuns = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            printf("%s runs: %d balls faced: %d\n", players[i].name, players[i].runsS, players[i].ballsF);
            totalRuns += players[i].runsS;
            printf("\n");
        }
    }
    printf("Total Runs: %d\n", totalRuns);
}

// Function to print bowling team scoreboard inline
void printBowlingTeamScoreboard(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    printf("Bowling Team Scoreboard: %s\n", teamName);
    int totalOvers = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            int oversBowled = players[i].ballsB / 6;
            printf("%s balls bowled: %d runs conceded: %d\n", players[i].name, players[i].ballsB, players[i].runsC);
            totalOvers += oversBowled;
            printf("\n");
        }
    }
    printf("Total Overs Bowled: %d\n", totalOvers);
}

// Function to calculate strike rate for a batsman
float calculateStrikeRate(int runsScored, int ballsFaced) {
    if (ballsFaced == 0) {
        return 0.0; // Prevent division by zero
    }
    return ((float) runsScored / ballsFaced) * 100.0;
}

// Function to calculate economy rate for a bowler
float calculateEconomyRate(int runsConceded, int ballsBowled) {
    if (ballsBowled == 0) {
        return 0.0; // Prevent division by zero
    }
    float oversBowled = ballsBowled / 6.0; // Convert balls to overs
    return (float) runsConceded / oversBowled;
}

// Function to determine if the runs scored constitute a boundary
int isBoundary(int runs) {
    return (runs == 4 || runs == 6);
}

void startOver(struct Match *match, struct CricketPlayer players[],
               int numPlayers, struct CricketPlayer *batter1,
               struct CricketPlayer *batter2, struct Sponsor sponsors[]) {
    match->over.overNum++;
    match->over.balls = 0;
    match->over.Runs = 0;
    match->over.Wickets = 0;

    printf("Starting Over %d\n", match->over.overNum);

    // Selecting bowler
    printf("Select the bowler:\n");
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, match->bowlingTeam.name) == 0) {
            printf("%d\t%s\n", players[i].id, players[i].name);
        }
    }
    int bowlerID;
    printf("Enter the ID of the bowler: ");
    scanf("%d", &bowlerID);
    // Error checking
    if (bowlerID < 1 || bowlerID > numPlayers) {
        printf("Invalid player.\n");
    } else {
        printf("Selected Bowler: %s\n", players[bowlerID - 1].name);

        // Add runs and wickets for each ball in the over
        for (int ball = 1; ball <= 6; ball++) {
            int runs;
            printf("Enter runs scored on ball %d: ", ball);
            scanf("%d", &runs);

            // Ask if the runs constitute a boundary if it's 4
            if (runs == 4) {
                int isBoundaryRun;
                printf("Did the batsman hit a boundary? (1 for yes, 0 for no): ");
                scanf("%d", &isBoundaryRun);
                if (isBoundaryRun) {
                    match->mEvent.boundaries++;
                    printSponsor(sponsors);
                }
            }
            // Ask if the runs constitute a boundary if it's 6
            else if (runs == 6) {
                match->mEvent.boundaries++;
                printSponsor(sponsors);
            }

            // Select the batsman who scored the runs
            int batsmanID;
            printf("Which batsman scored %d runs?\n", runs);
            printf("ID\tName\n");
            printf("%d\t%s\n", batter1->id, batter1->name);
            printf("%d\t%s\n", batter2->id, batter2->name);
            printf("Enter the ID of the batsman: ");
            scanf("%d", &batsmanID);

            // Error handling
            if (batsmanID != batter1->id && batsmanID != batter2->id) {
                printf("Invalid player.\n");
                continue;
            }

            // Update runs for batsman
            if (batsmanID == batter1->id) {
                batter1->runsS += runs;
                batter1->ballsF++;
                batter1->strikeR = calculateStrikeRate(batter1->runsS, batter1->ballsF);
            } else {
                batter2->runsS += runs;
                batter2->ballsF++;
                batter2->strikeR = calculateStrikeRate(batter2->runsS, batter2->ballsF);
            }

            // Update match stats
            match->over.Runs += runs;
            match->over.balls++;

            // Check for a wicket
            if (runs == 0) {
                int wicket;
                printf("Was there a wicket on ball %d? (1 for yes, 0 for no): ", ball);
                scanf("%d", &wicket);
                if (wicket == 1) {
                    match->over.Wickets++;
                    match->mEvent.wickets++;
                    printSponsor(sponsors);

                    // Update batting order after a wicket
                    if (batter1->id == batsmanID) {
                        batter1 = (batter1 == &players[MAX_PLAYERS - 1]) ? &players[0] : batter1 + 1;
                    } else {
                        batter2 = (batter2 == &players[MAX_PLAYERS - 1]) ? &players[0] : batter2 + 1;
                    }

                    // Ensure both batters aren't the same
                    if (batter1 == batter2) {
                        batter2 = (batter2 == &players[MAX_PLAYERS - 1]) ? &players[0] : batter2 + 1;
                    }
                }
            }
        }

        // Update economy rate for the bowler
        players[bowlerID - 1].ballsB += match->over.balls;
        players[bowlerID - 1].runsC += match->over.Runs;
        players[bowlerID - 1].econR = calculateEconomyRate(players[bowlerID - 1].runsC, players[bowlerID - 1].ballsB);
    }
}

// Function to print batting team players
void printBattingTeam(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    printf("Batting Team: %s\n", teamName);
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            printf("%d\t%s\n", players[i].id, players[i].name);
        }
    }
}

// Function to print bowling team players
void printBowlingTeam(struct CricketPlayer players[], int numPlayers, const char *teamName) {
    printf("Bowling Team: %s\n", teamName);
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            printf("%d\t%s\n", players[i].id, players[i].name);
        }
    }
}

int main() {
  // structs
  struct Match match;
  match.over.overNum = 0;
  match.over.balls = 0;
  match.over.Runs = 0;
  match.over.Wickets = 0;
  struct CricketPlayer players1[MAX_PLAYERS];
  struct CricketPlayer players2[MAX_PLAYERS];
  struct CricketPlayer *batter1, *batter2;
  struct Sponsor sponsors[MAX_SPONSORS];

  // teams, sponsors
  initializeTeams(&match);
  initializePlayers(players1, match.battingTeam.name);
  initializePlayers(players2, match.bowlingTeam.name);
  initializeSponsors(sponsors);

  // first two batsmen
  batter1 = &players1[0];
  batter2 = &players1[1];

  printf("\n");

  int choice;

  do {
    // gonna add more stuff here, especially stuff to do with boosting player
    // self esteem we can add options to show this persons runs and that ones
    // wickets and the strikerate etc etc
    printMenu(&match);
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      startOver(&match, players2, MAX_PLAYERS, batter1, batter2, sponsors);
      break;
    case 2:
        {
		int teamChoice;
        printf("Select team:\n");
        printf("1. Batting Team\n");
        printf("2. Bowling Team\n");
        printf("Enter your choice: ");
        scanf("%d", &teamChoice);

        switch (teamChoice) {
            case 1:
                showBattingPlayerStatistics(players1, MAX_PLAYERS, &match);
                break;
            case 2:
                showBowlingPlayerStatistics(players2, MAX_PLAYERS, &match);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        	}
        break;
    	}
    case 3:
    {
        int teamChoice;
        printf("Select team:\n");
        printf("1. Batting Team\n");
        printf("2. Bowling Team\n");
        printf("Enter your choice: ");
        scanf("%d", &teamChoice);

        switch (teamChoice) {
            case 1:
                showTeamStats(players1, MAX_PLAYERS, match.battingTeam.name);
                break;
            case 2:
                showTeamStats(players2, MAX_PLAYERS, match.bowlingTeam.name);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
        break;
    }

    case 4:
      printBattingTeamScoreboard(players1, MAX_PLAYERS, match.battingTeam.name);
      break;
    case 5:
      printBowlingTeamScoreboard(players2, MAX_PLAYERS, match.bowlingTeam.name);
      break;
    case 6:
      printf("End Match\n");
      break;
    default:
      printf("Invalid choice.\n");
      break;
    }
  } while (choice != 6);

  return 0;
}
