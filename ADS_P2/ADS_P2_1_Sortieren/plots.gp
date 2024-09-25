# reset
# set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
# set output 'runtime_comparison_algorithms.png'

# set autoscale x
# set autoscale y
# set xlabel "n [-]"
# set ylabel "t [s]"
# set key top left

# plot \
# "quicksort.txt" with linespoints title 'Quicksort',\
# "mergesort.txt" with linespoints title 'Mergesort',\
# "shellsort_2n.txt" with linespoints title 'Shellsort',\
# "heapsort.txt" with linespoints title 'Heapsort'



set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output 'runtime_comparison.png'

set title "Runtime Comparison of Quicksort and Insertionsort"
set xlabel "Number of elements (n)"
set ylabel "Time (seconds)"
set grid

set xrange[0:500]
set autoscale y
# Format for scientific notation
set format y '%.1e'

plot "insertionsort2.txt" with linespoints title 'Insertion Sort', \
     "quicksort2.txt" with linespoints title 'Quick Sort'
