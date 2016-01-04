clc
close all
clear all
clear global

set(0,'RecursionLimit',1000);

%% initializations
% Define global variables
global ConfigSpace;             % Joint configuration space
global NumRobots;               % Number of robots
global MapSize;                 % Size of map to be used
global Gscore;                  % Gcost of the combined system
global OptGraph;                % Optimal graph returned from Dijkstra search
global OptCosts;                % Optimal costs of each node returned by Dijkstra search
global goal;                    % Goal point the robot should traverse to

% Define map size
MapSize = 50;

% Define the joint config space as the combination of each robot's
% ConfigSpace (Individual config space = MapSize*MapSize)

ConfigSpace = [MapSize, MapSize, MapSize, MapSize, MapSize, MapSize, MapSize, MapSize];

% Other initializations
NumRobots = 4;
Cur = num2cell(zeros(1,length(ConfigSpace)));       % To keep track of the current position
numNeighbors = 8;                                   % Number of neighbors

% Generate random cost map
Gscore = num2cell(gen_costs(MapSize, MapSize, .05));
inf = max(max(cell2mat(Gscore)));

% Define the start point and end point as (x;y;) for each robot
start = {31;15;
    45;15;
    18;1;
    1;7};

goal =  {1;1;
    15;1
    8;15
    10;15};

% Set up a variable to store all the optimum trajectories
OptimumTrajectories  = [];

%% Conduct Dijkstra search and find the optimum trajectory for each robot
for i = 1:2:length(start)-1
    startX = cell2mat(start(i));
    startY = cell2mat(start(i+1));
    
    goalX = cell2mat(goal(i));
    goalY = cell2mat(goal(i+1));
    
    [Graph, Costs] = Dijkstra_search_Coordinates([startX,startY], [goalX,goalY]);
    OptGraph(floor(i/2)+1,:) = Graph;
    OptCosts(floor(i/2)+1,:) = Costs;
end

%% Begin M* search

% Initialize the Gcost and Fcost for the starting point
Fscore = getGscore(start) + HcostEstimateMultiple(start,goal);

% Add the starting element to the open set
Openset.cost = sum(Fscore);
Openset.ind = sub2ind(ConfigSpace, start{:});
closedset.ind = [];
Backset =  containers.Map('KeyType','double', 'ValueType','any');
CollisionSet = containers.Map('KeyType','double', 'ValueType','any');
Camefrom =  containers.Map('KeyType','double', 'ValueType','any');

while(1)
    NotCollidingRobots = [];
    
    % Select the node with the least cost
    [~, bestKey] = min(Openset.cost);
    current = Openset.ind(bestKey);
    [Cur{:}] = ind2sub(ConfigSpace, current)
    Fscore = getGscore(Cur) + HcostEstimateMultiple(Cur,goal);
    
    % Check if the goal has been reached
    if(current == sub2ind(ConfigSpace, goal{:}))
        disp('path found');
        retraceMstar(goal, Camefrom, start);
        break;
    end
    
    % Identify the colliding robots and their collision points
    [CollidingRobotIndices, CollidingRobots] = findCollidingRobots(Cur);
    
    % Update the collision set
    if CollidingRobots
        % If a collision has been detected, skip this vertex
        % Remove current from the open set and add it to the closed set
        closedset.ind = [closedset.ind, current];
        Openset.cost(bestKey) = [];
        Openset.ind(bestKey) = [];
        continue;
    end
    
    %     [NeighDist, neighbors] = getNeighbors(Cur,CollisionSet);
    [NeighDist, neighbors] = getNeighborsNEWONE(Cur,CollisionSet);
    
    % Remove current from the open set and add it to the closed set
    closedset.ind = [closedset.ind, current];
    Openset.cost(bestKey) = [];
    Openset.ind(bestKey) = [];
    
    for i = 1:numel(neighbors)
        % Get the neighbours for each robot
        neigh = cell2mat(neighbors(i));
        
        % Convert it to the appropriate format
        neigh = reshape(neigh',1,(NumRobots*2));
        NeighCell = num2cell(neigh);
        
        % Get the index of the neighbor in the config space
        Neighind = sub2ind(ConfigSpace,  NeighCell{:});
        
        % Add the current state to the backset
        if cell2mat(Backset.keys) == Neighind
            Backset(Neighind) = [Backset(Neighind) current];
            Backset(Neighind) = unique(Backset(Neighind));
        else
            Backset(Neighind) = current;
            Backset(Neighind) = unique(Backset(Neighind));
        end
        
        % Find if any of the neighbors robots are involved in collision
        [CollidingRobotIndices, CollidingRobots] = findCollidingRobots(NeighCell);
        
        % Update the collision set if any collisions are present
        if CollidingRobots
            if cell2mat(CollisionSet.keys)==Neighind
                CollisionSet(Neighind) = [CollisionSet(Neighind), CollidingRobots];
            else
                CollisionSet(Neighind) = CollidingRobots;
            end
        end
        
        % Update the Gcost and Fcost for the current neighbor
        FscoreNeighbor = getGscore(NeighCell) + HcostEstimateMultiple(NeighCell, goal);
        
        % Perform BackPropogation
        [current, Neighind, goal, CollisionSet, Openset, Backset] = backProp(current, Neighind, goal, CollisionSet, Openset, Backset);
        
        % Update the cost if required
        if sum(Fscore+NeighDist(i)) < sum(FscoreNeighbor)
            FscoreNeighbor = Fscore+NeighDist(i);
        end
        
        % Add neighbor to the openset if it is not present
        if isempty(Openset.ind)
            Openset.ind = [Openset.ind; Neighind];
            Openset.cost = [Openset.cost; sum(FscoreNeighbor)];
        end
        if ~sum(Openset.ind == Neighind)
            Openset.ind = [Openset.ind; Neighind];
            Openset.cost = [Openset.cost; sum(FscoreNeighbor)];
        end
        % Keep track of the best way to goal
        if sum(cell2mat(Camefrom.keys) == Neighind)
            continue;
        else
            Camefrom(Neighind) = current;
        end
    end
end
