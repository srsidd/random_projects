function [current, Neighind, goal, CollisionSet, Openset, Backset] = backProp(current, Neighind, goal, CollisionSet, Openset, Backset)
% Function to perform the backpropogation in M*, to propogate the collision
% back recursively
%%%% Taken in the current position in the joint space, the goal point, the indices of the neighbouring node, the
%%%% collision set at the current point, open set of nodes and the set of back propogated nodes
%%%% Returns the same arguments it takes in after updating them
global ConfigSpace;

Cur = num2cell(zeros(1,length(ConfigSpace)));
[Cur{:}] = ind2sub(ConfigSpace, current);

% Check if current is in the backset
if ~sum(cell2mat(Backset.keys) == current)
    return;
end

% Get the collision set of the current and the neighbor it cameFrom
if  sum(cell2mat(CollisionSet.keys)==current)
    Ck = CollisionSet(current);
else
    Ck = [];
end
if  sum(cell2mat(CollisionSet.keys)==Neighind)
    Cl = CollisionSet(Neighind);
else
    Cl = [];
end

% Update collision sets if required
if ~(isempty(Cl)) || ~(isempty(Ck))
    isSubset = all(ismember(Cl, Ck));
    if ~isSubset
        CollisionSet(current) = union(Cl,Ck);
        % Add node to openset if the collision set has changed
        if ~sum(Openset.ind==current)
            Openset.ind = [Openset.ind; current];
            Fscore = getGscore(Cur) + HcostEstimateMultiple(Cur, goal);
            Openset.cost = [Openset.cost; sum(Fscore)];
        end
        % For each neighbor that I cameFrom, backPropogate and update collision set
        BacksetIndices = Backset(current);
        for i = 1:length(BacksetIndices)
            CurrentBacksetIndex = BacksetIndices(i);
            [CurrentBacksetIndex, Neighind, goal, CollisionSet, Openset, Backset] = backProp(CurrentBacksetIndex, Neighind, goal, CollisionSet, Openset, Backset);
        end
    end
end
