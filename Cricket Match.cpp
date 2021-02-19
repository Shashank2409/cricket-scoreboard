#include<bits/stdc++.h>
using namespace std;

string input_file_path = "input.txt" , output_file_path = "output.txt";

class Player{
	public:
	string name;
	int currentScore;
	bool playing;
	
	Player(){
		
	}
	
	Player(string name){
		this -> name = name;
		currentScore = 0;
		playing = false;
	}
	
	void addScore(int score){
		this -> currentScore += score;
	}
	
	int getScore(){
		return this -> currentScore;
	}
	void changeCrease(){
		this -> playing = !(this -> playing);
	}
	string getName(){
		return this->name;
	}
	bool isPlaying(){
		return this->playing;
	}
};

class Team{
	public:
		
	const static int noOfPlayersInATeam = 11;
	string name;
	vector<Player*> players;
	
	Team(){
		name = "";
	}
	
	Team(string name){
		this -> name = name;
	}
	
	void addTeamPlayer(Player *player){
		this -> players.push_back(player);
	}
	
	void printAllPlayers(){
		for(int i = 0; i < players.size(); i++){
			cout<<players[i] -> name<<" ";
		}
		cout<<endl;
	}
	pair<Player* , Player*> nextTwoPlayers(int currentWickets){
		pair<Player* , Player*> currentPlayers;
		if(currentWickets <= 9){
			currentPlayers.first = this -> players[currentWickets];
			currentPlayers.second = this -> players[currentWickets + 1];
		}
		return currentPlayers;
	}
	Player* getNextPlayer(int player_no){
		if(player_no < 10){
			return this -> players[player_no + 1];	
		}
		return NULL;
	}
};


class Ball{
	public:
	int score;
	Player* player;
	bool wicket , NB , wide;
	
	Ball(){
		this->score = 0;
		this->wicket = false;
		this->wide = false;
		this->NB = false;
	}
	void updateScore(int score){
		this -> score = score;
	}
	void wicketBall(){
		this->wicket = true;
	}
	void wideBall(){
		this->wide = true;
	}
	void noBall(){
		this->NB = true;
	}
};

class Over{
	public:
	vector<Ball*> balls;

	void addBall(Ball *ball){
		(this->balls).push_back(ball);
	}
};


class Inning{
	public:
	vector<Over*>overs;
	int currentScore , currentWickets , extras , ballsPlayed , totalBalls;
	Team* playingTeam;
	pair<Player* , Player*> currentPlayers;

	Inning(int total_overs , Team* playingTeam){
		currentScore = 0;
		currentWickets = 0;
		this -> playingTeam = playingTeam;
		currentPlayers = playingTeam -> nextTwoPlayers(this -> currentWickets);
		this -> extras = 0;
		this -> ballsPlayed = 0;
		this -> totalBalls = 0;
	}
	
	void addScore(int score){
		this -> currentScore += score;
//		cout<<"current Score\n";
		if((currentPlayers.first) -> isPlaying() == true){
			(currentPlayers.first) -> addScore(score);
		}
		else{
			(currentPlayers.second) -> addScore(score);
		}
	}
	
	int getTotalScore(){
		return this -> currentScore;
	}
	
	void addWicket(){
		this -> currentWickets++;
		if((currentPlayers.first) -> playing == true){
			currentPlayers.first = playingTeam -> getNextPlayer(this->currentWickets);
		}
		else{
			currentPlayers.second = playingTeam -> getNextPlayer(this->currentWickets);
		}
	}
	
	int getWickets(){
		return this -> currentWickets;
	}
	
	int getTotalBallsInInnings(){
		return this -> totalBalls;
	}
	
	pair<Player* , Player*> getCurrentPlayers(){
		return this->currentPlayers;
	}
	
	
	void endOver(Over *over){
		(currentPlayers.first) -> changeCrease();
		(currentPlayers.second) -> changeCrease();
		(this->overs).push_back(over);
	}
	
	/*
		Return pair of current score. 1st int is strikers end’s score and 2nd int is non-strikers end’s score
	*/
	pair<int , int> getCurrentScore(){
		pair<int , int> currentScores;
		if((currentPlayers.first) -> playing == true){
			currentScores.first = (currentPlayers.first) -> currentScore;
		currentScores.second = (currentPlayers.second) -> currentScore;
		}
		else{
		
		}
	}
};	

class Match{
	public:
	vector<Inning*> innings;
	pair<Team* , Team*> teams;
	int innings_played;
	
	Match(Team* team1 , Team* team2){
		(this -> teams).first = team1;
		(this -> teams).second = team2;
		this -> innings_played = 0;
	}
	
	
	void addInning(Inning *inning){
		(this -> innings).push_back(inning);
	}
};

