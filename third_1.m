x=-pi:1/100:pi;
y=sin(x)+cos(10.*x);
plot(x,y,'-.r')
xlim([-pi,pi])
title('函数')