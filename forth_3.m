x=[-1,-0.96,-0.62,0.1,0.4,1];
y=[-1,-0.1512,0.386,0.4802,0.8838,1];
n=2;

while(n<=5)
    p=polyfit(x,y,n)
    n = n + 1;
    x1=-1:0.01:1;
    y1=polyval(p,x1);
    figure
    plot(x,y,".")
    hold on
    plot(x1,y1);
end