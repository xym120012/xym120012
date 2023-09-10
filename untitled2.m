x=-2:0.1:2;
y=x';
z1=x.^2+2*y.^2;
z2=0.*x+3-y.^2;
surf(x,y,z1);
hold on;
surf(x,y,z2)