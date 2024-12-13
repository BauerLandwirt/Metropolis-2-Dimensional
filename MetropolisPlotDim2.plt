 set style fill transparent solid 0.04 noborder
 set style circle radius 0.01
 set xlabel "x" font "Times-Roman,12"
 set ylabel "y" font "Times-Roman,12"
set terminal pdf
set output "MetropolisDim2PlotExample.pdf"
 plot "MetropolisSampleDim2.txt" u 1:2 with circles lc rgb "blue" notitle