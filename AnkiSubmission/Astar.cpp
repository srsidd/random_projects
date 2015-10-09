/*
	This code performs A* search to take the shortest path between two points on a grid.
	Euclidean Distance is used as a heuristic here.
	@author: Siddharth
	Date - Oct 9th, 2015.
*/

#include <iostream>
#include <math.h>
#include <list>
#include <algorithm>
#include <vector>
#include <limits>

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
		Position() {
			x = inf;
			y = inf;
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

class Node : public Position{
	/*
		Class to represent each point in the graph as a node
		Members include node properties - Costs, Coordinate, and bool to indicate if open or closed, and value indicating path, grid or obstacle
		if Value = 0, it's a node, if value = 2 it's a path, if value = inf it's an obstacle
		Methods include setters and getters for each attribute
	*/
	protected:
		float Gcost;
		float Fcost;
		bool openNode;
		bool closedNode;
		int value;

	public:
		// Constructor
		Node() {
			Gcost = 0;
			Fcost = 0;
			openNode = false;
			closedNode = false;
			value = 0;
		}

		/*
			Setter and Getter methods for accessing different attributes for the Node class
		*/
		void setGcost(int cost) {
			this->Gcost = cost;
		}

		void setFcost(int cost) {
			this->Fcost = cost;
		}

		void setValue(int val) {
			this->value = val;
		}

		void addToOpen() {
			this->openNode = true;
		}

		void addToClosed() {
			this->closedNode = true;
		}

		void removeFromOpen() {
			this->openNode = false;
		}

		void removeFromClosed() {
			this->closedNode = false;
		}

		int getGcost() {
			return this->Gcost;
		}

		int getFcost() {
			return this->Fcost;
		}

		int getValue() {
			return this->value;
		}

		bool isOpen() {
			return this->openNode;
		}

		bool isClosed() {
			return this->closedNode;
		}

};

class Output {
	/*
		Class to log data and display the grid by painting the screen
		Members include characters to display the grid, the path, the obstacle and the display area
		Method includes logging data
	*/	
	private:
		char GridDisplayChar;
		char PathDisplayChar;
		char ForbiddenDisplayChar;
		char StartDisplayChar;
		char GoalDisplayChar;

	
	public:
		//Constructor
		Output() {

			GridDisplayChar = '.';
			PathDisplayChar = '#';
			ForbiddenDisplayChar = 'Z';
			StartDisplayChar = 'S';
			GoalDisplayChar = 'E';
		}

		/*
			Setter and Getter methods for accessing different attributes for the Grid class
		*/
		void setGridDisplayChar(char gridChar) {
			this->GridDisplayChar = gridChar;
		}

		void setPathDisplayChar(char pathChar) {
			this->PathDisplayChar = pathChar;
		}

		void setForbiddenDisplayChar(char obstacleChar) {
			this->ForbiddenDisplayChar = obstacleChar;
		}
		void setStartDisplayChar(char startChar) {
			this->StartDisplayChar = startChar;
		}

		void setGoalDisplayChar(char goalChar) {
			this->GoalDisplayChar = goalChar;
		}

		char getGridDisplayChar() { 
			return this->GridDisplayChar;
		}

		char getPathDisplayChar() {
			return this->PathDisplayChar;
		}

		char getForbiddenDisplayChar() {
			return this->ForbiddenDisplayChar;
		}

		char getStartDisplayChar() {
			return this->StartDisplayChar;
		}

		char getGoalDisplayChar() {
			return this->GoalDisplayChar;
		}

		/*
			Methods for displaying the grid on the screen and logging data
		*/
		void showDefualtChars();
		void paintScreen(Position , Position , Node[][gridSize]);
		void logData(string s) {
		cout << s << endl;
		}
};

		/*
			Method to output to the user the default characters being used to display the grid on the screen
			Takes in no values, returns no values
		*/
		void Output::showDefualtChars() {
			cout << "Characters used to display the grid\n" ;
			cout << "gridDisplayChar = " <<  getGridDisplayChar() << "\n" ;
			cout << "pathDisplayChar = " <<  getPathDisplayChar() << "\n";
			cout << "obstacleDisplayChar = " << getForbiddenDisplayChar() << "\n";
			cout << "startDisplayChar = " <<  getStartDisplayChar() << "\n" ;
			cout << "goalDisplayChar = " <<  getGoalDisplayChar() << "\n \n";
		}


		/*
			Method to display the grid on the screen
			Uses characters to display the nodes, the obstacles and the path to be taken
		*/
		void Output::paintScreen(Position start, Position goal, Node myNode[][gridSize]) {
			showDefualtChars();
			for( int row = 0; row < gridSize; row ++) {
				for( int cols = 0; cols < gridSize; cols ++) {

					if (start.getX() == myNode[row][cols].getX() && start.getY() == myNode[row][cols].getY()) {
						cout << StartDisplayChar << " ";
						continue;
					}
					else if (goal.getX() == myNode[row][cols].getX() && goal.getY() == myNode[row][cols].getY()) { 
						cout << GoalDisplayChar << " ";
						continue;
					}
					switch(myNode[row][cols].getValue()) {
						case 0: 
							cout << GridDisplayChar << " ";
							break;
						case 2:
							cout << PathDisplayChar << " ";
							break;
						case inf:
							cout << ForbiddenDisplayChar << " ";
							break;
					}
				}
			cout <<"\n";
			}
		}
		
		
class Input {
	/*
		Class to check whether the user input is appropriate
		Uses the display class to display messages on the screen
		Methods includes as acceptInt which accepts only integers
	*/
	private:
		Output disp;

	public:
		// Constructor
		Input() {

		}
		int acceptInt(int value) {
			while(cin.fail()){
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(),'\n');
		        disp.logData("Bad entry, enter a number");
		        cin >> value;
		    }
		    return value;
		}

};

