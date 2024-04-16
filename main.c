#include <stdio.h>
#include <stdlib.h>

struct Team_1 {
    char name[25];
    int score;
};
struct Team_2 {
    char name[25];
    int score;
};

dis a test
struct Player{
    char name[50];
    int Runs_S, Runs_C;
    int Balls_F, Balls_B;
    int Wickets;
    float Strike_R;
    float Econ_R;
};


struct Match_Event{
    int Wickets;
    int Boundaries;
    struct Player x;
};


struct Over{
    struct Player x;
    int over_num;
    int Balls_B;
    int Runs;
    int Wickets;
} Over;


struct Match{
    struct Team_1 T1;
    struct Team_2 T2;
    int Curr_Over;
    int Curr_Runs;
    struct Match_Event M_Event;
    int Match_Results;
} Match;


struct Sponser{
    char name[25];
    char slogan[75];

} Sponser;

int main()
{
    printf("Hello world!\n");
    return 0;
}
