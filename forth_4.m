a=[1,2,0,6];
b=[0,2,4,1];
s=a+b
m=conv(a,b)
b=[2,4,1];
[q1,r1]=deconv(a,b)
[q2,r2]=deconv(b,a)

