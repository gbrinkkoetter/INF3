/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream>
#include "SIMPLESOCKET.H"
#include "TASK3.H"

using namespace std;

string coordStr(int x, int y){
	std::stringstream ss;
	ss<<"COORD["<< x <<","<< y <<"]";
	return ss.str();
}

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	int x=0, y=0, r;
	int nmbShoots = 0;

	//connect to host
	c.conn(host , 2025);

	/*
	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		*/

	for(int i=0; i<500; i++){	// i = Anzahl Durchführungen
	c.sendData(string("NEWGAME"));
	msg = c.receive(32);
	nmbShoots=0;

	//Strategie A: Feld für Feld

	/*
	for(y=1; y<=10; y++){
		for(x=1; x<=10; x++){
			msg = coordStr(x,y);
			c.sendData(msg);
			msg = c.receive(32);
			nmbShoots++;

		if(1 != sscanf(msg.c_str(),"RES[%d]",&r)){
			cout << "unkown response:" << msg << endl;
			}
		if(r == TASK3::GAME_OVER) break;
		}
	}
	cout << "" << nmbShoots << endl;
	}
	*/

	//Strategie B: Schießen auf zufälliges Feld


	while(1){
		x = (rand()%10) + 1;
		y = (rand()%10) + 1;
		msg =coordStr(x,y);
		c.sendData(msg);
		msg = c.receive(32);
		if(1 != sscanf(msg.c_str(),"RES[%d]",&r)){
			cout << "unkown response:" << msg << endl;
			}
		else{
			nmbShoots++;
			}
		if(r == TASK3::GAME_OVER) break;
		}

	cout << "" << nmbShoots << endl;
	}


	// Ende der Strategien

	c.sendData(string("BYEBYE"));
	msg = c.receive(32);
	cout << "unknown response:" << msg << endl;

}



