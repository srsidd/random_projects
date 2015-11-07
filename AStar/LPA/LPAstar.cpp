#include <iostream>
#include <stdio.h>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <new>
#include <fstream>


using namespace std;

#define L 6 //Length
#define B 4 //Breadth


typedef std::pair<int*,int> returnNeighbours;
typedef std::pair<float,float> KEY_TYPE;


struct Nodes
{
	KEY_TYPE KEY;
	float gScore;
	float hScore;
	float fScore; 
	float rhsValue;
	bool obstacle; 
	int nodeId;
}nodeList[L*B]; // all the nodes by default are given values of 0 for everything

struct nodeQueue
{
	KEY_TYPE KEY;
	int nodeId;
};



const auto M = 6;
const auto N = 4;
auto map = new double[M][N];



int* neighbours; //The generateNeighbour() variable
int XY[2];//The indexToCartesian() variable
returnNeighbours N1;
returnNeighbours nextToMe_INIT, nextToMe_uV, nextToMe_faN, nextToMe_path;
std::vector<nodeQueue> priorityQueue; 
vector<int> path;
vector<int> tbAltered;
vector<int> succPath;

void INIT();
void printStat();
int* indexToCartesian(int);
float heuristic_cost(int,int);
void printPQ();
bool keyCompare();
void computeShortestPath();
void updateVertex(Nodes);
void forAllNeighbors(Nodes);
void getMap();
void printMap();
void assignNodes();
void printGridValues();
void getPath();
void getChange();
std::vector<int> getSuccessors(int);
returnNeighbours generateNeighbour(int);
KEY_TYPE calculateKey(int);




float INF = numeric_limits<float>::max(); //Max value that a float can take
int startNode = 0;
int endNode = 3;
int nn;

int main()
{


	//obtain the map
	getMap();
	printMap();

	//assign the nodeList accordingly
	assignNodes();

	//Initialise all gScore to be INF; rhsValue accordingly; init all keys
	INIT();

	//Print Status 
	printStat();
	printPQ();
	
	//pathPlan

	while(1)
	{
		computeShortestPath();

		cout<<"\n After computeShortestPath\n\n";

		//Print Status 
		printStat();

		//printMap with gScores and keys
		//printGridValues();
		getPath();
		for (std::vector<int>::iterator pIt = path.begin(); pIt != path.end()+1; ++pIt)
			cout<<setw(2)<<*pIt<<"\t";
		cout<<"\n\n";
		// succPath = getSuccessors(17);
		//get nodes that need changing
		getChange();

		for(int it = 0; it < tbAltered.size(); ++it)
		{
			nn = tbAltered[it];
			succPath = getSuccessors(nn);
			nodeList[nn].obstacle = ~nodeList[nn].obstacle;
		    for(std::vector<int>::iterator sIter = succPath.begin(); sIter != succPath.end(); ++sIter)
			{				
				updateVertex(nodeList[*sIter]);
			}
		}	

		//hold output
		getchar();	
	}
	

}

void getChange()
{
	printMap();
	int userInput,found;	
	int idx, len, thatNode;
	userInput = 0;
	found = 0;
	cout<<"Enter those indecies that have to be toggled. Numbering follows a bottomLeft origin with indecies increasing linearly from 0 to the right(with wrap around)\n";
	cin>>userInput;
 	while(userInput !=  -1)
 	{
 		tbAltered.push_back(userInput);
 		cin>>userInput;
 	}

 	//for each of the nodes that are entered above, we must check if it is in the path traversed
 	
 	for (int iter = 0; iter<tbAltered.size(); iter++)
 	{	

 		thatNode = tbAltered[iter];
 		for (std::vector<int>::iterator it = path.begin() ; it != path.end(); ++it)
 		{
 				
 			len = *it; 			
 			if(len == thatNode)
 			{
 				found = 1;
 			}	
 			 			
 		}
 		// vector<int>::iterator iterPathNode = find_if(path.begin(), path.end(),
 		// 			 [&thatNode](int n){return n == thatNode;});

 		//idx = iterPathNode - path.begin();

 		if ( found!= 1)
 		{
 			tbAltered.erase(tbAltered.begin() + iter);
 			iter--;
 		}

 		found = 0;
 	}
}

