# -Gomoku-five-in-a-row
自己基於蒙地卡羅樹搜索(MCST)上修改的bot 以確保能在文書機等級CPU上運行  
  
5個主要的架構函數  
UCB  
select  
expand  
simulate   
backpropagate   
  
以及一些其他的函數  
legalmove:減少計算量的選擇函數  
wincheck:判斷是否勝利  
scorecheck:判斷該步的價值  
walk:方便寫wincheck/scorecheck函數而封裝的while循環  
apply:落下該步  
prt:輸出棋盤  
等等函數  
  
如果你的電腦性能很好，可以去修改程式第17行的iter_cnt值  
這是每一步程式嘗試的次數  
  
當然仍有很多待改善的地方，慢慢改進:)  
