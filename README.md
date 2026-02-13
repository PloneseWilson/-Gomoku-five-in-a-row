# -Gomoku-five-in-a-row

A bot written by myself partly based on Monte Carlo Tree Search(MCTS)  
so that it can run on laptops with normal CPU  

check out Gomoku.cpp

-----------------------------------------------  
structure functions:  
UCB  
select  
expand  
simulate   
backpropagate   
  
-----------------------------------------------  
other functions:  

legalmove:find valid next move  


wincheck: check win      


scorecheck: compute the value of a step  


walk: just a while loop function  


apply: place a step  
  

prt: print the board  


 etc    

-----------------------------------------------  

If you have great CPU, you can change the iter_cnt at line 17 in Gomoku.cpp   
which is the number of attempts the program will compute each time

:)  
