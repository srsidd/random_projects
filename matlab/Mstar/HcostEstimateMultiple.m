function cost = HcostEstimateMultiple(start, goal)
% Function to calculate the Heuristic from the current point to the goal
% point for each robot. Using Euclidean distance as the heurisitic.
%%%% Takes in the two positions from the joint configuration space
%%%% Returns a cost value between the two points

global ConfigSpace;

% For each robot, find the cost of it's current position to it's respective goal
for i = 1:2:length(start)-1
    Startx = start{i};
    Starty = start{i+1};
    Goalx = goal{i};
    Goaly = goal{i+1};
    cost(floor(i/2)+1) = sqrt((Goalx-Startx).^2+(Goaly-Starty).^2);
end

