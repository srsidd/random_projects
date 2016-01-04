function CollidingPoints = findCollidingPoints(Cur)
% Function to check if any robots are involved in a collision and return
% the individual points at which the collisionsoccur
%%%% Takes in a position in the joint configuration space
%%%% Returns an array having all the points involved in robot collision
global ConfigSpace;

% Get the individual x and y coordinates for each position
for i = 1:2:length(Cur)-1
    x(floor(i/2)+1) = Cur{i};
    y(floor(i/2)+1) = Cur{i+1};
end

CollidingPoints = [0,0];
cntr = 1;
% Collision occurs if the x and y coordinates of two points are the same
for i = 1:length(x)
    for j = i+1:length(x)
        if x(i) == x(j) && y(i) == y(j)
            CollidingPoints(cntr,1) = x(j);
            CollidingPoints(cntr,2) = y(j);
            cntr = cntr+1;
        end
    end
end
CollidingPoints(find(CollidingPoints(:,1)==0),:) = [];
