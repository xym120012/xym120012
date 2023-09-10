x=-6:0.1:6;
y=x';
q=sqrt(x.^2+y.^2);
z=sin(q)./q;
surf(x,y,z)