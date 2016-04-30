Extensively modified by Chris. c_svm algorithm from dlib library. 

1. Takes in training data from "AchSheet.csv". 

2. Based on the training data, outputs cross validation results of different c and gamma values for manual selection. 

3. Based on selected c and gamma values, creates a classification model and saves it in "achievement_result.dat" or "immersion_result.dat". 

4. Processes test cases in AchTest.csv and outputs a constant value, positive or negative values that show classification result.


Installation and run instructions.

1. Create new project in VS2015.

2. Remove main cpp files, if any.

3. Replace files in project with contents of this folder.

4. Go to project properties -> VC++ Directories. Include the project folder path in the "Include Directories".

5. Run the program.


