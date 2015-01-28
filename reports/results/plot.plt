set terminal png
set output 'plot.png'

set xlabel "corpus_size"
set format x "%s"

set ydata time
set timefmt "%S"
set ylabel "time"

set autoscale

set title "Sequential"
set key reverse Left outside
set grid

set style data linespoints

plot	"ROUGE.dat" using 1:2 title "ROUGE", \
	"METEOR.dat" using 1:2 title "METEOR", \
	"GTM.dat" usign 1:2 title "GTM"

