#include <iostream>
#include <math.h>
#include <algorithm>
#include <map>

#define inf 1000
#define gridSize 20

using namespace std;

class Position {
	/*
		Class to store x and y positions in the graph
		Members include integers x,y
		Methods include setters and getters
	*/
	protected:
		int x;
		int y;

	public:
		// Constructor
		Position () { }

		Position(int p1, int p2) {
			x = p1;
			y = p2;
		}

		/*
			Setter and Getter methods for accessing different attributes for the Position class
		*/
		void setX(int xCoord) {
			this->x = xCoord;
		}

		void setY(int yCoord) {
			this->y = yCoord;
		}

		int getX() {
			return this->x;
		}

		int getY(){
			return this->y;
		}
};

class Node {
	/*
		Class to represent each point in the graph as a node
		Members include node properties - Costs, Coordinate, and bool to indicate if open or closed, and value indicating path, grid or obstacle
		if Value = 0, it's a node, if value = 2 it's a path, if value = inf it's an obstacle
		Methods include setters and getters for each attribute
	*/
	protected:
		float Gcost;
		float Hcost;
		Position p;

	public:
		// Constructor
		Node () { }

		Node(Position pos) {
			Gcost = 0;
			Hcost = 0;
			p.setX(pos.getX());
			p.setY(pos.getY());
		}

		/*
			Setter and Getter methods for accessing different attributes for the Node class
		*/
		void setGcost(int cost) {
			this->Gcost = cost;
		}

		void setHcost(int cost) {
			this->Hcost = cost;
		}

		int getGcost() {
			return this->Gcost;
		}

		int getHcost() {
			return this->Hcost;
		}
};


class Grid {

	protected:
		Node &myNode[gridSize][gridSize];
		Position cameFrom[gridSize][gridSize];

	public:
		float getCost(Position p1, Position p2) {
			return ((sqrt(pow((p2.getX() - p1.getX()),2) + pow((p2.getY() - p1.getY()),2))));
		}

		// Constructor
		Grid(Position start, Position end) {
			for(int rows = 0; rows < gridSize; rows++) {
				for(int cols = 0; cols < gridSize; cols++) {
					Position curPos(rows, cols);
					(myNode[rows][cols])(curPos);
					if(rows == start.getX() && cols == start.getY()) {
						myNode[rows][cols].setGcost(0);
						myNode[rows][cols].setHcost(getCost(start, end));
					}
				}
			}
		}

};

int main(){ 
	cout << "hello world" << endl;
	multimap<int, Node> m;
	Node* myNode = new Node;

	// m.insert(pair<Node, int>(myNode[0][1], 2));
	// m.insert(pair<Node, int>(myNode[0][2], 3));
	// m.insert(pair<Node, int>(myNode[0][3], 4));
	// m.insert(pair<Node, int>(myNode[0][4], 5));
}