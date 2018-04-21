array=round(255*rand(12,20));
[r,c]=size(array);
fid=fopen('in.txt','w');
for i=1:r
    for j=1:c
        if j==c
            fprintf(fid,'%d\r\n',array(i,j));%如果是最后一个，就换行
        else
            fprintf(fid,'%d\r\t',array(i,j));%如果不是最后一个，就tab
        end
    end

end
fclose(fid);%fid[r,c]





