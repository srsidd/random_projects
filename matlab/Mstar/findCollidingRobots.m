function [CollidingRobotIndices, CollidingRobots] = findCollidingRobots(Cur)
% Function to check and find all robots involved in a collision at a node
%%%% Takes in the current position in the joint configuration space
%%%% Returns the robots involved in the collision along with their indices
global ConfigSpace;

% Get the x and y coordinates for each robot position
for i = 1:2:length(Cur)-1
    x(floor(i/2)+1) = Cur{i};
    y(floor(i/2)+1) = Cur{i+1};
end

CollidingRobots = [0, 0];

% If the x and y coordinates for two robots are the same, they are colliding
for i = 1:length(x)
    for j = i+1:length(x)
        if x(i) == x(j) && y(i) == y(j)
            CollidingRobots = [CollidingRobots; i, j];
        end
    end
end
CollidingRobots(find(CollidingRobots(:,1)==0),:)=[];
CollidingRobotIndices = CollidingRobots;
CollidingRobots = unique(CollidingRobots);