class Grid {
	/*
		Class to represent the overall graph A* will be searching through
		Members include nodes(num of nodes = size of graph), start and end positions for planning, and a cameFrom to retrace the path
		Methods include initializations of start, end points, obstacles in the grid, getting cost between 2 nodes,
		Getting the nextbest node from the open list, searching the graph and reconstructing the path
	*/
	public:
		Node myNode[gridSize][gridSize];
		Position start;
		Position goal;
		Position cameFrom[gridSize][gridSize];
		Output disp;
		Input inputObj;

		// Constructor
		Grid() {
			for(int rows = 0; rows < gridSize; rows++) {
				for(int cols = 0; cols < gridSize; cols++) {
					myNode[rows][cols].setX(rows);
					myNode[rows][cols].setY(cols);
				}
			}
		}

		/*
			Takes in no arguments, returns no values.
			Method for initiliazing obstacles in the graph
			Currently input by the user
			Does not handle exceptions well - Only checks for digits
		*/
		void getObstacles() {
			int numObstacles;	// To store number of obstacles in the graph, Input from user
			int obstacleX;		// To store x coordinate of each obstacle in the graph
			int obstacleY;		// To store y coordinate of each obstacle in the graph
			disp.logData("Enter number of obstacles ");
			cin >> numObstacles;
			// Handle non numeric inputs
			numObstacles = inputObj.acceptInt(numObstacles);

			for (int i = 0; i < numObstacles; i++) {
				disp.logData("Enter x coordinate of obstacle");
				cin >> obstacleX;				
				// Handle non Numeric inputs
				obstacleX = inputObj.acceptInt(obstacleX);

				disp.logData("Enter y coordinate of obstacle");
				cin >> obstacleY;
				// Handle non numeric exceptions
				obstacleY = inputObj.acceptInt(obstacleY);
			    // Make sure the obstacle is in the graph
			    if(obstacleX > gridSize-1 || obstacleY > gridSize-1 || obstacleX < 0 || obstacleY < 0) {
			    	throw "Obstacle points out of graph";
			    }
			    if (obstacleX == start.getX() && obstacleY == start.getY()) {
			    	throw "Obstacle cannot be the start point";
			    }
			    if (obstacleX == goal.getX() && obstacleY == goal.getY()) {
			    	throw "Obstacle cannot be the goal point";
			    }
				myNode[obstacleX][obstacleY].setX(obstacleX);
				myNode[obstacleX][obstacleY].setY(obstacleY);
				myNode[obstacleX][obstacleY].setGcost(inf);			// Make costs infinite if node is an obstacle
				myNode[obstacleX][obstacleY].setFcost(inf);
				myNode[obstacleX][obstacleY].addToClosed();		// Node is closed if it's an obstacle
				myNode[obstacleX][obstacleY].addToClosed();
				myNode[obstacleX][obstacleY].setValue(inf);
			}
		}

