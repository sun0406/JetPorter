
#include "gameUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <math.h>
int GameUtil::compute(Square* square, Player* player){

  double chi = player->getChi();
  double weight = player->getWeight();
  double teleporterEnergy = square->getTeleporterEnergy();
  double cannonPowder = square->getCannonPowder();

  double teleporterCompute = 0;
  double chi_round_down = floor(chi);
  for(double i = 0.0; i <= chi_round_down; i=i+1.0){
    teleporterCompute += sqrt( chi* i * teleporterEnergy);
  }
  teleporterCompute *= 1.0/(1.0 + chi);

  double cannonCompute = (pow((pow(cannonPowder,1.7)/pow(weight,1.5)),2))/9.8;

  if (cannonCompute<1.0 && teleporterCompute<1.0){
    return 1.0;
  }
  else{
    return std::max(teleporterCompute, cannonCompute);
  }

}

bool GameUtil::isValidPath(std::vector<int>& path, Player* player, Game* game){

	std::vector<Square*> gameboard = game->getBoard();

	if (path.front()!= 0 || path.back()!= gameboard.size()-1){
		return false;
	}
	for (int i=0; i<path.size()-1;i++){
		if (path[i+1]-path[i]>compute(gameboard[i],player)){
			return false;
		}
		if (path[i+1]<=path[i]){
			return false;
		}

	}
	return true;

}

int GameUtil::shortestPathDistance(Game* game, Player* player){
	std::vector<Square*> gameboard = game->getBoard();

	int starting_point = 0;
	int distance = 0;
	int temp = 0;

	for (int i = 0; i < gameboard.size()-1 ; i++ ) {
		temp = compute(gameboard[starting_point],player)+starting_point;
		int temp2 = starting_point;
		for (int j=starting_point+1; j<=temp; j++){
			if ( compute(gameboard[j],player) + j > compute(gameboard[temp2],player) + temp2  ){
				temp2 = j;
			}
		}

		starting_point = temp2;
		distance +=1;
		if ( compute(gameboard[starting_point],player) + starting_point >= gameboard.size()-1 ){
			distance +=1;
			break;
		}
	}

	return distance;

}
