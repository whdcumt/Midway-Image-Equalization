set terminal svg size 800,650 dynamic enhanced fname 'arial' fsize 18 butt solid dashed 
set style rectangle fillstyle noborder
set object 1 rect from screen 0,0 to screen 1,1 fillcolor rgb"#ffffff" behind 

set output out

set clip two
set style fill solid 1.00 noborder
set key inside right bottom vertical Left reverse enhanced autotitles nobox
set key noinvert samplen 1 spacing 1 width 0 height 0

set xrange [ 1.00000 : 255 ] noreverse nowriteback
set yrange [ 0.00000 : maximum ] noreverse nowriteback
unset colorbox

# define line styles using explicit rgbcolor names
set style line 1 lt 1 lc rgb "red" lw 1.5
set style line 2 lt 1 lc rgb "green" lw 1.5 
set style line 3 lt 1 lc rgb "blue" lw 1.5
set style line 4 lt 2 lc rgb "red" lw 1.5
set style line 5 lt 2 lc rgb "green" lw 1.5
set style line 6 lt 2 lc rgb "blue" lw 1.5

plot data1 using 1:2 with lines ls 1 title '1st red channel',   \
     data1 using 1:3 with lines ls 2 title '1st green channel', \
     data1 using 1:4 with lines ls 3 title '1st blue channel',  \
     data2 using 1:2 with lines ls 4 title '2nd red channel',   \
     data2 using 1:3 with lines ls 5 title '2nd green channel', \
     data2 using 1:4 with lines ls 6 title '2nd blue channel'
