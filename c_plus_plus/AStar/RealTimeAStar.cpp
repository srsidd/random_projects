/*
	Code to run real time A star algorithm
	Author : Siddharth Srivatsa
	Date : 27th October, 2015
*/

#include <iostream>
#include <math.h>
#define inf 10000
#define gridSizeX 10
#define gridSizeY 10

using namespace std;

class Position { 
	protected:
		int x;
		int y;

	public:
		Position() {
			this->x = 0;
			this->y = 0;
		}

		Position(int p1, int p2) {
			this->x = p1;
			this->y = p2;
		}

		~Position() { }

		void setX(int pos) {
			this->x = pos;
		}

		void setY(int pos) {
			this->y = pos;
		}

		int getX() {
			return this->x;
		}

		int getY() {
			return this->y;
		}

};

class Node : public Position { 
	protected:
		int Gdist;
		int RHSdist;

	public:
		Node() {
			Gdist = inf;
			RHSdist = inf;
		}

		Node(int x, int y) {
			Gdist = inf;
			RHSdist = inf;
			this->x = x;
			this->y = y;
		}

		~Node() { }

		void setGdist(int dist) {
			this->Gdist = dist;
		}

		void setRHSdist(int dist) {
			this->RHSdist = dist;
		}

		int getGdist() {
			return this->Gdist;
		}

		int getRHSdist() {
			return this->RHSdist;
		}
};
class Distance { 

	public: 
		Distance() { }

		~Distance() { }
		static float calcDistance(Position p1, Position p2) {
			return sqrt(pow((p2.getX() - p1.getX()),2) + pow((p2.getY() - p1.getY()), 2));
		}
};

class Grid { 
	protected:
		Node gridNode[gridSizeX][gridSizeY];

	public:
		Grid() {
			for( int row = 0; row < gridSizeX; row++) {
				for (int col = 0; col < gridSizeY; col++) {
					gridNode[row][col].setX(row);
					gridNode[row][col].setY(col);
				}
			}
		}
		~Grid () { }
};

int main() {
	Position start(1,22);
	Position n(133,999);
	Grid myGrid;
	cout << start.getX() << endl;
	cout << start.getY() << endl;
	cout << n.getX() << endl;
	cout << n.getY() << endl;
	cout << Distance::calcDistance(start, n) << endl;
}