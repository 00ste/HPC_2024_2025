# Define variables
datafile = 'results.csv'

# Output filenames
output_exec_500 = 'exec_openmp_500.png'
output_exec_750 = 'exec_openmp_750.png'
output_speedup_500 = 'speedup_openmp_500.png'
output_speedup_750 = 'speedup_openmp_750.png'
output_efficiency_500 = 'efficiency_openmp_500.png'
output_efficiency_750 = 'efficiency_openmp_750.png'

### Execution Time Plots (No change in y-axis)
set terminal pngcairo size 1200,700 enhanced background rgb 'white'
set datafile separator ","

# Execution Time (500 Iterations)
set output output_exec_500
set title "Execution Time (500 Iterations)" font ",16"
set xlabel 'Total Size (bytes)' font ",16"
set ylabel 'Execution Time (s)' font ",16"
set grid linewidth 2
set key outside right
set yrange [0:250]


plot datafile using 1:($4/1000) title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($6/1000) title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($8/1000) title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($10/1000) title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($12/1000) title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($14/1000) title '1024 Threads' with linespoints linewidth 3 pointsize 2

# Execution Time (750 Iterations)
set output output_exec_750
set title "Execution Time (750 Iterations)" font ",16"

plot datafile using 1:($5/1000) title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($7/1000) title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($9/1000) title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($11/1000) title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($13/1000) title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($15/1000) title '1024 Threads' with linespoints linewidth 3 pointsize 2

### Speedup Plots (y-axis locked to 15)
set yrange [0:30]

# Speedup (500 Iterations)
set output output_speedup_500
set title "Speedup (500 Iterations)" font ",16"
set ylabel 'Speedup' font ",16"

plot datafile using 1:($2/$4) title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($2/$6) title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($2/$8) title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($2/$10) title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($2/$12) title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($2/$14) title '1024 Threads' with linespoints linewidth 3 pointsize 2

# Speedup (750 Iterations)
set output output_speedup_750
set title "Speedup (750 Iterations)" font ",16"

plot datafile  using 1:($3/$5) title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($3/$7) title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($3/$9) title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($3/$11) title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($3/$13) title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:($3/$15) title '1024 Threads' with linespoints linewidth 3 pointsize 2

### Efficiency Plots (y-axis locked to 110)
set yrange [0:300]

# Efficiency (500 Iterations)
set output output_efficiency_500
set title "Efficiency (500 Iterations)" font ",16"
set ylabel 'Efficiency' font ",16"

plot datafile using 1:(($2/$4)/1)*100 title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($2/$6)/2)*100 title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($2/$8)/5)*100 title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($2/$10)/10)*100 title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($2/$12)/20)*100 title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($2/$14)/40)*100 title '1024 Threads' with linespoints linewidth 3 pointsize 2

# Efficiency (750 Iterations)
set output output_efficiency_750
set title "Efficiency (750 Iterations)" font ",16"

plot datafile using 1:(($3/$5)/1)*100 title '1 Thread' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($3/$7)/2)*100 title '4 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($3/$9)/5)*100 title '16 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($3/$11)/10)*100 title '64 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($3/$13)/20)*100 title '256 Threads' with linespoints linewidth 3 pointsize 2, \
     '' using 1:(($3/$15)/40)*100 title '1024 Threads' with linespoints linewidth 3 pointsize 2