vector<int> getSuccessors(int nodeId)
{
	// This function is used to obtain all the successors(from Path) of a particular node 
	reverse(path.begin(), path.end());
	for(int i = 0; i<path.size(); i++)
	{
		if(path[i] == nodeId)
		{
			std::vector<int>::iterator it1 = path.begin() +i;
			std::vector<int>::iterator it2 = path.end();
			std::vector<int> nextInLine(it1,it2);	
			nextInLine.push_back(endNode);		
			return nextInLine;
		}		
	
	}


}


void getPath()
{
	//This funciton will have to ascertain the path. get min cost as you go
	//greedily decreasing start dist. This implies, we start from goalNode

	int hopNodeId;
	vector<Nodes> towardsStart;
	hopNodeId = endNode;
	int currentNeighbour;

	path.clear();
	while (hopNodeId != startNode)
	{
		nextToMe_path = generateNeighbour(hopNodeId);

		for (int neighIter = 0; neighIter<nextToMe_path.second; neighIter++)
		{
			//assign from the nodeList
			currentNeighbour = nextToMe_path.first[neighIter];

			//check if that neighbour is an obstacle
			if(nodeList[currentNeighbour].obstacle)
			{
				continue;
			}
			if (nodeList[currentNeighbour].gScore == nodeList[currentNeighbour].rhsValue)
			{
				towardsStart.push_back(nodeList[currentNeighbour]);
			}
		}
		sort(towardsStart.begin(), towardsStart.end(), [](Nodes N1, Nodes N2){return N1.gScore < N2.gScore;});
		path.push_back(towardsStart.front().nodeId);

		hopNodeId = towardsStart.front().nodeId;

		towardsStart.clear();
	}
}

void getMap()
{
    ifstream file("data.txt");

    for (unsigned int i = 0; i < M; i++)
    {
        //array_2d[i] = new int[5];

        for (unsigned int j = 0; j < N; j++) 
            file >> map[i][j];
    
    }    
    file.close();
}

void printMap()
{
	for (unsigned int i = 0; i < M; i++)
    {
        //array_2d[i] = new int[5];

        for (unsigned int j = 0; j < N; j++) 
            cout<<setw(2)<<map[i][j]<<" ";
    
    	cout<<"\n";
    }    
    
}


void printGridValues()
{
	int iter = L*B - 1;
	int counter = 0;
	for (unsigned int i = 0; i < M; i++)
    {
        //array_2d[i] = new int[5];
    	counter = 0;
        for (unsigned int j = 0; j < N; j++) 
        {
        	//cout<<setw(2)<<iter<<" ";
        	cout<<"|"<<setw(5)<<nodeList[iter].gScore<<" \t["<<setw(3)<<nodeList[iter].KEY.first<<","<<
        	setw(3)<<nodeList[iter].KEY.second<<"]|";
			--iter;
        }

    
    	cout<<"\n";
    }    
}


void assignNodes()
{	
	//This function, assigns the nodes to their obstacle values

	int* cartesian;

	for (int iter = 0; iter <M*N; iter++)
	{
		cartesian = indexToCartesian(iter);
		if(map[cartesian[0]][cartesian[1]] != 0 )
			nodeList[iter].obstacle = 1;
	}
}


bool pairCompare(const nodeQueue& firstElem, const nodeQueue& secondElem) 
{
	if (firstElem.KEY.first == secondElem.KEY.first)
   		return firstElem.KEY.second < secondElem.KEY.second; //lower key comes first
   	else
   		return firstElem.KEY.first < secondElem.KEY.first;
}

