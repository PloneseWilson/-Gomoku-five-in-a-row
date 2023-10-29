# -Gomoku-five-in-a-row
自己基於蒙地卡羅樹搜索(MCTS)上修改的bot 以確保能在文書機等級CPU上運行  
A bot written by myself partly based on Monte Carlo Tree Search(MCTS)  
so that it can run on laptops with normal CPU  

check out Gomoku.cpp

-----------------------------------------------  
5個主要的架構函數/structure functions:  
UCB  
select  
expand  
simulate   
backpropagate   
  
-----------------------------------------------  
以及一些其他的函數/other functions:  

legalmove:find valid next move  
選擇合法的下一步，減少計算量的選擇函數

wincheck: check win      
判斷是否勝利

scorecheck: compute the value of a step  
判斷該步的價值  

walk: just a while loop function  
方便寫wincheck/scorecheck函數而封裝的while循環  

apply: place a step  
落下該步  

prt: print the board  
輸出棋盤  

等等函數 etc    

-----------------------------------------------  
如果你的電腦性能很好，可以去修改程式第17行的iter_cnt值  
這是每一步程式嘗試的次數  

If you have great CPU, you can change the iter_cnt at line 17  
which is the number of attempts the program will compute each time

當然仍有很多待改善的地方，慢慢改進:)  
