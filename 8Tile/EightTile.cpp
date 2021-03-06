#include "EightTile.h"
#include <iostream>
#include "NA_MathsLib.h"
#include <stdlib.h>

using std::cout;
using std::endl;

EightTile::EightTile()
{
	myMove = NONE;  //initialize member attributes
	
	/*
	tiles[0][0] = 0; tiles[1][0] = 1; tiles[2][0] = 2; //set up puzzle tiles
	tiles[0][1] = 3; tiles[1][1] = 4; tiles[2][1] = 5;
	tiles[0][2] = 6; tiles[1][2] = 7; tiles[2][2] = 8;
	//*/

	//*
	tiles[0][0] = 1; tiles[1][0] = 4; tiles[2][0] = 2; //assigned problem
	tiles[0][1] = 3; tiles[1][1] = 5; tiles[2][1] = 8;
	tiles[0][2] = 6; tiles[1][2] = 0; tiles[2][2] = 7;
	//*/

	solution[0][0] = 0; solution[1][0] = 1; solution[2][0] = 2; //set up solved puzzle tile positions
	solution[0][1] = 3; solution[1][1] = 4; solution[2][1] = 5;
	solution[0][2] = 6; solution[1][2] = 7; solution[2][2] = 8;

	//find blank position
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}

	display();
}

void EightTile::display(void)
//draw puzzle as it is now
{
	system("cls"); //https://support.microsoft.com/en-us/kb/99261
	cout << tiles[0][0] << " " << tiles[1][0] << " " << tiles[2][0] << endl;
	cout << tiles[0][1] << " " << tiles[1][1] << " " << tiles[2][1] << endl;
	cout << tiles[0][2] << " " << tiles[1][2] << " " << tiles[2][2] << endl;
	cout << endl;
}
void EightTile::setMove(enum move m)
//sets which way you want to move
{
	myMove = m;
}
void EightTile::swap(void)
//attempts to move blank in direction set - up, down, left or right by doing a tile/blank swap
//can't move beyond edges of puzzle
{
	int temp;
	if ((myMove == LEFT) && okLeft()) {
		temp = tiles[x - 1][y];
		tiles[x - 1][y] = tiles[x][y];
		tiles[x][y] = temp;
		x = x - 1;

	}
	if ((myMove == RIGHT) && okRight()) {
		temp = tiles[x + 1][y];
		tiles[x + 1][y] = tiles[x][y];
		tiles[x][y] = temp;
		x = x + 1;

	}

	if ((myMove == UP) && okUp()) {
		temp = tiles[x][y - 1];
		tiles[x][y - 1] = tiles[x][y];
		tiles[x][y] = temp;
		y = y - 1;

	}
	if ((myMove == DOWN) && okDown()) {
		temp = tiles[x][y + 1];
		tiles[x][y + 1] = tiles[x][y];
		tiles[x][y] = temp;
		y = y + 1;

	}

	myMove = NONE;
}
bool EightTile::okLeft(void)
//can I move left?
{

	if (x > 0)
		return true; else return false;
}
bool EightTile::okRight(void)
//can I move right?
{
	if (x < 2)
		return true; else return false;
}
bool EightTile::okUp(void)
//can I move up?
{
	if (y > 0)
		return true; else return false;
}
bool EightTile::okDown(void)
//can I move down?
{
	if (y < 2)
		return true; else return false;
}

bool EightTile::okMove(move m)
{
	switch (m)
	{
	case move::DOWN:
		return okDown();
		break;
	case move::LEFT:
		return okLeft();
		break;
	case move::UP:
		return okUp();
		break;
	case move::RIGHT:
		return okRight();
		break;

	default:
		cout << "EightTile::okMove - default used in switch"; // most of my defaults wait for impossibilities
		return false;
		break;
	}
}

int EightTile::getX()
{
	return x;
}

int EightTile::getY()
{
	return y;
}

int EightTile::getSolution(int i, int j)
{
	return solution[i][j];
}

int** EightTile::getTilesCopy()
{
	int** copy;
	copy = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		copy[i] = new int[3];
		for (int j = 0; j < 3; j++)
		{
			copy[i][j] = tiles[i][j];
		}
	}
	return copy;
}

void EightTile::shuffle()
{
	cout << "shuffling puzzle, this may take a moment\n";
	// copy solution into current tiles to make sure that shuffled puzzel will be solveable
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tiles[i][j] = solution[i][j];
		}
	}

	// update blank tracking by finding the blank tile again - it should be the first place searched so this could be simplified
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (tiles[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}

	// do the actual shuffle
	extern NA_MathsLib na_maths;

	na_maths.seedDice();
	int i = 0;
	bool moveOK;
	while (i < SHUFFLE_COUNT)
	{
		moveOK = false;
		move randomMove = (move) na_maths.dice(1,4);
		switch (randomMove)
		{
		case move::DOWN:
			moveOK = okDown();
			break;
		case move::LEFT:
			moveOK = okLeft();
			break;
		case move::UP:
			moveOK = okUp();
			break;
		case move::RIGHT:
			moveOK = okRight();
			break;
		
		default:
			cout << "EightTile::shuffle - default used in switch"; // most of my defaults waitForElapse for imposibilities
			break;
		}
		if (moveOK)
		{
			setMove(randomMove);
			swap();
			i++;
		}
	}

}


