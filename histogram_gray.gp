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
set style line 1 lt 1 lc rgb "black" lw 1.5
set style line 2 lt 2 lc rgb "black" lw 1.5 

plot data1 using 1:2 with lines ls 1 title '1st gray channel',   \
     data2 using 1:2 with lines ls 2 title '2nd gray channel'   