int* indexToCartesian(int index)
{
	
	div_t cartesian;
	cartesian = div(index,N);
	XY[0] = cartesian.rem; //Y
	XY[1] = cartesian.quot; //X

	//The XY obtained here does not give us the coordinates in the required format. The origin in the required format is at the bottom left
	//Thus, we transform these pts as required. 

	int gridR, gridC;
	gridR = (M-1) - XY[1]; //Here, M is the numof rows as specified. 
	gridC = XY[0];

	XY[0] = gridR;
	XY[1] = gridC;

	return XY;
}


float heuristic_cost(int here, int there)
{
	float cost;
	int start[2], endNode[2];
	int *cartesian;

	cartesian = indexToCartesian(here); //Start cartesian coordiantes
	start[0] = cartesian[0];
	start[1] = cartesian[1];

	cartesian = indexToCartesian(there);
	endNode[0] = cartesian[0];
	endNode[1] = cartesian[1];

	cost = sqrt(pow((start[0] - endNode[0]),2) + pow((start[1] - endNode[1]),2));


	return cost;
}




void printStat()
{
	int iter;
	for (iter = 0; iter< L*B; iter++)	
	{
		cout<<"NODE: "<<setw(3)<<iter<<"\tgScore: "<<setw(11)<<nodeList[iter].gScore<<"\tKEY: ["\
			<<nodeList[iter].KEY.first<<", "<<nodeList[iter].KEY.second<<"]"<<"\n";	
		//cout<<"NODE: "<<setw(3)<<iter<<"\tgScore: "<<setw(11)<<nodeList[iter].gScore<<"\n";
	}

}

void printPQ()
{
	int sizeQ;
	nodeQueue tempNQ;

	sizeQ = priorityQueue.size();

	//test the sort functionality
	sort(priorityQueue.begin(), priorityQueue.end(),pairCompare);

	int iter;
	for (iter = 0; iter < sizeQ; iter++)	
	{
		tempNQ = priorityQueue.at(iter);
		cout<<setw(3)<<tempNQ.nodeId<<"; ["<<setw(10)<<tempNQ.KEY.first<<setw(10)<<tempNQ.KEY.second<<"]\n";
	}	
	
}


