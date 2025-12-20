#Álvaro Martínez García, 48150407E
set terminal png
set output "pow2.png"

set xlabel "exp value"
set ylabel "Steps"

set title  "pow2"

set yrange [0:100]
set xrange [1:25]

plot "pow2.CPUtimes" using 1:2 with lines title "pow2_1" ,\
"pow2.CPUtimes" using 1:3 with lines title "pow2_2" ,\
"pow2.CPUtimes" using 1:4 with lines title "pow2_3" ,\
