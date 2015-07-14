
img = imread('test2.png');
ycc = rgb2ycbcr(img);
fid = fopen('output1.txt', 'w');
if fid == -1, error('Cannot open file'); end
% store image paramenters as first 3 values
% row col num_matrices
fprintf(fid, '%d %d %d ', size(ycc));  % Assuming it is an RGB image
fprintf(fid, '%g ', ycc(:));
fclose(fid);

fid = fopen('rgb_out.txt', 'r');
if fid == -1, error('Cannot open file'); end
x = fscanf(fid, '%d ', 1);
y = fscanf(fid, '%d ', 1);
z = fscanf(fid, '%d ', 1);
ImgData = fscanf(fid, '%g ', Inf);
Img     = reshape(ImgData, x, y, z);
fclose(fid);

ImgInt = double(Img/255);
