% read image & plot original

% Input image:
InputImageFile = '../data/FEUPin.jpg';

% Export to text file, ASCII, one image line per text line
OutputTextFile = '../data/datain.txt';

% Export to C include file:
CIncludeFile   = '../aship/datain.h';

i1 = imread( InputImageFile );
figure(1);
imshow( i1 );

imagesize = size( i1 );
NROWS = imagesize(1);
NCOLS = imagesize(2);

% Select a 512x512 image window:
NROWS1 = 512;
NCOLS1 = 512;
START_ROW = 1200;
START_COL = 2750;

% Uncomment to use the whole image:
%NROWS1 = NROWS;
%NCOLS1 = NCOLS;
% 
%START_ROW = 1;
%START_COL = 1;

% convert to grayscale
ig = uint8( ( int32(i1(START_ROW:START_ROW+NROWS1-1,START_COL:START_COL+NCOLS1-1,1))+ ...
              int32(i1(START_ROW:START_ROW+NROWS1-1,START_COL:START_COL+NCOLS1-1,2))+ ...
              int32(i1(START_ROW:START_ROW+NROWS1-1,START_COL:START_COL+NCOLS1-1,3)) ) / 3 );

% plot grayscale image:
figure(2);
imshow( ig );

% Export to text file:
fp = fopen(OutputTextFile, 'w');
for k=1:NROWS1
    fprintf( fp, '%d ', ig(k,:) );
    fprintf( fp, '\n');
end
fclose( fp );


% Export to C include file:
fp = fopen( CIncludeFile, 'w');
fprintf(fp, 'int Min[NROWS][NCOLS] = { \n' );
for k=1:NROWS1 % for each line
    fprintf( fp, '{ \n');
    for l=1:NCOLS1
       if l == NCOLS1
           fprintf( fp, '%3d \n', ig(k,l) );
       else
           fprintf( fp, '%3d, ', ig(k,l)  );
       end
       if mod(l, 32) == 0
           fprintf( fp, '\n' );
       end
    end
    fprintf( fp, '}');
    if k ~= NROWS1
        fprintf( fp, ',\n');
    else
        fprintf( fp, '\n');
    end
end
fprintf(fp, '}; \n');
fclose( fp );

        