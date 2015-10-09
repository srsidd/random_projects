function [NeighCosts, Neighbors] = findNoncollidingNeighbours(NotCollidingRobots, NotCollidingRobotPoints)
% Function that finds that neighbors for robots that are not involved in
% the collision. Neighbors are obtained from the optimal graphs that were
% produced from the Dijkstra's Search.
%%%% Takes in robots not involved in collision along with their current positions
%%%% Returns the neighbors for the robots in the same order along with their Gcosts

global ConfigSpace;
global OptGraph;
global OptCosts;
global Gscore;
global goal;
global NumRobots;

Cur = num2cell(zeros(1,length(ConfigSpace)));
goalneigh = cell2mat(reshape(goal,2,(NumRobots))');

% For each robot not involved in collision get the neighbor from the
% optimum Dijkstra map that has already been computed
for k = 1:length(NotCollidingRobots)
    lgoal = goalneigh(k,:);
    goalInd = sub2ind(size(Gscore), lgoal(1), lgoal(2));
    Curx = NotCollidingRobotPoints(k,1);
    Cury = NotCollidingRobotPoints(k,2);
    CurInd  = sub2ind(size(Gscore), Curx, Cury);
    CurRobot = NotCollidingRobots(k);
    
    CurRobotTraj = OptGraph(CurRobot,:);
    CurRobotCosts = OptCosts(CurRobot,:);
    
    % If the robot has reached the goal, don't assign new neighbors to it
    if CurInd == goalInd
        [Neighbors(k,1),Neighbors(k,2)] = ind2sub(size(Gscore),CurInd);
        NeighCosts(k) = 0;
        continue;
    end
    NextInd = CurRobotTraj(CurInd);
    [Neighbors(k,1),Neighbors(k,2)] = ind2sub(size(Gscore),NextInd);
    NeighCosts(k) = CurRobotCosts(CurInd);
end