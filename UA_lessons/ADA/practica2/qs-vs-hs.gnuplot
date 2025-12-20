#Álvaro Martínez García, 48150407E
set terminal png
set output "quickSort.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set title  "Quicksort"

plot "qs-vs-hs.Msteps" using 1:2 with lines title "random arrays" ,\
"qs-vs-hs.Msteps" using 1:4 with lines title "sorted arrays" ,\
"qs-vs-hs.Msteps" using 1:6 with lines title "reverse-sorted arrays" ,\

#------------------------------------------------------------------------

set terminal png
set output "heapSort.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set title  "Heapsort"

plot "qs-vs-hs.Msteps" using 1:3 with lines title "random arrays" ,\
"qs-vs-hs.Msteps" using 1:5 with lines title "sorted arrays" ,\
"qs-vs-hs.Msteps" using 1:7 with lines title "reverse-sorted arrays" ,\


#------------------------------------------------------------------------

set terminal png
set output "qs-vs-hs-RA.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set title  "Quicksort versus Heapsort (random arrays)"

y(x)= a*x*log(x) + b*x
fit y(x) "qs-vs-hs.Msteps" using 1:2 via a,b
z(x)= c*x*log(x) + x*d
fit z(x) "qs-vs-hs.Msteps" using 1:3 via c,d

plot "qs-vs-hs.Msteps" using 1:2 with lines title "Quicksort" ,\
"qs-vs-hs.Msteps" using 1:3 with lines title "Heapsort" ,\
y(x) title "fitting Quicksort time value to..." ,\
z(x) title "fitting Heapsort time value to..."


#------------------------------------------------------------------------

set terminal png
set output "qs-vs-vs-SA.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set title  "Quicksort versus Heapsort (sorted arrays)"

y(x)= e*x*log(x) + f*x
fit y(x) "qs-vs-hs.Msteps" using 1:4 via e,f
z(x)= g*x*log(x) + x*h
fit z(x) "qs-vs-hs.Msteps" using 1:5 via g,h

plot "qs-vs-hs.Msteps" using 1:4 with lines title "Quicksort" ,\
"qs-vs-hs.Msteps" using 1:5 with lines title "Heapsort" ,\
y(x) title "fitting Quicksort time value to..." ,\
z(x) title "fitting Heapsort time value to..."


#------------------------------------------------------------------------

set terminal png
set output "qs-vs-hs-RSA.png"

set xlabel "size of arrays"
set ylabel "Millions of program steps"

set title  "Quicksort versus Heapsort (reverse-sorted arrays)"

y(x)= i*x*log(x) + j*x
fit y(x) "qs-vs-hs.Msteps" using 1:6 via i,j
z(x)= k*x*log(x) + x*l
fit z(x) "qs-vs-hs.Msteps" using 1:7 via k,l

plot "qs-vs-hs.Msteps" using 1:6 with lines title "Quicksort" ,\
"qs-vs-hs.Msteps" using 1:7 with lines title "Heapsort" ,\
y(x) title "fitting Quicksort time value to..." ,\
z(x) title "fitting Heapsort time value to..."


