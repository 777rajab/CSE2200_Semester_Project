// big shoutout to chat for helping me write this, couldnt have done it without you <3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 11
#define MAX_NAME_LENGTH 50
#define MAX_TEAM_LENGTH 50
#define MAX_SPONSORS 5

// Function to introduce a delay
void delay (unsigned int mseconds)
{
	time_t go=mseconds + clock();
	while (go>clock());
}

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
  int teamSwitched; // Flag to indicate if teams are switched
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

// Function to initialize players for Team A
void initializeTeamAPlayers(struct CricketPlayer players[]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].id = i + 1;
        strcpy(players[i].team, "Team A");

        // Assign player names for Team A
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

        // Initialize other player attributes
        players[i].runsS = 0;
        players[i].runsC = 0;
        players[i].ballsF = 0;
        players[i].ballsB = 0;
        players[i].boundaries = 0;
        players[i].wickets = 0;
        players[i].strikeR = 0.0;
        players[i].econR = 0.0;
    }
}

// Function to initialize players for Team B
void initializeTeamBPlayers(struct CricketPlayer players[]) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        players[i].id = i + 1;
        strcpy(players[i].team, "Team B");

        // Assign player names for Team B
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

        // Initialize other player attributes
        players[i].runsS = 0;
        players[i].runsC = 0;
        players[i].ballsF = 0;
        players[i].ballsB = 0;
        players[i].boundaries = 0;
        players[i].wickets = 0;
        players[i].strikeR = 0.0;
        players[i].econR = 0.0;
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

  printf("The CPL Final is proudly sponsored by %s!\n", sponsors[sponsorIndex].name);
  printf("%s\n", sponsors[sponsorIndex].slogan);
  delay(2500);
  system("cls");
}

// menu
void printMenu(struct Match *match) {
  printf("/===========================================/\n");
  printf("         CPL 2024 Interactive Scoreboard\n");
  printf("/===========================================/\n");
  printf("Batting Team: %s\t\tBowling Team: %s\n", match->battingTeam.name, match->bowlingTeam.name);
  printf("Runs in Over: %d\t\t\tWickets in Over: %d\n", match->over.Runs, match->over.Wickets);
  printf("Total Runs: %d\t\t\tCurrent Over: %d\n", match->battingTeam.score, match->over.overNum);
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
    system("cls");
    // Display player statistics based on player ID
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == playerID && strcmp(players[i].team, match->battingTeam.name) == 0) {
            printf("Let's make some noise for %s!\n", players[i].name);
            printf("Runs Scored: %d\n", players[i].runsS);
            printf("Boundaries: %d\n", players[i].boundaries);
            printf("Balls Faced: %d\n", players[i].ballsF);
            printf("Strike Rate: %.2f\n", players[i].strikeR);
            delay(2500);
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
	system("cls");
    // Display player statistics based on player ID
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].id == playerID && strcmp(players[i].team, match->bowlingTeam.name) == 0) {
            printf("Let's make some noise for %s!\n", players[i].name);
            printf("Wickets: %d\n", players[i].wickets);
            printf("Balls Bowled: %d\n", players[i].ballsB);
            printf("Runs Conceded: %d\n", players[i].runsC);
            printf("Economy Rate: %.2f\n", players[i].econR);
            delay(2500);
            break;
        }
    }
}

// Function to display team statistics
void showTeamStats(struct CricketPlayer players[], int numPlayers, const char *teamName, struct Match *match) {
	system("cls");
    int totalRuns = 0;
    int totalWickets = 0;
    int totalOvers = match->over.overNum;

    // Calculate total runs, wickets, and overs
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].team, teamName) == 0) {
            totalRuns += players[i].runsS;
            totalWickets += players[i].wickets;
        }
    }

    // Display team statistics
    printf("Let's have a look at %s's stats!\n\n", teamName);
    printf("Total Runs: %d\n", totalRuns);
    printf("Total Wickets: %d\n", totalWickets);
    printf("Total Overs Bowled: %d\n", totalOvers);
    printf("Runs in Current Over: %d\n", match->over.Runs);
    printf("Wickets in Current Over: %d\n", match->over.Wickets);
    delay(2500);
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
    delay(2500);
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
    delay(2500);
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

