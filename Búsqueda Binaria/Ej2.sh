make all
make ejercicio2_test

gnuplot << END_GNUPLOT
set title "Tiempo-tamaño"
set ylabel "Tamaño"
set xlabel "Milisegundos"
set key right bottom
set grid
set term png
set output "ejercicio2_TIME.png"
plot "busqueda.dat" using 1:3 with lines lw 2 title "Tiempo Medio"
replot

set title "Min OB - tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio2_MIN.png"
plot "busqueda.dat" using 1:4 with lines lw 2 title "Min OB"
	
replot

set title "Medio OB-tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio2_MEDIO.png"
plot "busqueda.dat" using 1:5 with lines lw 2 title "Medio OB"
replot

set title "Max OB-tamaño"
set ylabel "Tamaño"
set xlabel "OB"
set key right bottom
set grid
set term png
set output "ejercicio2_MAX.png"
plot "busqueda.dat" using 1:6 with lines lw 2 title "Max OB"
replot


quit
END_GNUPLOT

make clean