int main(){
	
	ifstream in(input_file_path.c_str());
    ofstream out(output_file_path.c_str()); 
	
	/*ADMIN INPUT*/
	cout<<"Enter the team names\n";
	string team1_name , team2_name;
	in>>team1_name>>team2_name;	
	
	cout<<"Enter "<<team1_name<<" playing 11 names\n";
	Team *team1 = new Team(team1_name);
	for(int i = 0; i < team1 -> noOfPlayersInATeam; i++){
		string player_name;
		in>>player_name;
		cout<<player_name<<endl;
				
		Player *player = new Player(player_name);
		team1 -> addTeamPlayer(player);
	}
	
	cout<<"Enter "<<team2_name<<" playing 11 names\n";
	Team *team2 = new Team(team2_name);
	for(int i = 0; i < team2 -> noOfPlayersInATeam; i++){
		string player_name;
		in>>player_name;
		cout<<player_name<<endl;
		
		Player *player = new Player(player_name);
		team2 -> addTeamPlayer(player);
	}
	
	int total_overs = 0 , total_innings = 0;
	cout<<"Enter the no of innings in 1 match\n";
	in>>total_innings;
	
	cout<<"Enter the no of overs in 1 innings\n";
	in>>total_overs;
	
	int total_balls_played = 0;
	Inning *currentInning;
	Over *currentOver;
	Ball *currentBall;
	Match *match = new Match(team1 , team2);

	/*COMMENTATOR AND VIEWER INPUT*/
	cout<<"Print\n1 for 'Ball played'\n2 for getting the current score and wickets\n3 for getting the current players\n";
	
	while(1){
		int query_type;
		in>>query_type;
		
//		cout<<"query\n";
//		cout<<query_type<<endl;
		
		if(query_type == 1){
//			cout<<"query 1\n";
			if(total_balls_played == 0){
				Inning *inning1 = new Inning(total_overs , team1);
				match -> addInning(inning1);
				currentInning = inning1;
			}
			else if(total_balls_played == total_overs*6){
				Inning *inning2 = new Inning(total_overs , team2);
				match -> addInning(inning2);
				currentInning = inning2;
			}
			else if(total_balls_played >=  total_overs*6*2){
				cout<<"MATCH IS OVER!!\n";
				continue;
			}
			
			Ball *ball = new Ball();
			currentBall = ball;
			
			if(total_balls_played % 6 == 0){
				if(total_balls_played != 0){
					currentInning -> endOver(currentOver);	
				}
				currentOver = new Over();
				
			}
			
			string ball_score;
			in>>ball_score;
			
			if(ball_score == "Wicket"){
				currentInning -> addWicket();
				total_balls_played++;
				ball->wicketBall();
			}
			else if(ball_score == "Wide"){
				currentInning -> addScore(1);
				ball->wideBall();
			}
			else if(ball_score == "NB"){
				currentInning -> addScore(1);
				ball->noBall();
			}
			else{
				int score = ball_score[0] - '0';
//				cout<<"score "<<score<<endl;
				currentInning -> addScore(score);
				total_balls_played++;	
//				cout<<"yes\n";
				ball->updateScore(score);	
//				cout<<"yes\n";
			}
			currentOver->addBall(currentBall);
//			cout<<"yes\n";
		}
		
		else if(query_type == 2){
//			cout<<"query2\n";
			int score = currentInning -> getTotalScore() , wickets = currentInning -> getWickets();
			cout<<score<<"/"<<wickets<<endl;
		}
		
		else if(query_type == 3){
			pair<Player* , Player*> currentPlayers = currentInning->getCurrentPlayers();
			cout<<(currentPlayers.first)->getName();
			if((currentPlayers.first)->isPlaying() == true){
				cout<<"*\n";
			}
			else{
				cout<<"\n";
			}
			
			cout<<(currentPlayers.second)->getName();
			if((currentPlayers.second)->isPlaying() == true){
				cout<<"*";
			}
			else{
				cout<<"\n";
			}
			
		}
		
		else{
			cout<<"END\n";
			break;
		}
	}
}

/*
INPUT FORMAT

Enter the team names - 
Ind 
Eng
Enter Ind team players in playing order - 
a
b
c
d
e
f
g
h
i
j
k
Enter Eng team players in playing order- 
l
m
n
o
p
q
r
s
t
u
v
Enter no of overs in 1 innings - 12
Which team is batting first? Ind

1 for "Ball played" 
2 for getting the current score and wickets
3 for getting the current players and scores

1 2
2
1 4
1 Wicket
1 2
3
1 Wide
1 3

OUTPUT
2/0
b 2*
c 0

*/



