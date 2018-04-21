r=12;c=20;
C_min=zeros(r,c);
A=textread('in.txt');%A[c*r,1]列向量
B=reshape(A,c,r);%实现了矩阵的转置
C=B';%再转置矩阵，变成原矩阵

%最小值滤波：行
% for i=1:r
%     se1 = strel('rectangle',[1 3]);
%     C_min(i,:)=imerode(C(i,:),se1,'same'); %erode
% end
%最小值滤波：列
% for i=1:c
%     se1 = strel('rectangle',[7 1]);
%     C_min(:,i)=imerode(C(:,i),se1,'same'); %erode
% end
%最小值滤波：行&列
se1 = strel('square',7);
C_min=imerode(C,se1,'same'); %erode