// NOTE: This function assumes that the x,y coordiantes are in matlab format
returnNeighbours generateNeighbour(int node)	//node = nodeIndex
{
	int* cartesian;
	int* NEIGH;
	//int neighbours[8];
	cartesian = indexToCartesian(node); //Obtain(x,y)
	int x,y;
	//Ret_arr N;
	int L_lim;

	x = cartesian[0];
	y = cartesian[1];

	//int neighbours[8];
	

	if(x == L-1 && y == 0)//Bottom Left
	{
		neighbours = new (nothrow) int[3];
		//int NEIGH[3] = {1,0+B,0+B+1};	
		//return neighbours;
		neighbours[0] = 1;
		neighbours[1] = 0+B;
		neighbours[2] = 0+B+1;			
		L_lim = 3;	
	}

	else if(x == 0 && y == 0)//Top Left
	{
		neighbours = new (nothrow) int[3];
		neighbours[0] = node-B;
		neighbours[1] = node +1;
		neighbours[2] = node-B+1;						
		L_lim  = 3;
	}

	else if(x == L-1 && y == B-1)//Bottom Right	
	{
		neighbours = new (nothrow) int[3];
		neighbours[0] = node+B;
		neighbours[1] = node +B -1;
		neighbours[2] = node-1;						
		L_lim  = 3;
	}	

	else if(x == 0 && y == B-1)//Top Right
	{
		//int neighbours[3] = {node-B,node-1,node-B-1};		
		neighbours = new (nothrow) int[3];
		neighbours[0] = node-B;
		neighbours[1] = node  - 1;
		neighbours[2] = node-B-1;						
		L_lim  = 3;		
	}

	else if(y == 0 && x != L-1 && x!= 0)//Left Column
	{
		//int neighbours[5] = {node+1,node+B,node+B-1,node-B,node-B-1};		
		neighbours = new (nothrow) int[5];
		neighbours[0] = node+B;
		neighbours[1] = node +1;
		neighbours[2] = node+B+1;
		neighbours[3] = node-B;
		neighbours[4] = node - B + 1;						
		L_lim  = 5;		
	}

	else if(y == B-1 && x != L-1 && x!= 0)//Right Column
	{
		//int neighbours[5] = {node-1,node+B,node+B-1,node-B,node-B-1};		
		neighbours = new (nothrow) int[5];
		neighbours[0] = node+B;
		neighbours[1] = node -1;
		neighbours[2] = node+B-1;
		neighbours[3] = node-B;
		neighbours[4] = node - B - 1;						
		L_lim  = 5;					
	}

	else if(x == L-1 && y != 0 && y!= B-1)//Bottom Row
	{
		//int neighbours[5] = {node+1,node+B,node+B+1,node+B-1,node-1};		

		neighbours = new (nothrow) int[5];
		neighbours[0] = node+B;
		neighbours[1] = node +1;
		neighbours[2] = node+B+1;
		neighbours[3] = node-1;
		neighbours[4] = node + B - 1;						
		L_lim  = 5;		
	}

	else if(x == 0 && y != 0 && y!= B-1)//Top Row
	{
		//int neighbours[5] = {node+1,node-B,node-B+1,node-1,node-B-1};		

		neighbours = new (nothrow) int[5];
		neighbours[0] = node-B;
		neighbours[1] = node +1;
		neighbours[2] = node-B-1;
		neighbours[3] = node-1;
		neighbours[4] = node - B + 1;						
		L_lim  = 5;		

	}

	else
	{
		//int NEIGH[8] = {node+1, node-1, node+B, node-B, node+B+1, node+B-1, node-B-1, node-B+1};		
		neighbours= new (nothrow) int[8];
		
		neighbours[0] = node+1;
		neighbours[1] = node-1;
		neighbours[2] = node+B;
		neighbours[3] = node-B;
		neighbours[4] = node+B+1;
		neighbours[5] = node+B-1;
		neighbours[6] = node-B-1;
		neighbours[7] = node-B+1;
		

		L_lim = 8;
		
	}


	N1.first = neighbours;		
	N1.second = L_lim;
	return N1;

}


void INIT()
{
	int iter, neighIter;
	float hCost;
	float defaultRHS;
	float k1,k2;
	KEY_TYPE tempKEY;
	defaultRHS = INF;
	int currentNeighbour;

	for (iter = 0; iter < L*B; iter ++)	
	{
		nodeList[iter].gScore = INF;
		nodeList[iter].nodeId = iter;
	}	
    
    // init the startNode 
	nodeList[startNode].rhsValue = 0;
	nodeList[startNode].KEY.second = min(nodeList[startNode].rhsValue, nodeList[startNode].gScore);	
    hCost = heuristic_cost(startNode, endNode);
	nodeList[startNode].KEY.first = hCost + nodeList[startNode].KEY.second;  
	

	//init all the rhs values
	for (iter = 0; iter < L*B; iter ++)	
	{
		if (iter == startNode)
			continue;

		defaultRHS = INF;	

		//get the neighbours of the particular node \
		nextToMe_INIT = generateNeighbour(iter);

		for (neighIter = 0; neighIter<nextToMe_INIT.second; neighIter++)
		{
			//assign respective nodeID
			currentNeighbour = nextToMe_INIT.first[neighIter];

			//check if that neighbour is an obstacle
			if(nodeList[currentNeighbour].obstacle)
			{
				continue;
			}
			else
			{				
				nodeList[iter].rhsValue = nodeList[currentNeighbour].gScore + heuristic_cost(iter,currentNeighbour);
				if (nodeList[iter].gScore == INF)
					nodeList[iter].rhsValue = INF;
			}					
			
			if (nodeList[iter].rhsValue < defaultRHS)
				defaultRHS = nodeList[iter].rhsValue;

			nodeList[iter].rhsValue = defaultRHS;
		}
	}

	//init all keys
	for(iter = 0; iter < L*B; iter++)
	{
		

		//calcualte k_2 of KEY
		k2 = min(nodeList[iter].gScore,nodeList[iter].rhsValue);

		//calcualte k1 as h(s) + k2
		k1  = heuristic_cost(iter,endNode) + k2;

		tempKEY = make_pair(k1,k2);
		nodeList[iter].KEY = tempKEY;

	}		

	//push the startNode in the priority queue
	nodeQueue NQ;
	NQ.nodeId = startNode;
	NQ.KEY = nodeList[startNode].KEY;
	priorityQueue.insert(priorityQueue.begin() + 0, NQ);

	// NQ.nodeId = 666;
	// NQ.KEY.first = 5.65685;
	// NQ.KEY.second = 1;
	// priorityQueue.push_back(NQ);

	// NQ.nodeId = 655;
	// NQ.KEY.first = 5.65685;
	// NQ.KEY.second = 2;
	// priorityQueue.push_back(NQ);



}



