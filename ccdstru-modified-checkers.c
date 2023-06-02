/*
S14.2
Atutubo, Regner
Lapuz, Mari Salvador
Tuballa, Hans
Zuñiga, John
*/
#include <stdio.h>
#include <stdlib.h>
/****************************************************************************************
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
****************************************************************************************/

/*displayRow displays a row for game space
@param aRow[] stores characters (pieces for the game)*/

void displayRow(char aRow[])
{
	int i;
	
	for (i = 0; i < 6; i++){
        printf("%c  ", aRow[i]);
    }
		printf("\n");	
}
/***************************************************************************************/
/***************************************************************************************/

/*displayAll duplicates displayRow to create columns
//@aMatrix[][6] stores characters (pieces for the game)*/
void displayAll(char aMatrix[][6])
{
	int j;
	
	for (j = 0; j < 8; j++){
            printf("\n");
        displayRow(aMatrix[j]);
    }
}
/***************************************************************************************/
/***************************************************************************************/

/*displayBoard displays some elements for the board
@param aMatrix[][6] stores characters (pieces for the game)
@param cFree - represented by an asterisk; signifies empty/unoccupied points on the playing space*/
void displayBoard(char aMatrix[][6], char cFree)
{
	int i, j;
	
	for(i=0;i<8;i++)
  {
		for(j=0;j<6;j++)
    {
			aMatrix[i][j]=cFree;
			aMatrix[0][j] = '0'+j;
      
      if(i==0||j==0)
      {
			  aMatrix[i][j]='0'+i;
		  }
    }
	}
}
/***************************************************************************************/
/***************************************************************************************/

/*setPieces displays the opposing pieces on their initial positions
@param aMatrix[][6] stores characters (pieces for the game)
@param cAlpha - represented by A; usually first to move
@param cBeta - represented by B*/
void setPieces(char aMatrix[][6], char cAlpha, char cBeta){
	int i, j;

	for(i=1;i<8;i++){
		for(j=1;j<6;j++){
			if((i==7&&j%2==1)||(i==6&&j%2==0)){
			  aMatrix[i][j]=cAlpha;
			}
		}
	}
	for(i=1;i<8;i++){
		for(j=1;j<6;j++){
			if((i==1&&j%2==1)||(i==2&&j%2==0)){
				aMatrix[i][j]=cBeta;
			}
		}
	}
}
/***************************************************************************************/
/***************************************************************************************/

/*Region - valid areas to attack
@nNext[] where the chosen piece is placed*/

int sRegion(int nNext[]){

	//int i,j; 
	int sAvail;
	int nCheck1 = 0; int nCheck2 = 0;

//for values [row = even][col = odd]
		if (nNext[0]%2==0)
    {                    //even ROW -- 1
			nCheck1 = 1;
			if (nNext[1]%2==1)
      {                  //odd COLUMN -- 2
					nCheck2 = 1;
      }
		}
			
		else if(nNext[0]%2==1){ //odd ROW -- 2
			nCheck1 = 1;
				if (nNext[1]%2==0)  //even COLUMN -- 1
					nCheck2 = 1;
			}
	
	sAvail = nCheck1 + nCheck2;
	if (sAvail == 2)
  {
    return 1; //the area is restricted
  }
	else
  {
		return 0; //area is allowed
  }
}
/***************************************************************************************/
/***************************************************************************************/

/*checkValidityA checks if the move of the Alpha pieces are valid as based on the specs, pieces are only allowed to move one space diagonally or forward 
@param nPrev[] stores the value of the previous move
@param nNext[] stores the value of the next move*/

int checkValidityA(int nPrev[], int nNext[])
{
	int ok = 0;
// Check if the moves are valid, valid moves are forward and diagonal
// invalid moves are backward and sideways
	if(nPrev[0]==nNext[0]+1 && (nNext[1]==nPrev[1] ||     nNext[1]==nPrev[1]+1 ||nPrev[1]==nNext[1]+1 ))
		 ok = 1;
	else 
		ok = 0;
			
	return ok;
}
/***************************************************************************************/
/***************************************************************************************/

/* checkValidityB checks if the move of the Beta pieces are valid as based on the specs, pieces are only allowed to move one space diagonally or forward 

@param nPrev[] stores the value of the previous move
@param nNext[] stores the value of the next move*/

int checkValidityB(int nPrev[], int nNext[])
{
	int ok = 0;
// Check if the moves are valid, valid moves are forward and diagonal
// invalid moves are backward and sideways
	if(nNext[0]==nPrev[0]+1 && (nNext[1]==nPrev[1] ||     nNext[1]==nPrev[1]+1 ||nPrev[1]==nNext[1]+1 ))
		 ok = 1;
	else 
		ok = 0;
			
	return ok;
}

