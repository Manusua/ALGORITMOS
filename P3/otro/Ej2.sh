
gnuplot << END_GNUPLOT
f(x) = log(x)
g(x) = x

set title "OBS bbin"
set ylabel "OBS"
set xlabel "Tamaño"
set key right bottom
set grid
set term png
set output "ejercicio2_OBS_bbin.png"
plot "busqueda.dat" using 1:4 with lines lw 2 title "Min OB",\
"busqueda.dat" using 1:5 with lines lw 2 title "Medio OB",\
"busqueda.dat" using 1:6 with lines lw 2 title "Max OB",\
f(x) with lines lw 2 title "f(x)=log(x)"
replot

set title "OBS blin"
set ylabel "OBS"
set xlabel "Tamaño"
set key right bottom
set grid
set term png
set output "ejercicio2_OBS_blin.png"
plot "busquedalin.dat" using 1:4 with lines lw 2 title "Min OB",\
"busquedalin.dat" using 1:5 with lines lw 2 title "Medio OB",\
"busquedalin.dat" using 1:6 with lines lw 2 title "Max OB",\
g(x) with lines lw 2 title "f(x)=x"
replot

set title "Medios OBS"
set ylabel "OBS"
set xlabel "Tamaño"
set key right bottom
set grid
set term png
set output "ejercicio2_MedioOBS.png"
plot "busquedalin.dat" using 1:5 with lines lw 2 title "blin",\
"busqueda.dat" using 1:5 with lines lw 2 title "bbin"
replot

set title "Tiempo-Tamaño"
set ylabel "Tiempo"
set xlabel "Tamaño"
set key right bottom
set grid
set term png
set output "ejercicio2_TIME.png"
plot "busquedalin.dat" using 1:3 with lines lw 2 title "blin",\
"busqueda.dat" using 1:3 with lines lw 2 title "bbin"
replot


quit
END_GNUPLOT