// Function to check if switching of teams is required
void checkTeamSwitch(struct Match *match, int numPlayers, int *batter1Index, int *batter2Index) {
    // Check if 20 overs have been bowled or all batters are out
    if (match->over.Wickets == 10 || match->over.overNum == 20) {
    	
    	if (match->battingTeam.score < match->bowlingTeam.score && match->teamSwitched == 1) {
			printf("%s wins the match!\n", match->bowlingTeam.name);
			delay(3000);
		} else {
			// The match ends in a draw or tie
			printf("The match ends in a draw!\n");
		}
    	
        // Swap batting and bowling teams
        struct Team temp = match->battingTeam;
        match->battingTeam = match->bowlingTeam;
        match->bowlingTeam = temp;

        *batter1Index = 0;
        *batter2Index = 1;

        // Reset over count
        match->over.overNum = 0;
        
        // Set the flag to indicate teams are switched
        match->teamSwitched = 1;
    }
}

void startOver(struct Match *match, struct CricketPlayer battingPlayers[], struct CricketPlayer bowlingPlayers[],
               int numPlayers, int *batter1Index, int *batter2Index, struct Sponsor sponsors[]) {
	match->over.overNum++; // Increment the over number after completing the over loop
    printf("Starting Over %d\n", match->over.overNum);

    match->over.Runs = 0; // Reset runs for the over
    match->over.balls = 0; // Reset balls for the over

    // Selecting bowler
    printf("Select the bowler:\n");
    printf("ID\tName\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(bowlingPlayers[i].team, match->bowlingTeam.name) == 0) {
            printf("%d\t%s\n", bowlingPlayers[i].id, bowlingPlayers[i].name);
        }
    }
    int bowlerID;
    printf("Enter the ID of the bowler: ");
    scanf("%d", &bowlerID);
    // Error checking
    if (bowlerID < 1 || bowlerID > numPlayers) {
        printf("Invalid player.\n");
        delay(1000);
		return;
    } else {
        printf("Selected Bowler: %s\n", bowlingPlayers[bowlerID - 1].name);
        delay(1000);
        system("cls");
	}
	// Add runs and wickets for each ball in the over
    for (int ball = 1; ball <= 6; ball++) {
	    int runs;
	    printf("Enter runs scored on ball %d: ", ball);
	    scanf("%d", &runs);
		
		// Check if the batting team has surpassed the bowling team's runs
		if (match->battingTeam.score > match->bowlingTeam.score && match->teamSwitched == 1) {
			printf("Congratulations! %s has won the match!\n", match->battingTeam.name);
            return;
		}
		
	    // Select the batsman who scored the runs
	    int batsmanID;
	    printf("Which batsman scored %d runs?\n", runs);
	    printf("ID\tName\n");
	    printf("%d\t%s\n", battingPlayers[*batter1Index].id, battingPlayers[*batter1Index].name);
	    printf("%d\t%s\n", battingPlayers[*batter2Index].id, battingPlayers[*batter2Index].name);
	    printf("Enter the ID of the batsman: ");
	    scanf("%d", &batsmanID);
	
	    // Error handling
	    if (batsmanID != battingPlayers[*batter1Index].id && batsmanID != battingPlayers[*batter2Index].id) {
	        printf("Invalid player.\n");
	        continue;
	    }
	
	    // Update runs for batsman
	    if (batsmanID == battingPlayers[*batter1Index].id) {
	        battingPlayers[*batter1Index].runsS += runs;
	        battingPlayers[*batter1Index].ballsF++;
	        battingPlayers[*batter1Index].strikeR = calculateStrikeRate(battingPlayers[*batter1Index].runsS, battingPlayers[*batter1Index].ballsF);
	    } else {
	        battingPlayers[*batter2Index].runsS += runs;
	        battingPlayers[*batter2Index].ballsF++;
	        battingPlayers[*batter2Index].strikeR = calculateStrikeRate(battingPlayers[*batter2Index].runsS, battingPlayers[*batter2Index].ballsF);
	    }
	            
	    // Ask if the runs constitute a boundary if it's 4
	    if (runs == 4) {
	        int isBoundaryRun;
	        printf("Did the batsman hit a boundary? (1 for yes, 0 for no): ");
	        scanf("%d", &isBoundaryRun);
	        if (isBoundaryRun) {
	            match->mEvent.boundaries++;
	            system("cls");
	            printf("Fantastic! That's a boundary!\n\n");
	            printSponsor(sponsors);
	        }
	    }
	    // Ask if the runs constitute a boundary if it's 6
	    else if (runs == 6) {
	        match->mEvent.boundaries++;
	        system("cls");
	        printf("Wow! That's a massive SIX!\n\n");
	        printSponsor(sponsors);
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
	            system("cls");
	            printf("Out! What a wicket!\n\n");
	            printSponsor(sponsors);
						
				if (match->over.Wickets == 10) {
	         		printf("All out! End of innings.\n");
	         		delay(2500);
	         				
	         		if (match->battingTeam.score < match->bowlingTeam.score && match->teamSwitched == 1) {
						printf("%s wins the match!\n", match->bowlingTeam.name);
						delay(3000);
					} else {
						// The match ends in a draw or tie
						printf("The match ends in a draw!\n");
					}
	         		// Check if to switch teams
	        		checkTeamSwitch(match, numPlayers, batter1Index, batter2Index);
	            	return;
				}
	            // Update batting order after a wicket
	            if (batsmanID == battingPlayers[*batter1Index].id) {
	                *batter1Index = (*batter1Index == numPlayers - 1) ? 0 : *batter1Index + 1;
	            } else {
	                *batter2Index = (*batter2Index == numPlayers - 1) ? 0 : *batter2Index + 1;
	            }
	
	            // Ensure both batters aren't the same
	            if (*batter1Index == *batter2Index) {
	                *batter2Index = (*batter2Index == numPlayers - 1) ? 0 : *batter2Index + 1;
	            }
	        }
	    }
	    printf("\n");
	}   

    // Update economy rate for the bowler
    bowlingPlayers[bowlerID - 1].ballsB += match->over.balls;
    bowlingPlayers[bowlerID - 1].runsC += match->over.Runs;
    bowlingPlayers[bowlerID - 1].econR = calculateEconomyRate(bowlingPlayers[bowlerID - 1].runsC, bowlingPlayers[bowlerID - 1].ballsB);
        
    // Update total runs for batting team
    match->battingTeam.score += match->over.Runs;
        
    // Check if to switch teams
    checkTeamSwitch(match, numPlayers, batter1Index, batter2Index);
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
	struct Sponsor sponsors[MAX_SPONSORS];

	// teams, sponsors
	initializeTeams(&match);
	initializeTeamAPlayers(players1); // Initialize players for Team A
	initializeTeamBPlayers(players2); // Initialize players for Team B
	initializeSponsors(sponsors);

	int batter1Index = 0;
	int batter2Index = 1;

	printf("\n");

	int choice;

	do {
	system("cls");
    printMenu(&match);
    scanf("%d", &choice);
	system("cls");
    switch (choice) {
		case 1:
	      startOver(&match, players1, players2, MAX_PLAYERS, &batter1Index, &batter2Index, sponsors);
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
	                showTeamStats(players1, MAX_PLAYERS, match.battingTeam.name, &match);
	                break;
	            case 2:
	                showTeamStats(players2, MAX_PLAYERS, match.bowlingTeam.name, &match);
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
		
		// Check if teams are switched
        if (match.teamSwitched) {
        	system("cls");
            printf("Teams have been switched! It's time for a new innings!\n\n");
            
            // Print the runs scored by the previous batting team
            printf("%s just scored %d runs!\n\n", match.bowlingTeam.name, match.bowlingTeam.score);
			
			// Calculate the runs needed to win
			int runsNeeded = match.bowlingTeam.score + 1;

			// Display the runs needed for the new batting team to win
			printf("%s needs %d runs to win in 20 overs! Can they do it?", match.battingTeam.name, runsNeeded);
			
			delay(2500);
			system("cls");
            // Create a new loop for the new team to start batting
            do {
                // Print menu for the new batting team
                printMenu(&match);
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        startOver(&match, players2, players1, MAX_PLAYERS, &batter1Index, &batter2Index, sponsors);
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
	                			showBattingPlayerStatistics(players2, MAX_PLAYERS, &match);
	                			break;
	            			case 2:
	                			showBowlingPlayerStatistics(players1, MAX_PLAYERS, &match);
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
				                showTeamStats(players2, MAX_PLAYERS, match.battingTeam.name, &match);
				                break;
				            case 2:
				                showTeamStats(players1, MAX_PLAYERS, match.bowlingTeam.name, &match);
				                break;
				            default:
				                printf("Invalid choice.\n");
				                break;
				        }
				        break;
						}
                    case 4:
                        printBattingTeamScoreboard(players2, MAX_PLAYERS, match.battingTeam.name);
                        break;
                    case 5:
                        printBowlingTeamScoreboard(players1, MAX_PLAYERS, match.bowlingTeam.name);
                        break;
                    case 6:
                        printf("End Match\n");
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
            } while (choice != 6); // Loop until the match ends
        }
	} while (choice != 6);

	return 0;
}