/***************************************************************************************/
/***************************************************************************************/

/* movePieceA checks the turn of Alpha and if capturing of Beta is valid

@param aMatrix [][6] defines the size of the board
@param nRow gets the value chosen by the player
@param nCol gets the value chosen by the player
@param cAlpha is the char for 'A'
@param cBeta is the char for 'B'
@param cFree is the char for '*'
@param nPrev[] stores the value of the previous move
@param nNext[] stores the value of the next move
@param *turn is a pointer that checks if it is Alpha's Turn*/

void movePieceA(char aMatrix[][6], int nRow, int nCol, char cAlpha, char cBeta, char cFree, int nPrev[], int nNext[], int *turn)
{
//	int i, j;
  int nRowP, nColP;
  
  printf("\n");
  printf("Alpha's Turn \n");
  printf("\n");
  
	printf("Input initial coordinates: ");
	scanf("%d %d", &nRowP, &nColP);
  	nPrev[0] = nRowP; nPrev[1] = nColP;
//if the player chooses a piece which isn't alpha then the player will be required to choose again. (in this case Beta)
  if(aMatrix[nRow][nCol] == 'B')
  {
    printf("\n");
    printf("You must Choose Alpha!\n");
    printf("\n");
    *turn = -1;
  }
//if the player chooses a piece which isn't alpha then the player will be required to choose again. (in this case Asterisk)
  else if(aMatrix[nRow][nCol] == '*')
  {
    printf("\n");
    printf("You must Choose Alpha!\n");
    printf("\n");
    *turn = -1;
  }
  
	printf("Input coordinates of destination: ");
	scanf("%d %d", &nRow, &nCol);
	nNext[0] = nRow; nNext[1] = nCol;
  
  if(aMatrix[nRow][nCol] == 'B' && sRegion(nNext) == 1)//checks if the area is restricted
  {
    printf("\n");
    printf("You cannot eat here!\n"); 
    printf("\n");
    *turn = -1;
  }
  else if(aMatrix[nRow][nCol] == 'B' && sRegion(nNext) == 0) //checks if the area is allowing the player to eat a piece
  {
    printf("\n");
    printf("You ate a Beta piece!\n");
    printf("\n");
    aMatrix[nRow][nCol] = cAlpha;
    aMatrix[nRowP][nColP] = cFree;
  }
  else if(checkValidityA(nPrev, nNext)==1)
  {// checks if player's move is valid
    if (aMatrix[nRow][nCol] == 'A')
    {
      printf("\n");
      printf("You cannot eat your own piece!\n"); 
      printf("\n");
      *turn = -1;
    }
    aMatrix[nRow][nCol] = cAlpha; 
    aMatrix[nRowP][nColP] = cFree; //nRowP nColP stores prev                                         location
  }
  else
  {
    printf("\n");
    printf("Wrong Movement!\n"); 
    printf("\n");
    *turn = -1; 
  }
}
/***************************************************************************************/
/***************************************************************************************/
/* movePieceB checks the turn of Beta and if capturing of Alpha is valid

@param aMatrix [][6] defines the size of the board
@param nRow gets the value chosen by the player
@param nCol gets the value chosen by the player
@param cAlpha is the char for 'A'
@param cBeta is the char for 'B'
@param cFree is the char for '*'
@param nPrev[] stores the value of the previous move
@param nNext[] stores the value of the next move
@param *turn is a pointer that checks if it is Beta's Turn*/