		/*
			Takes in two positions, returns a floating number as the cost between the two positions.
			Hueristic for finding out the distance between nodes, currently using Euclidean distance.
		*/
		float getCost(Position p1, Position p2) {
			return ((sqrt(pow((p2.getX() - p1.getX()),2) + pow((p2.getY() - p1.getY()),2))));
		}

		/*
			Takes in no arguments, returns no values.
			Method for initiliazing the start point for the robot in the graph
			Currently input by the user
			Does not handle exceptions
		*/
		void getStart() {
			int tempX;
			int tempY;
			disp.logData("Enter x coordinate of the start position");
			cin >> tempX;
			// Handle non Numeric inputs
			tempX = inputObj.acceptInt(tempX);

			disp.logData("Enter y coordinate of the start position");
			cin >> tempY;
			// Handle non Numeric inputs
			tempY = inputObj.acceptInt(tempY);

		    start.setX(tempX);
		    start.setY(tempY);

			// Make sure position is valid
			if(start.getX() > gridSize-1 || start.getY() > gridSize-1 || start.getX() < 0 || start.getY() < 0) {
			    throw "Start point out of graph";
		    }
		}

		/*
			Takes in no arguments, returns no values.
			Method for initiliazing the goal point for the robot in the graph
			Currently input by the user
			Does not handle exceptions
		*/
		void getEnd() {
			int tempX;
			int tempY;
			disp.logData("Enter x coordinate of the end position");
			cin >> tempX;
			// Handle non Numeric inputs
			tempX = inputObj.acceptInt(tempX);

			disp.logData("Enter y coordinate of the end position");
			cin >> tempY;
			// Handle non Numeric inputs
			tempY = inputObj.acceptInt(tempY);
			
			goal.setX(tempX);
			goal.setY(tempY);
			// Make sure position is valid
			if(goal.getX() > gridSize-1 || goal.getY() > gridSize-1 || goal.getX() < 0 || goal.getY() < 0) {
			    throw "End point out of graph";
		    }

		    myNode[start.getX()][start.getY()].setGcost(0);
			myNode[start.getX()][start.getY()].addToOpen();
			myNode[start.getX()][start.getY()].setFcost(getCost(start, goal));	// Initialize the start node in the graph
		}

		/*
			Takes in no arguments, returns no values.
			Method for finding the next best node from the list of opennodes. Uses Fcost as the metric
		*/
		Node getNextBestNode() {
			float minDist = inf;
			Node cur;

			// Iterate throught the open list of nodes and select the best node to explore next
			for(int rows = 0; rows < gridSize; rows++) {
				for(int cols = 0; cols < gridSize; cols++) {
					if(myNode[rows][cols].getFcost() < minDist && myNode[rows][cols].isOpen() == true){
						cur.setX(rows);
						cur.setY(cols);
						minDist = myNode[rows][cols].getFcost();
					}
				}
			}
			return cur;
		}

