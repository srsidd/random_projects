function Gcost = getGscore(start)
% Function to generate the Gcost of the current node. Get's the Gcost of
% the individual nodes in the individual configuration spaces
%%%% Takes in the current position in the joint configuration space
%%%% Returns the Gcost got from the map for each position
global Gscore; 

Gcost = 0;
% For each robot, get the gcost from the map
for i = 1:2:length(start)-1
    x = start{i};
    y = start{i+1};
    index = sub2ind(size(Gscore),x,y);
    Gcost(floor(i/2)+1) = cell2mat(Gscore(index));
end