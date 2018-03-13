Describe how and what each group member contributed for the past two weeks. If you are solo, 
these points will be part of the next section.

Christine: For the first week, I worked on making our AI give some random move without a heuristic, 
and I tried to do minimax. 
For the second week, I fixed the minimax and worked on returning a move that used alpha beta pruning.

Tarini: For the first week, I worked on making our heuristic. And for the second week, I
made the heuristic "better". 



Document the improvements that your group made to your AI to make it tournament-worthy. Explain why 
you think your strategy(s) will work. Feel free to discuss any ideas were tried but didn't work out.

We made the heuristic better by considering frontier flips, creeping edges, and the opponent's pieces 
on edges. Reducing the number of frontier flips increases mobility, and considering the opponent's 
pieces on edges reduces the change that we will get flipped. Also, creeping edges are a good strategy
to consider (sometimes). 
We also used alpha-beta pruning, which should make it able to go deeper into the minimax
tree and at a quicker speed.