		/*
			Takes in the current node, returns no values.
			Method for finding the neighbors and exploring the graph from the current node
		*/
		void exploreGrid(Node cur) {

			Node neighbor;
			
			const int numNeighbors = 8;

			// Transitions (Along with distance)to be made to reach neighboring nodes from the current position
			int deltaX[numNeighbors] = {1, 1, 0,-1,-1,-1, 0, 1}; 
			int deltaY[numNeighbors] = {0, 1, 1, 1, 0,-1,-1,-1};
			float deltaDistance[numNeighbors] = {1,sqrt(2),1,sqrt(2),1,sqrt(2),1,sqrt(2)};
			float curNeighborDistance;		// To keep track of distance between the neighbor and the start

			for (int curNeighbor = 0; curNeighbor < numNeighbors; curNeighbor++) {
				neighbor.setX(cur.getX() + deltaX[curNeighbor]);
				neighbor.setY(cur.getY() + deltaY[curNeighbor]);

				// Make sure neighbors are valid and are not closed nodes (obstacles)
				if(neighbor.getX()< 0 || neighbor.getX() > gridSize) {
					continue;
				}
				if(neighbor.getY() < 0 || neighbor.getY() > gridSize) {
					continue;
				}
				if (myNode[neighbor.getX()][neighbor.getY()].isClosed() == true) {
					continue;
				}

				// Get the Gcost of the neigbor to keep track of how distance has been travelled from the start.
				curNeighborDistance = cur.getGcost()  + deltaDistance[curNeighbor];

				if (neighbor.isOpen() == false || curNeighborDistance < neighbor.getGcost()) {
					cameFrom[neighbor.getX()][neighbor.getY()].setX(cur.getX());
					cameFrom[neighbor.getX()][neighbor.getY()].setY(cur.getY());
					myNode[neighbor.getX()][neighbor.getY()].setGcost(curNeighborDistance);
					Position tempPos;
					tempPos.setX(neighbor.getX());
					tempPos.setY(neighbor.getY());
					myNode[neighbor.getX()][neighbor.getY()].setFcost(myNode[neighbor.getX()][neighbor.getY()].getGcost() + getCost(tempPos, goal));
					if(neighbor.isOpen() == false && neighbor.isClosed() == false) {
						myNode[neighbor.getX()][neighbor.getY()].addToOpen();		// Add the niehgbor to the open list if not already present
					}
				}

			}
		}

		/*
			Takes in the no arguments, returns no values.
			Method for backtracing from the goal to the end for reaching 
		*/
		void reconsrtuctPath() {
			Position traceBackPos;
			traceBackPos = goal;

			myNode[traceBackPos.getX()][traceBackPos.getY()].setValue(2);
			traceBackPos = cameFrom[traceBackPos.getX()][traceBackPos.getY()];

			// Back trace through the graph by selecting the previous node that the robot came from.
			for(int rows = gridSize-1; rows >= 0 ; rows--) {
				for(int cols = gridSize-1; cols >= 0; cols--) {
					if(traceBackPos.getX() == cameFrom[rows][cols].getX() && traceBackPos.getY() == cameFrom[rows][cols].getY()) {
						myNode[traceBackPos.getX()][traceBackPos.getY()].setValue(2);
						traceBackPos = cameFrom[traceBackPos.getX()][traceBackPos.getY()];
						if (traceBackPos.getX() == start.getX() && traceBackPos.getY() == start.getY()) {
							myNode[traceBackPos.getX()][traceBackPos.getY()].setValue(2);
							return;
						}
					}
				}
			}

			// Back trace through the graph by selecting the previous node that the robot came from.
			for(int rows = 0; rows < gridSize ; rows++) {
				for(int cols = 0; cols < gridSize-1; cols++) {
					if(traceBackPos.getX() == cameFrom[rows][cols].getX() && traceBackPos.getY() == cameFrom[rows][cols].getY()) {
						myNode[traceBackPos.getX()][traceBackPos.getY()].setValue(2);
						traceBackPos = cameFrom[traceBackPos.getX()][traceBackPos.getY()];
						if (traceBackPos.getX() == start.getX() && traceBackPos.getY() == start.getY()) {
							myNode[traceBackPos.getX()][traceBackPos.getY()].setValue(2);
							return;
						}
					}
				}
			}
			disp.logData(" No path could be found ");
		}

		/*
			Takes in the no arguments, returns no values.
			Method for performing the A* search and calling other functions from the start to the end
		*/
		void getShortestPath() {
			while(1) {
				Node currentNode;

				// Get the best node from the open list to explore next
				currentNode = getNextBestNode();

				// Check if the goal has been reached
				if(currentNode.getX() == goal.getX() && currentNode.getY() == goal.getY()) {
					reconsrtuctPath();
					disp.paintScreen(start, goal, myNode);
					return;
				}

				// Remove the current node from the open list and add it to the closed list
				myNode[currentNode.getX()][currentNode.getY()].removeFromOpen();
				myNode[currentNode.getX()][currentNode.getY()].addToClosed();

				// Continue searching and exploring the graph				
				exploreGrid(currentNode);
			}
		}
};

/*
	Main function
*/
int main() {
	Grid myGrid;
    try {
    	myGrid.getStart();
    	myGrid.getEnd();
    	myGrid.getObstacles();
    }
    catch (const char* msg) {
    	cerr << msg << ", Exiting code" << endl;
    	exit(0);
    }
    
	myGrid.getShortestPath();
}