KEY_TYPE calculateKey(int nodeId)
{
	KEY_TYPE tempKey;
	int hCost;
	tempKey.second = min(nodeList[nodeId].rhsValue, nodeList[nodeId].gScore);	
	hCost = heuristic_cost(nodeId, endNode);
	tempKey.first = hCost + tempKey.second;
	return tempKey;  

}

bool keyCompare()
{
	KEY_TYPE topKey, goalKey;
	topKey = priorityQueue.front().KEY;
	goalKey = calculateKey(endNode);


	if (topKey.first == goalKey.first)
   		return (topKey.second < goalKey.second || topKey.second == goalKey.second) ; //lower key comes first
   	else
   		return (topKey.first < goalKey.first );
}



void updateVertex(Nodes s)
{

	int iter, neighIter, currentNeighbour;
	float defaultRHS, hCost, bestRhsValue;
	float tempF;
	iter = s.nodeId;
	std::vector <float> rhsOptions;

	if(s.nodeId != startNode)
	{
		//for every new neighbour, ensure that the defaultRHS is INF
		defaultRHS = INF;	

		//get neighbours of that particular neighbour itself(to find RHSValue)
		nextToMe_uV = generateNeighbour(s.nodeId);
		
		//get the neighbours of the particular node \
		//nextToMe_uV = generateNeighbour(s.nodeId);

		for ( neighIter = 0; neighIter<nextToMe_uV.second; neighIter++)
		{
			//assign from the nodeList
			currentNeighbour = nextToMe_uV.first[neighIter];

			//check if that neighbour is an obstacle
			if(nodeList[currentNeighbour].obstacle)
			{
				continue;
			}
			else
			{				
				tempF = nodeList[currentNeighbour].gScore + heuristic_cost(iter,currentNeighbour);
				if (nodeList[iter].obstacle)
					tempF = INF;
				if (nodeList[currentNeighbour].obstacle)
					tempF = INF;
				if (nodeList[currentNeighbour].gScore == INF)
					tempF = INF;							
		    }
		    rhsOptions.push_back(tempF);

			// if (nodeList[iter].rhsValue < defaultRHS)
			// 	defaultRHS = nodeList[iter].rhsValue;

			// //ensure that the rhsValue assigned at the end will be the minimum. 
			// //This statement could be placed even at the end of the `for' loop
			// nodeList[iter].rhsValue = defaultRHS;
	    }

	    bestRhsValue = *min_element(rhsOptions.begin(),rhsOptions.end());
	    //tempF = rhsOptions;

	}

	//update rhsValue
	nodeList[iter].rhsValue = bestRhsValue;

	//Remove the particular node from the priorityQ
	nodeQueue result;
	vector<nodeQueue>::iterator iterNQ = find_if(priorityQueue.begin(), priorityQueue.end(), [&iter] (nodeQueue tempNQ) 	
	 																				{ return tempNQ.nodeId == iter; } );
	int idx;
	idx = iterNQ - priorityQueue.begin();
	result = *iterNQ;

	if (idx != priorityQueue.size()) //indicates that the element is found
		priorityQueue.erase(priorityQueue.begin()+idx);

	//Insert the vertex if it is locally inconsistent
	nodeQueue tempNQ;
	if(!(nodeList[iter].obstacle))
	{
		if(nodeList[iter].gScore != nodeList[iter].rhsValue)
		{
			//updateKey
			nodeList[iter].KEY.second = min(nodeList[iter].rhsValue, nodeList[iter].gScore);	
	    	hCost = heuristic_cost(s.nodeId, endNode);
			nodeList[iter].KEY.first = hCost + nodeList[iter].KEY.second;  
			
			tempNQ.nodeId = s.nodeId;
			tempNQ.KEY = nodeList[iter].KEY;
			priorityQueue.push_back(tempNQ);
		}		
	}
	

}


