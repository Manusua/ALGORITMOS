make all
make ejercicio5_test

gnuplot << END_GNUPLOT
set title "Tiempo-tamaño"
set ylabel "Tamaño"
set xlabel "Milisegundos"
set key right bottom
set grid
set term png
set output "ejercicio5_TIME.png"
plot "ejercicio5.log" using 1:2 with lines lw 2 title "Tiempo Medio"
replot

set title "Min OB - tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio5_MIN.png"
plot "ejercicio5.log" using 1:3 with lines lw 2 title "Min OB"
	
replot

set title "Medio OB-tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio5_MEDIO.png"
plot "ejercicio5.log" using 1:4 with lines lw 2 title "Medio OB"
replot

set title "Max OB-tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio5_MAX.png"
plot "ejercicio5.log" using 1:5 with lines lw 2 title "Max OB"
replot


quit
END_GNUPLOT










make clean
