a= imread('D:\muniat2.jpg')
v=im2double(a)
output1=1*(v.^0.5)
output2=1*(v.^1.5)
output3=1*(v.^3.0)
subplot(2,2,1)
imshow(a)
subplot(2,2,2)
imshow(output1)
subplot(2,2,3)
imshow(output2)
subplot(2,2,4)
imshow(output3)