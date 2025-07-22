set title "Intracavity Gaussian Beam Mode"
set xlabel "Position z (mm)"
set ylabel "Beam Radius w(z) [mm]"
set key outside

# Read the element positions once into a datafile
plot \
    "cavity_mode.txt" using 1:3 with lines lw 2 title "Beam Waist w(z)", \
    for [i=0:3] "elements.txt" index 0 using 1:(0):(1):(1) every ::i::i with vectors nohead lc rgb "gray" lw 1 dt 2 notitle, \
    for [i=0:3] "elements.txt" index 0 using 1:(0):2 every ::i::i with labels offset 1,1 notitle
