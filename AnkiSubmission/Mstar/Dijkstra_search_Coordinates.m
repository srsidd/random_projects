function [Graph, Costs] = Dijkstra_search_Coordinates(goal, start)
% Function to perform Dijkstra's search between any two given points for
% each individual robot within their individual configuration spaces
%%%% Takes in a 2-D x,y start and goal position.
%%%% Returns the optimal trajecory along with the completely explored graph

global Gscore;

inf = 1000;

Qind = [];
[r,c] = size(Gscore);

% Define the neighbours to search over
neighbors = [1,0;
    1,1;
    0,1;
    -1,1,;
    -1, 0;
    -1,-1;
    0,-1;
    1,-1];
numNeighbors = 8;
neighDist = [1,sqrt(2),1,sqrt(2),1,sqrt(2),1,sqrt(2),0];

% Convert from points to indices
startInd = sub2ind(size(Gscore), start(1), start(2));
goalInd =  sub2ind(size(Gscore), goal(1), goal(2));

% Initialization, set all nodes as unvisited and make distances as infinity
for i = 1:r
    for j = 1:c
        ind = sub2ind(size(Gscore),j,i);
        if ind == startInd
            dist(ind) = 0;
            prev(ind) = 0;
            Costs(ind) = 0;
            Qind = [Qind ind];
        elseif ind ~= startInd
            dist(ind) = inf;
            prev(ind) = inf;
            Qind = [Qind ind];
        end
    end
end

% Initialize the Gcost and Fcost for the starting point
OrigQ = Qind;
while ~isempty(Qind)
    [CurDist, bestKey] = min(dist);
    current =  Qind(bestKey);
    [CurX, CurY] = ind2sub(size(Gscore),current);
    
    % Remove current from the open set and add it to the open set
    dist(bestKey) = [];
    Qind(bestKey) = [];
    
    % Search for best path to take
    for n = 1:numNeighbors
        % Find the neighbors
        NeighX(n) = (CurX+neighbors(n,1));
        NeighY(n) = (CurY+neighbors(n,2));
        
        if NeighX(n) < 1 || NeighY(n) < 1 || NeighX(n) > length(Gscore) || NeighY(n) > length(Gscore)
            continue;
        end
        
        neighInd(n) = sub2ind(size(Gscore), NeighX(n), NeighY(n));
        
        % Calculate the new Cost
        cost = CurDist+neighDist(n);
        
        if cost < dist(find(Qind==neighInd(n)))
            dist(find(Qind==neighInd(n))) = cost;
            Costs(find(OrigQ==neighInd(n))) = cost;
            prev(find(OrigQ==neighInd(n))) = current;
        end
    end
    
end
Totalpath = [];
[pathX, pathY] = ind2sub(size(Gscore),goalInd);
Totalpath = [pathX, pathY];

% Get the entire graph that was explored
for i = length(prev):-1:1
    temp = prev(goalInd);
    if temp == startInd
        break;
    end
    [pathX, pathY] = ind2sub(size(Gscore),temp);
    Totalpath = [Totalpath; pathX, pathY];
    goalInd = temp;
end
[pathX, pathY] = ind2sub(size(Gscore),startInd);
Totalpath = [Totalpath; pathX, pathY];
Totalpath = flipud(Totalpath);
Graph = prev;
