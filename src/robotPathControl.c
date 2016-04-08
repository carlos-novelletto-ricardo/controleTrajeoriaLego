/*
 ============================================================================
 Name        : robotPathControl.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define byte8   int

byte8 currentCoordenate[2];
byte8 endCoordenate[2];
byte8 initCoordenate[2];

byte8 currentPosition[3][3];
byte8 detectecObstacles[3][3];


char *actionList[40];
int actionListIndex=0;

char fwdMove[]="Moveu paraFrente";
char leftMove[]="Moveu Esquerda";
char rightMove[]="Moveu Direita";

char turnleft[]="Girou Esquerda";
char turnright[]="Girou Direita";


char downMove[]="Moveu Para Baixo";
char turn180[]="Girou 180";

#define none 			0
#define obstacle 		1
#define startPoint 		2
#define endPoint 		3
#define right 			4
#define left 			5
#define moveFpward		6
#define MoveDown 		7
#define turnAround      8
#define noneAction 		9

#define o1 1
#define o2 2
#define o3 3
#define o4 4
#define o5 5
#define o6 6
#define o7 7
#define o8 8
#define o9 9
#define o10 10
#define o11 11
#define o12 12


struct robot {

	unsigned int gotCargo;
	unsigned int orientation;
	unsigned int latsOrientation;
	unsigned int netxMov;
	unsigned int lastxMov;

}EV3;

void setRobotOrientaion(unsigned int in_orientation){

	switch(in_orientation){
	case 90:   {
					if(EV3.latsOrientation==0)
					actionList[actionListIndex++]=turnleft;
					else if(EV3.latsOrientation==180)
					actionList[actionListIndex++]=turnright;

					actionList[actionListIndex++]=fwdMove;

					EV3.orientation=90;

					break;
	case 0:   {

				if(EV3.latsOrientation!=0)
					actionList[actionListIndex++]=turnleft;
				actionList[actionListIndex++]=fwdMove;
				EV3.orientation=0;
				break;
	}
	case 180: {
				if(EV3.latsOrientation!=180)
					actionList[actionListIndex++]=turnright;
				actionList[actionListIndex++]=fwdMove;
				EV3.orientation=180;

		break;
	}

	case 270: {

		if(EV3.latsOrientation!=270)
			actionList[actionListIndex++]=turn180;
		actionList[actionListIndex++]=fwdMove;
		EV3.orientation=270;
		break;
	}
	case 360: {

				actionList[actionListIndex++]=turn180;
				actionList[actionListIndex++]=turn180;
				EV3.netxMov=moveFpward;
				break;
			}
	}
	}

	EV3.latsOrientation=EV3.orientation;
}


void setObstacle(short int in_obs){

	switch(in_obs){
		case o1: {	detectecObstacles[0][1]=1;
					break;
				 }
		case o2: {detectecObstacles[0][1]=1;
					break;
				}
		case o3: {
					detectecObstacles[0][2]=1;
					break;
				}

		case o4: {
					detectecObstacles[1][0]=1;
					break;
				}
		case o5: {
					detectecObstacles[1][1]=1;
					break;
				}
		case o6: {
					detectecObstacles[1][2]=1;
					break;
				}

		case o7: {
					detectecObstacles[2][0]=1;
					break;
				}
		case o8: {
					detectecObstacles[2][1]=1;
					break;
				}
		case o9: {
					detectecObstacles[2][2]=1;
					break;
				}
		default : break;
	}

}

byte8 getObstacle(byte8 *in_coordenate){

	return detectecObstacles[in_coordenate[0]][in_coordenate[1]];

}

byte8 getTrajectiry(byte8 *in_coordenate){

	return currentPosition[in_coordenate[0]][in_coordenate[1]];

}

void setStartPoint(byte8 in_startPoint){

	switch(in_startPoint){
		case 1: 	currentPosition[0][0]=1; 	currentCoordenate[0]=0; currentCoordenate[1]=0; initCoordenate[0]=0; initCoordenate[0]=1; break;
		case 2: 	currentPosition[0][1]=1;  	currentCoordenate[0]=0; currentCoordenate[1]=1; initCoordenate[0]=0; initCoordenate[1]=1; break;
		case 3: 	currentPosition[0][2]=1;  	currentCoordenate[0]=0; currentCoordenate[1]=2; initCoordenate[0]=0; initCoordenate[2]=1; break;
	}
}

void setEndPoint(byte8 in_endPoint){

	switch(in_endPoint){
		case 1: 	{currentPosition[2][0]=endPoint; endCoordenate[0]=2; endCoordenate[1]=0; break;}
		case 2: 	{currentPosition[2][1]=endPoint; endCoordenate[0]=2; endCoordenate[1]=1; break;}
		case 3: 	{currentPosition[2][2]=endPoint; endCoordenate[0]=2; endCoordenate[1]=2; break;}
	}
}





struct pointAction{

	byte8 possibleActions[4];
};


struct pointActions{

	struct pointAction point[3][3];
};

struct pointActions PointActions;



//enum options{none,obstacle,startPoint,endPoint,right,left,moveUp,MoveDown,turnAround,noneAction};
void setPossibleInitActions(void){

	PointActions.point[0][0].possibleActions[0]=right;
	PointActions.point[0][0].possibleActions[1]=moveFpward;
	PointActions.point[0][0].possibleActions[2]=noneAction;
	PointActions.point[0][0].possibleActions[3]=noneAction;


	PointActions.point[0][1].possibleActions[0]=right;
	PointActions.point[0][1].possibleActions[1]=moveFpward;
	PointActions.point[0][1].possibleActions[2]=left;
	PointActions.point[0][1].possibleActions[3]=noneAction;

	PointActions.point[0][2].possibleActions[0]=moveFpward;
	PointActions.point[0][2].possibleActions[1]=left;
	PointActions.point[0][2].possibleActions[2]=noneAction;
	PointActions.point[0][2].possibleActions[3]=noneAction;



	PointActions.point[1][0].possibleActions[0]=right;
	PointActions.point[1][0].possibleActions[1]=moveFpward;
	PointActions.point[1][0].possibleActions[2]=MoveDown;
	PointActions.point[1][0].possibleActions[3]=noneAction;


	PointActions.point[1][1].possibleActions[0]=right;
	PointActions.point[1][1].possibleActions[1]=moveFpward;
	PointActions.point[1][1].possibleActions[2]=left;
	PointActions.point[1][1].possibleActions[3]=MoveDown;

	PointActions.point[1][2].possibleActions[0]=moveFpward;
	PointActions.point[1][2].possibleActions[1]=left;
	PointActions.point[1][2].possibleActions[2]=right;
	PointActions.point[1][2].possibleActions[3]=MoveDown;

	PointActions.point[2][0].possibleActions[0]=right;
	PointActions.point[2][0].possibleActions[1]=MoveDown;
	PointActions.point[2][0].possibleActions[2]=noneAction;
	PointActions.point[2][0].possibleActions[3]=noneAction;


	PointActions.point[2][1].possibleActions[0]=right;
	PointActions.point[2][1].possibleActions[1]=left;
	PointActions.point[2][1].possibleActions[2]=MoveDown;
	PointActions.point[2][1].possibleActions[3]=noneAction;

	PointActions.point[2][2].possibleActions[0]=MoveDown;
	PointActions.point[2][2].possibleActions[1]=left;
	PointActions.point[2][2].possibleActions[2]=noneAction;
	PointActions.point[2][2].possibleActions[3]=noneAction;

}

struct pointAction *getPossiPointActions( byte8 *pointCoordenate){

	return PointActions.point[ pointCoordenate[0] ][ pointCoordenate[1]].possibleActions;

}


void calculatePathVector(){

	float *moduleFoward,*moduleRight,*moduleLeft,*moduleDown, *minModulep;
	float modules[4],minModule;
	byte8 Nextcooredenate[2];
	byte8 terminationConditon;
	Nextcooredenate[0]=currentCoordenate[0];
	Nextcooredenate[1]=currentCoordenate[1];

	moduleFoward=&modules[0];
	moduleRight=&modules[1];
	moduleLeft=&modules[2];
	moduleDown=&modules[3];

	byte8 pointCoordenate[2]={0,0}; //y,x
	struct pointAction *pAction;


	int i;
	int j;
	int t;

	int x;
	int ttt;



    	do{

		pAction=getPossiPointActions(currentCoordenate);


		for(j=0;j<4;j++){

					switch (pAction->possibleActions[j]){

						case moveFpward : {

										byte8  nextCoordate[2];

										nextCoordate[0]=currentCoordenate[0]+1;
										nextCoordate[1]=currentCoordenate[1];
										if(getObstacle(nextCoordate)!=0){
											pAction->possibleActions[j]=noneAction;

										}
										break;

									}
						case MoveDown : {

										byte8  nextCoordate[2];

										nextCoordate[0]=currentCoordenate[0]-1;
										nextCoordate[1]=currentCoordenate[1];
										if(getObstacle(nextCoordate)!=0){
											pAction->possibleActions[j]=noneAction;

										}
										break;

									}
						case right : {
										byte8  nextCoordate[2];

										nextCoordate[0]=currentCoordenate[0];
										nextCoordate[1]=currentCoordenate[1]+1;
										if(getObstacle(nextCoordate)!=0){
											pAction->possibleActions[j]=noneAction;

										}
										break;
									}
						case left : {
										byte8  nextCoordate[2];

										nextCoordate[0]=currentCoordenate[0];
										nextCoordate[1]=currentCoordenate[1]-1;
										if(getObstacle(nextCoordate)!=0){
											pAction->possibleActions[j]=noneAction;

										}
										break;

									}
						case noneAction :  break;
						default : break;
					}
				}

			modules[0]=1000;
			modules[1]=1000;
			modules[2]=1000;
			modules[3]=1000;

		for(j=0;j<4;j++){

			switch (pAction->possibleActions[j]){

				case moveFpward : {

								float Y,X,Multiplication;
										Y= endCoordenate[0]- (currentCoordenate[0]+1);
										X= endCoordenate[1]- currentCoordenate[1];

										Multiplication= (float)(X*X+Y*Y);

								modules[0] =  sqrt(Multiplication) ;

								break;

							}

				case right : {
							float Y,X,Multiplication;
									Y= endCoordenate[0]- (currentCoordenate[0] );
									X= endCoordenate[1]- (currentCoordenate[1]+1);

									Multiplication= (float)(X*X+Y*Y);

							modules[1] =  sqrt(Multiplication) ;
							break;
							}
				case left : {
							float Y,X,Multiplication;
									Y= endCoordenate[0]- (currentCoordenate[0] );
									X= endCoordenate[1]- (currentCoordenate[1]-1);

									Multiplication= (float)(X*X+Y*Y);

							modules[2] =  sqrt(Multiplication) ;
							break;

							}
				case MoveDown: {

									float Y,X,Multiplication;
											Y= endCoordenate[0]- (currentCoordenate[0]-1);
											X= endCoordenate[1]- currentCoordenate[1];

											Multiplication= (float)(X*X+Y*Y);

									modules[3] =  sqrt(Multiplication) ;

									break;

								}
				case noneAction :  break;
				default : break;

			}
		}

		minModule=1000;

		for(t=0;t<4;t++){

			if(minModule>modules[t] && modules[t]>=0){
				minModule=modules[t];

			}

		}

		if(minModule==(*moduleFoward)){
			Nextcooredenate[0]+=1;
			 setRobotOrientaion(90);
		    //actionList[actionListIndex++]=fwdMove;

		}
		else if(minModule==(*moduleRight)){
			Nextcooredenate[1]+=1;
			setRobotOrientaion(0);
			//actionList[actionListIndex++]=rightMove;
		}
		else if(minModule==(*moduleLeft)){
			Nextcooredenate[1]-=1;
			setRobotOrientaion(180);
		    //actionList[actionListIndex++]=leftMove;
		}
		else if(minModule==(*moduleDown)){
			Nextcooredenate[0]-=1;
			setRobotOrientaion(270);
			//actionList[actionListIndex++]=downMove;
		}

		//read sensor
		//found obstacle
		//recalculate trajectory

		float Y,X,Y2,X2,Multiplication1,Multiplication2,newModule1,newModule2;
			Y= endCoordenate[0]- (Nextcooredenate[0] );
			X= endCoordenate[1]- (Nextcooredenate[1]);

			Y2= endCoordenate[0]- (currentCoordenate[0] );
			X2= endCoordenate[1]- (currentCoordenate[1]);


			 Multiplication1= (float)(X*X+Y*Y);
			 Multiplication2= (float)(X2*X2+Y2*Y2);
			 newModule1 =  sqrt(Multiplication1) ;
			 newModule2 =  sqrt(Multiplication2) ;
			 static int position=2;
			 static int obstacles=2;
			 if(newModule1>=newModule2){


				 detectecObstacles[currentCoordenate[0]][currentCoordenate[1]]=obstacles++;
				 currentPosition[Nextcooredenate[0]][Nextcooredenate[1]]=position++;
				 currentCoordenate[0]=Nextcooredenate[0];
				 currentCoordenate[1]=Nextcooredenate[1];

			 }
			 else{
					currentPosition[Nextcooredenate[0]][Nextcooredenate[1]]=position++;
					 currentCoordenate[0]=Nextcooredenate[0];
					 currentCoordenate[1]=Nextcooredenate[1];

			 }

		ttt=0;

		ttt=0;
		ttt=0;
			if((endCoordenate[0]==currentCoordenate[0])&&(endCoordenate[1]==currentCoordenate[1])) break;
	}while(1);



	ttt=0;
}



int main(void) {
	EV3.latsOrientation=90;
	EV3.orientation=90;
	setPossibleInitActions();
	setStartPoint(1);
	setEndPoint(3);
	setObstacle(o8);
	setObstacle(o5);
	calculatePathVector();
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