void movePieceB(char aMatrix[][6], int nRow, int nCol, char cAlpha, char cBeta, char cFree, int nPrev[], int nNext[], int *turn)
{
	
//	int i, j;
  int nRowP, nColP;

  printf("\n");
  printf("Beta's Turn \n");
  printf("\n");
  
	printf("Input initial coordinates: ");
	scanf("%d %d", &nRowP, &nColP);
  	nPrev[0] = nRowP; nPrev[1] = nColP;
//if the player chooses a piece which isn't alpha then the player will be required to choose again. (in this case Alpha) 
  if(aMatrix[nRow][nCol] == 'A')
  {
    printf("\n");
    printf("You must Choose Beta!\n");
    printf("\n");
    *turn = 2;
  }
//if the player chooses a piece which isn't alpha then the player will be required to choose again. (in this case Asterisk)
  else if(aMatrix[nRow][nCol] == '*')
  {
    printf("\n");
    printf("You must Choose Beta!\n");
    printf("\n");
    *turn = 2;
  }
  
	printf("Input coordinates of destination: ");
	scanf("%d %d", &nRow, &nCol);
	nNext[0] = nRow; nNext[1] = nCol;//nRowP nColP stores prev location          
      
  if(aMatrix[nRow][nCol] == 'A' && sRegion(nNext) == 1)
  {//checks if the area is restricted
    printf("\n");
    printf("You cannot eat here!\n"); 
    printf("\n");
    *turn = 2;
  }
  else if(aMatrix[nRow][nCol] == 'A' && sRegion(nNext) == 0)
  {//checks if the area is allowing the player to eat a piece
    printf("\n");
    printf("You ate an Alpha piece!\n");
    printf("\n");
    aMatrix[nRow][nCol] = cBeta;
    aMatrix[nRowP][nColP] = cFree;
  } 
  else if(checkValidityB(nPrev, nNext)==1)
  {// checks if player's move is valid
    if (aMatrix[nRow][nCol] == 'B')
    {
      printf("\n");
      printf("You cannot eat your own piece!\n"); 
      printf("\n");
      *turn = 2;
    }
    aMatrix[nRow][nCol] = cBeta; // basta yung thought para kapag nag invalid inde magiging asterisk yung input na nilagay
    aMatrix[nRowP][nColP] = cFree; 
  }
  else
  {
    printf("\n");
    printf("Wrong Movement!\n"); 
    printf("\n");
    *turn = 2;
  }
}

 
/* scanMatrix checks if Alpha or Beta won

@param aMatrix[][6] defines the size of the board
@param cAlpha is the char 'A'
@param cBeta is the char 'B'
@param *GameOver1 is a pointer that determines if the first winning factor is applied
@param *GameOver2 is a pointer that determines if the second winning factor is applied*/

void scanMatrix(char aMatrix[][6], char cAlpha,char cBeta,
  int *GameOver1, int *GameOver2)
{
  
	int i,j;
	//int nSum1 = 0; int nSum2 = 0;
	int nAlpha = 0; int nBeta = 0;

	for (i = 0; i < 8; i++)//ROWS
	{
		for (j = 0; j < 6; j++)//COLS
		{
			if (aMatrix[i][j] == cAlpha)
			    nAlpha++;
			else if (aMatrix[i][j] == cBeta)
			    nBeta++;
    }
	}

  if (nAlpha != 5 || nBeta != 5)
  {
    *GameOver1 = 1;
    *GameOver2 = 0;
  }
  else
  { 
    *GameOver2 = 1;
    *GameOver1 = 0;
  }

  if(*GameOver1 == 1)
  {
    if (nAlpha == 0)
  	{
  		printf("Beta Won!\n");
      exit(1);
  	}
  
  	else if (nBeta == 0)
  	{
  		printf("Alpha Won!\n");
      exit(1);
  	}
  }
  
  printf("Total A: %d\n", nAlpha);
	printf("Total B: %d\n", nBeta);
}

int main(){
	//int j, i, x nCount=0;
	int nRow, nCol;
	//int top = 0;
	int nTemp = 0;
  int turn = 0;
  int GameOver1 = 0; int GameOver2 = 0;
  //int alphaW2 = 0; int betaW2 = 0;
  int nPrev[2]; int nNext[2];
	
	char cAlpha = 'A';
	char cBeta =  'B';
	char cFree =  '*';
	
	char aMatrix[8][6];

  //create a function for turn indication if it's alpha or beta's turn
  
	displayBoard(aMatrix, cFree);
	setPieces(aMatrix, cAlpha, cBeta);

	while(nTemp==0)
  {
    while(turn == 0)//ALPHA
    {
      displayAll (aMatrix);
      scanMatrix(aMatrix, cAlpha, cBeta,
        &GameOver1, &GameOver2);
	    movePieceA(aMatrix, nRow, nCol, cAlpha, 
	          cBeta, cFree, nPrev, nNext, &turn);
      //printf("GameOver 1 Ending: %d\n", GameOver1);
      //printf("GameOver 2 Ending: %d\n", GameOver2);

      turn++;
    }
    while(turn == 1)//BETA
    {
      displayAll (aMatrix);
      scanMatrix(aMatrix, cAlpha, cBeta,
        &GameOver1, &GameOver2);
	    movePieceB(aMatrix, nRow, nCol, cAlpha, 
	          cBeta, cFree, nPrev, nNext, &turn);
      
     // printf("GameOver 1 Ending: %d\n", GameOver1);
     // printf("GameOver 2 Ending: %d\n", GameOver2);
      turn--;
    }
	}
  
	return 0;
}


