# Define variables
datafile = 'res_ref.csv'
output_exec = 'execution_time.png'
output_speed = 'speedup.png'
title_exec = 'Execution Time as a Function of Data Size'
title_speed = 'Speedup as a Function of Data Size'

### Plot 1: Execution Time for All Thread Counts

# Set terminal and output for the first plot
set terminal pngcairo size 800,600 enhanced background rgb 'white'
set output output_exec

# Main title and subtitle for the first plot
set title title_exec

# Axes labels
set xlabel 'Data Size'
set ylabel 'Seconds'

# Set x-axis to logarithmic scale
set logscale x

# Set grid and key placement
set grid
set key outside right

# Plot execution time for all thread counts
plot datafile using 1:2 title 'Sequential' with linespoints, \
     '' using 1:3 title '1 thread' with linespoints, \
     '' using 1:4 title '2 threads' with linespoints, \
     '' using 1:5 title '5 threads' with linespoints, \
     '' using 1:6 title '10 threads' with linespoints, \
     '' using 1:7 title '20 threads' with linespoints, \
     '' using 1:8 title '40 threads' with linespoints, \
     '' using 1:9 title '60 threads' with linespoints, \
     '' using 1:10 title '100 threads' with linespoints

### Plot 2: Speedup for Different Thread Counts

# Set terminal and output for the second plot
set output output_speed

# Title for the second plot
set title title_speed

# Axes labels for the speedup plot
set xlabel 'Data Size'
set ylabel 'Speedup'

# Plot speedup for different thread counts
plot datafile using 1:($2/$3) title '1 thread' with linespoints, \
     '' using 1:($2/$4) title '2 threads' with linespoints, \
     '' using 1:($2/$5) title '5 threads' with linespoints, \
     '' using 1:($2/$6) title '10 threads' with linespoints, \
     '' using 1:($2/$7) title '20 threads' with linespoints, \
     '' using 1:($2/$8) title '40 threads' with linespoints, \
     '' using 1:($2/$9) title '60 threads' with linespoints, \
     '' using 1:($2/$10) title '100 threads' with linespoints
