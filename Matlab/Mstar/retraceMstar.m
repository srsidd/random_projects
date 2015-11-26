function retraceMstar(goal, Camefrom, start)
% Function to trace back the points searched from the goal to the start and
% to display the goals to be taken by the robots.
%%%% Takes in the start point and goal point in the joint configuration
%%%% space and the cameFrom set that keeps track of the robot search
%%%% Returns nothing

global ConfigSpace;
global NumRobots;
global Gscore;

% Convert from points to indices
startInd = sub2ind(ConfigSpace, start{:});
goalInd =  sub2ind(ConfigSpace, goal{:});

Cur = num2cell(zeros(1,length(ConfigSpace)));
TotalPath = goalInd;
temp = goalInd;
while temp ~= startInd
    retrace = Camefrom(temp);
    TotalPath = [TotalPath; retrace];
    temp = retrace;
end
TotalPath = [TotalPath; startInd];
TotalPath = flipud(TotalPath);
figure,
imagesc(cell2mat(Gscore));
colormap(gray);
for i = 1:length(TotalPath)
    [Cur{:}] = ind2sub(ConfigSpace, TotalPath(i))
    Path = reshape(cell2mat(Cur), 2,NumRobots)';
    hold on
    plot(Path(1,1),Path(1,2),'or','MarkerSize',5);
    hold on
    plot(Path(2,1),Path(2,2),'ob','MarkerSize',5);
    hold on
    plot(Path(3,1),Path(3,2),'om','MarkerSize',5);
    hold on
    plot(Path(4,1),Path(4,2),'og','MarkerSize',5);
    hold on
    %     plot(Path(5,1),Path(5,2),'ow','MarkerSize',5);
    %     hold on
    %     plot(Path(6,1),Path(6,2),'oy','MarkerSize',5);
    drawnow;
    pause(1);
end

