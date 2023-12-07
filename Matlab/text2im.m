% read B&W image
% Output image:
OutputImageFile = '../data/FEUPout.bmp';

% Export to text file, ASCII, one image line per text line
InputTextFile = '../data/datain.txt';
OutputTextFile = '../data/dataout.txt';
i1 = uint8( load( InputTextFile ) );
i2 = uint8( load( OutputTextFile ) );

% Plot original
figure(1);
imshow( i1 );

% Plot final
figure(2);
imshow( i2 );

% Write to bitmap file:
imwrite(i2, OutputImageFile );
        