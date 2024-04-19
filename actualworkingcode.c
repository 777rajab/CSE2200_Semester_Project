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

void printPlayers(struct CricketPlayer players[], int numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    printf("ID: %d Team: %s Name: %s\n", players[i].id, players[i].team,
           players[i].name);
  }
}

// temporary menu, needs to be updated to look more scoreboard like
void printMenu(struct Match *match) {
  printf("/================================/\n");
  printf("CPL 2024 Interactive Scoreboard\n");
  printf("          MENU         \n");
  printf("/================================/\n");
  printf("Batting Team: %s\n", match->battingTeam.name);
  printf("Bowling Team: %s\n", match->bowlingTeam.name);
  printf("Current Over: %d\n", match->over.overNum);
  printf("Balls Bowled: %d\n", match->over.balls);
  printf("Runs in Over: %d\n", match->over.Runs);
  printf("Wickets in Over: %d\n", match->over.Wickets);
}

// this is where everything is happening basically
void startOver(struct Match *match, struct CricketPlayer players[],
               int numPlayers, struct CricketPlayer *batter1,
               struct CricketPlayer *batter2, struct Sponsor sponsors[]) {
  match->over.overNum++;
  match->over.balls = 0;
  match->over.Runs = 0;
  match->over.Wickets = 0;

  printf("Starting Over %d\n", match->over.overNum);

  // selecting bowler
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
  // some error checking, need to let them re-enter if wrong, need to do this
  // for all error-prone stuff
  if (bowlerID < 1 || bowlerID > numPlayers) {
    printf("Invalid player.\n");
  } else {
    printf("Selected Bowler: %s\n", players[bowlerID - 1].name);

    // add runs and wickets for each ball in the over
    for (int ball = 1; ball <= 6; ball++) {
      int runs;
      printf("Enter runs scored on ball %d: ", ball);
      scanf("%d", &runs);

      // select the batsman who scored the runs
      int batsmanID;
      printf("Which batsman scored %d runs?\n", runs);
      printf("ID\tName\n");
      printf("%d\t%s\n", batter1->id, batter1->name);
      printf("%d\t%s\n", batter2->id, batter2->name);
      printf("Enter the ID of the batsman: ");
      scanf("%d", &batsmanID);

      // error stuff
      if (batsmanID != batter1->id && batsmanID != batter2->id) {
        printf("Invalid player.\n");
        continue;
      }

      // update runs for batsman
      if (batsmanID == batter1->id) {
        batter1->runsS += runs;
        batter1->ballsF++;
      } else {
        batter2->runsS += runs;
        batter2->ballsF++;
      }

      // update match stats
      match->over.Runs += runs;
      match->over.balls++;

      // boundaries, gonna need to check the 4 to see if they ran 4 times or if
      // it was actual 4
      if (runs == 4 || runs == 6) {
        match->mEvent.boundaries++;
        printSponsor(sponsors);
      }
      if (runs == 0) {
        int wicket;
        printf("Was there a wicket on ball %d? (1 for yes, 0 for no): ", ball);
        scanf("%d", &wicket);
        if (wicket == 1) {
          match->over.Wickets++;
          match->mEvent.wickets++;
          printSponsor(sponsors);

          // updating batting order after a wicket
          if (batter1->id == batsmanID) {
            // if batter1 got out, replace it with the next player
            batter1 = (batter1 == &players[MAX_PLAYERS - 1]) ? &players[0]
                                                             : batter1 + 1;
          } else {
            // if batter2 got out, replace it with the next player
            batter2 = (batter2 == &players[MAX_PLAYERS - 1]) ? &players[0]
                                                             : batter2 + 1;
          }

          // making sure both batters arent the same
          if (batter1 == batter2) {
            batter2 = (batter2 == &players[MAX_PLAYERS - 1]) ? &players[0]
                                                             : batter2 + 1;
          }
        }
      }
    }
  }
}

int main() {
  // structs
  struct Match match;
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
    printf("1. Start New Over\n");
    printf("2. End Match\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      startOver(&match, players2, MAX_PLAYERS, batter1, batter2, sponsors);
      break;
    case 2:
      printf("Match over.\n");
      break;
    default:
      printf("Invalid choice.\n");
      break;
    }
  } while (choice != 2);

  return 0;
}