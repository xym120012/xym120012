A=[1,-1,1;
   2,1,1;
   1,-1,-2]
B=[1;2;-4]
A_trace=trace(A)
A_rank=rank(A)
A_inv=inv(A)
x=inv(A)*B