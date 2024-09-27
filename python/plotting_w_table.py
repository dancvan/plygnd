import matplotlib.pylab as pylab

Data = np.genfromtxt(‘generic.csv’)

set1 = Data[:,0]
set2 = Data[:,1]
set3 = Data[:,2]

mask2 = ~np.isnan(set2)
mask3 = ~np.isnan(set3)

#Adding a table
#pairing values
col_label1 = [‘current [A]’ , ‘power [W]’]
col_label2 = [‘current [A]’, ‘pulse width [ns]’]
current_power = np.concatenate(([set1[mask2]],[set2[mask2]]), axis=0).T
current_pulse= np.concatenate(([set1[mask3]], [set3[mask3]]), axis=0).T


fig, (ax1, ax2) = plt.subplots(2, sharex=True)


power_table = ax1.table(cellText=current_power, colWidths=[0.1]*3, colLabels=col_label1, loc='right’)

pulse_table = ax2.table(cellText=current_pulse, colWidths=[0.1]*3, colLabels=col_label2, loc=‘right’)

ax1.plot(set1[mask2], set2[mask2])
ax2.plot(set1[mask3], set3[mask3]) 

ax2.set_xlabel(‘Current [A]’, fontname=‘Times New Roman’, fontsize=14)

ax1.set_ylabel(‘Power [W]’, fontname=‘Times New Roman’,fontsize=14)

ax2.set_ylabel('Pulse width [ns]’, fontname=‘Times New Roman’,fontsize=14)


