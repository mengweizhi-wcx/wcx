array=round(255*rand(12,20));
[r,c]=size(array);
fid=fopen('in.txt','w');
for i=1:r
    for j=1:c
        if j==c
            fprintf(fid,'%d\r\n',array(i,j));%��������һ�����ͻ���
        else
            fprintf(fid,'%d\r\t',array(i,j));%����������һ������tab
        end
    end

end
fclose(fid);%fid[r,c]





