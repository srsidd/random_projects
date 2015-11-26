function [NeighDist, Retneighbors] = getNeighbors(Cur,CollisionSet)
% Function to get neigboring nodes for each robot from their respective
% current positions
%%%% Takes in the current position in the joint configuration space and the
%%%% collision set at the current position
%%%% Returns the Neighboring positions for each robot along with costs
global NumRobots;
global MapSize;
global goal;
global ConfigSpace;

CurrentRobotPoints = reshape(cell2mat(Cur), 2,NumRobots)';

% Maintain an array of the neighbors for robot to transit to
neighbors = [1,0;
    1,1;
    0,1;
    -1,1,;
    -1, 0;
    -1,-1;
    0,-1;
    1,-1];

numNeighbors = 8;                                               % Number of neighbors
Dist = [1,sqrt(2),1,sqrt(2),1,sqrt(2),1,sqrt(2),0];             % Distance from current to each neighbor
current = sub2ind(ConfigSpace, Cur{:});

CollidedRobots = [];
NonCollidedRobots = [];
% Check thecollision set to see if there was a collision at the current node previously
if ~isempty(find(cell2mat(CollisionSet.keys) == current))
    CollidedRobots = CollisionSet(current);
end

% If there are no collisions get the neighbors from the optimal search of
% Dijkstra's search performed earlier
if isempty(CollidedRobots)
    [NeighDist, neigh] = findNoncollidingNeighbours(1:NumRobots, CurrentRobotPoints);
    Retneighbors = {neigh};
    return;
end

temp = CurrentRobotPoints;
% Keep track of the robots not involved in the collision.
for i = 1:NumRobots
    if i == CollidedRobots
        continue;
    end
    NonCollidedRobots = [NonCollidedRobots, i];
end

% For all robots not involved in collision get the neighbors from the optimal search of
% Dijkstra's search performed earlier
p = 1;
for i = 1:length(NonCollidedRobots)
    Robot = NonCollidedRobots(i);
    [NeighDistance, neigh] = findNoncollidingNeighbours(Robot, CurrentRobotPoints(Robot,:));
    temp(Robot,:) = neigh;
    tempDist(Robot) = NeighDistance;
    Retneighbors(p) = {temp};
    NeighDist(p) = tempDist(Robot);
    p = p+1;
end

temp = CurrentRobotPoints;
% Keep track of the collided robots
CollidedRobotPoints = temp(CollidedRobots,:)
CollidedRobotPoints = reshape(CollidedRobotPoints,1,2*length(CollidedRobots));

% For each of the robots involved in collision search the individual
% neighbors in the joint config space to find a non colliding node
for i = 1:length(CollidedRobots)
    Robot = CollidedRobots(i);
    PointX = CurrentRobotPoints(Robot,1);
    PointY = CurrentRobotPoints(Robot,2);
    for n = 1:numNeighbors
        tempNeigh(1) = PointX + neighbors(n,1);
        tempNeigh(2) = PointY + neighbors(n,2);
        if tempNeigh(1) < 1 || tempNeigh(2) < 1 || tempNeigh(1) > MapSize || tempNeigh(2) > MapSize
            continue;
        end
        temp(Robot,:) = tempNeigh;
        tempDist(Robot) = Dist(n);
        Retneighbors(p) = {temp};
        p = p+1;
        NeighDist(p) = tempDist(Robot);
    end
end
