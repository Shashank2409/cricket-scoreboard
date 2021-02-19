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
	int score;
	Player* player;
	
	updateScore(int score){
		this -> score = score;
	}
};

class Over{
	vector<Ball*> balls;

	void addBall(Ball *ball){
		(this -> balls).push_back(ball);
	}
	int getScore(){
		for(int i = 0; i < balls.size(); i++){
			
		}
	}
};


class Inning{
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
//	void addOver(Over over , int currentScore , int currentWickets , Team team){
//		this -> overs.push_back(over);
//		this -> currentScore = currentScore;
//		this -> currentWickets += currentWicket;
//		this -> team = team;
//	}
	void addScore(int score){
		this -> currentScore += score;
		if((currentPlayers.first) -> playing == true){
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
	
	int getCurrentPlayers(){
		return this->currentPlayers;
	}
	
	
	void endOver(){
		(currentPlayers.first) -> changeCrease();
		(currentPlayers.second) -> changeCrease();
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
//	cin>>team1_name>>team2_name;
	in>>team1_name>>team2_name;	
	cout<<"Enter "<<team1_name<<" playing 11 names\n";
	Team *team1 = new Team(team1_name);
	for(int i = 0; i < team1 -> noOfPlayersInATeam; i++){
		string player_name;
//		cin>>player_name;
		in>>player_name;
		cout<<player_name<<endl;
				
		Player *player = new Player(player_name);
		team1 -> addTeamPlayer(player);
	}
	
	cout<<"Enter "<<team2_name<<" playing 11 names\n";
	Team *team2 = new Team(team2_name);
	for(int i = 0; i < team2 -> noOfPlayersInATeam; i++){
		string player_name;
//		cin>>player_name;
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
	Match *match = new Match(team1 , team2);
//	match -> addInning(inning);

	/*COMMENTATOR AND VIEWER INPUT*/
	cout<<"Print\n1 for 'Ball played'\n2 for getting the current score and wickets\n3 for getting the current players\n";
	
	while(1){
		int query_type;
		cin>>query_type;
		
		if(query_type == 1){
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
			else if(total_balls_played >=  total_over*6*2){
				cout<<"MATCH IS OVER!!\n";
				continue;
			}
			
			if(total_balls_played % 6 == 0){
				currentInnings -> endOver();
			}
			
			string ball_score;
			cin>>ball_score;
			
			if(ball_score == "Wicket"){
				currentInnings -> addWicket();
				total_balls_played++;
			}
			else if(ball_score == "Wide"){
				currentInnings -> addScore(1);
			}
			else if(ball_score == "NB"){
				currentInnings -> addScore(1);
			}
			else{
				int score = ball_score[0] - '0';
				currentInnings -> addScore(score);
				total_balls_played++;		
			}
		}
		
		else if(query_type == 2){
			int score = currentInning -> getTotalScore() , wickets = currentInning -> getWickets();
			cout<<score<<"/"<<wickets<<endl;
		}
		
		else if(query_type == 3){
			pair<Player* , Player*> currentPlayers = currentInning->getCurrentPlayers();
			cout<<(currentPlayers.first)->getName();
			if((currentPlayers.first)->isPlaying == true){
				cout<<"*\n";
			}
			else{
				cout<<"\n";
			}
			
			cout<<(currentPlayers.second)->getName();
			if((currentPlayers.second)->isPlaying == true){
				cout<<"*";
			}
			else{
				cout<<"\n";
			}
			
		}
		else{
			cout<<"INVALID QUERY\n";
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


*/



