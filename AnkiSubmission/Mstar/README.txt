Steps to run the code -
1. Unzip the folder and make sure all the files are in the same folder.
2. The main function is called "MStar2.m"
3. Open that in matlab, change your current directory to where the files are stored and run "MStar2.m"
4. The default configuration is to have 4 robots with a mapsize of 50
5. The above parameter can be changed along with the start and end points for each robot
6. The code is not very user friendly to change the parameters and I was not able to make the user input these parameters due to time constraints

Steps for changing parameters - 
1. To change the size of the map,
	In "MStar2.m", a global variable called MapSize is being intialized to 50 (Line 19)

2. To change start and end points for each robot,
	In "MStar2.m" two variales "start" and "goal" define these points (Lines 36 and 41)
	The points are listed such that start\goal = {x1; y1; x2; y2; x3; y3; x4; y4} where the x and y are the coordinates for each individual robot and in that order

3. To change the number of robots,
	The number of robots is being initialized by the variable "NumRobots" (Line 27)
	In addition to this, the joint configuration space should also be changed accordingly
	This is done by the "ConfigSpace" variable (Line 24). ConfigSpace is defined such that 
	ConfigSpace = {MapHeight1, MapWidth1, MapHeight2, MapWidth2, MapHeight3, MapWidth3, MapHeight4, MapWidth4}
	The number of start and end points (Lines 36 and 41) should be edited accordingly.


Please Note - There maybe corner cases and other edge cases I have not taken care of. This project was a short duration proof of concept and I was not able to optimize it and make it efficient.