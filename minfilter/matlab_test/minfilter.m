r=12;c=20;
C_min=zeros(r,c);
A=textread('in.txt');%A[c*r,1]������
B=reshape(A,c,r);%ʵ���˾����ת��
C=B';%��ת�þ��󣬱��ԭ����

%��Сֵ�˲�����
% for i=1:r
%     se1 = strel('rectangle',[1 3]);
%     C_min(i,:)=imerode(C(i,:),se1,'same'); %erode
% end
%��Сֵ�˲�����
% for i=1:c
%     se1 = strel('rectangle',[7 1]);
%     C_min(:,i)=imerode(C(:,i),se1,'same'); %erode
% end
%��Сֵ�˲�����&��
se1 = strel('square',7);
C_min=imerode(C,se1,'same'); %erode
