set title "Concave–Concave Resonator Mode"
set xlabel "z (mm)"
set ylabel "Beam Waist w(z) [mm]"
set grid
set key outside

plot \
    "cavity_mode.txt" using 1:3 with lines lw 2 title "Beam Waist w(z)", \
    for [i=0:1] "elements.txt" using (column(1)):(0):(column(1)):(graph 1) every ::i::i with vectors nohead lc rgb "gray" lw 1 dt (2,2) notitle, \
    for [i=0:1] "elements.txt" using 1:(0):2 every ::i::i with labels offset 1,1 notitle