void forAllNeighbors(Nodes u)
{
	// This function calculates all the neighbours of the particular node u.
	// It will then perform the updateVertex funciton to all of the neighbours
	
	int currentNeighbour;

	nextToMe_faN = generateNeighbour(u.nodeId);

	for (int neighIter = 0; neighIter<nextToMe_faN.second; neighIter++)
	{
		//assign from the nodeList
		currentNeighbour = nextToMe_faN.first[neighIter];

		//check if that neighbour is an obstacle
		if(nodeList[currentNeighbour].obstacle)
			continue;			
		else
			updateVertex(nodeList[currentNeighbour]);		

	}
}

void computeShortestPath()
{
	KEY_TYPE topKey, goalKey;
	bool flagKey;

	nodeQueue u;
	Nodes currentNode;
	bool ans;
	char userInput;

	//sort the priorityQueue. 
	sort(priorityQueue.begin(), priorityQueue.end(),pairCompare);


		topKey = priorityQueue.front().KEY;
	goalKey = calculateKey(endNode);



	if (topKey.first == goalKey.first)
  			flagKey =  (topKey.second < goalKey.second || topKey.second == goalKey.second) ; //lower key comes first
  	 else
   			flagKey =  (topKey.first < goalKey.first );


	while(flagKey  ||  nodeList[endNode].rhsValue != nodeList[endNode].gScore)
	{	
		//sort the priorityQueue. 
		sort(priorityQueue.begin(), priorityQueue.end(),pairCompare);

		//take out the first node in the priorityQ		
		u = priorityQueue.front();
		currentNode = nodeList[u.nodeId]; 

		//delte element from the Q
		priorityQueue.erase(priorityQueue.begin() + 0);

		if(currentNode.gScore > currentNode.rhsValue)
		{
			nodeList[currentNode.nodeId].gScore = currentNode.rhsValue;
			forAllNeighbors(currentNode);			
		}	
		else
		{
			nodeList[currentNode.nodeId].gScore = INF;
			updateVertex(currentNode);
			forAllNeighbors(currentNode);
			
		}

		// cout<<"PrintPQ?\n";
		// cin>>userInput;
		// if(userInput == 'Y' || userInput == 'y')
		// 	printPQ();

		// cout<<currentNode.nodeId<<"\n";
		// cout<<keyCompare()<<"\n";
		// cout<<(nodeList[endNode].rhsValue != nodeList[endNode].gScore)<<"\n\n";

		sort(priorityQueue.begin(), priorityQueue.end(),pairCompare);
		
		topKey = priorityQueue.front().KEY;
		goalKey = calculateKey(endNode);

		if (topKey.first == goalKey.first)
   			flagKey =  (topKey.second < goalKey.second || topKey.second == goalKey.second) ; //lower key comes first
  		 else
   			flagKey =  (topKey.first < goalKey.first );



	}
}