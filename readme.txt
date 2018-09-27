CSCI 103 Programming Assignment 2, Chroma Key, Fall 2014

Name:Minxuan Song

Email Address: minxuans@usc.edu

NOTE: You can delete the questions, we only need your responses.

=============================== Prelab =======================================

Pixel                |    RGB Value     |  Distance from Chroma Key
-------------------------------------------------------------------
Top-left background  | ( 68  ,  142  , 21   )  |  n/a
Arm                  | (  255 , 172   ,  140  )  | 224
Vest                 | (  27 ,  32  , 28   )  | 118
Shirt                | (   253,  213  ,243    )  | 298

================================== Review ===================================
1. Discuss and justify which pixels you chose to compute the average 
background value for method 1. Was there a reason not to choose more or
fewer pixels?

Response 1: I used 20 pixels from the top corners which were determined by using 2 for loops. Had the pixels been fewer, the program's judgement of the background may be inaccurate. However, if I take more pixels, I may accidentally run into the foreground, which may result in even worse outcomes.

2. For method 1, do some experiments to find the range of distance thresholds 
for which the program seems to operate the best. You may use different 
thresholds for the two different sample images (Colbert and Bird). 
Note: threshold values that are too low will cause certain portions of the 
chroma key to stay in the picture; values that are too high will cause parts 
of the foreground image to disappear.

Response 2:

  Image                  Min Threshold           Max Threshold
  Colbert range:  from       30          to         70
  Bird range:     from        20           to       75


3. For method 2, explain what you implemented and why.  How did you go about 
implementing it? Walk us through a high-level description of what you did in 
your code (and use comments in the actual .cpp file to fill in the details). 
What other alternatives did you consider either before or after you
implemented your selected method?  What are the relative pros and cons of 
these methods? [This question is open-ended!]

Response 3:For method 2, I used 2 for loops to take in 20 points in the top left corner, and for all the points taken, I'll make the program automatically collect the datas for the highest value and the lowest value separately for R, G and B channel. After that, I'll calculate the differences in value between MaxR and MinR, MaxG and MinG and MaxB and MinB and keep track of that value. Then, I'll add 20 to each of the values calculated as a mean to offset uncertainties, in other words deviations. During the process, I have also conceived of another way, which is to measure all the points' RGB value and automatically solve out the distribution of these points, figuring out the backgrounds automatically by graphing them out. This method I reckon should be the most logical way to do it, since the program will successfully run even if the top left corner is filled with foreground. However, I couldn't think of a way to simply code it out by the knowledge I now have, so I took the previous approach.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:

Do you have any other remarks?

:
