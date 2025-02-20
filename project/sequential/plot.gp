# Define variables
datafile = 'results.csv'
output_exec = 'execution_time.png'

### Plot: Execution Time vs. Total Size

# Set terminal and output for the plot
set terminal pngcairo size 800,600 enhanced background rgb 'white'
set output output_exec

# Axes labels
set xlabel 'Total Size (bytes)'
set ylabel 'Execution Time (s)'

# Set grid and key placement
set grid
set key outside right

# Adjust x-axis tic frequency based on Total Size
set xtics auto

# Format y-axis for better readability
set format y "%.0f"

# Ensure correct column indexing in case of formatting issues
set datafile separator ","

# Plot Execution Time for 500 and 750 iterations as two separate series
plot datafile using 1:($2/1000) title '500 Iterations' with linespoints, \
     '' using 1:($3/1000) title '750 Iterations' with linespoints
