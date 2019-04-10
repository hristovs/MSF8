import matplotlib.pyplot as plt
import numpy as np

with open('/Users/SusieMoynihan/GroupProject/MSF8/test.text') as f:
    lines = f.readlines()
    pScore = [line.split()[1] for line in lines]
    avgPatient = [line.split()[2] for line in lines]

x = ["" for y in range(len(pScore))]
for i in range(0,len(pScore)):
    x[i] = i+1
    pScore[i] = float(pScore[i])
    avgPatient[i] = float(avgPatient[i])

plt.plot( x, pScore, marker='.', markerfacecolor='#0504aa', markersize=12, color='#0165fc', linewidth=2, label= 'P Score')
plt.plot( x, avgPatient, marker='D',markerfacecolor='#f97306', markersize=6, color='#fdaa48', linewidth=2, label='Average Patient')
plt.legend()
y_pos = np.arange(len(x))
plt.xticks(y_pos, x)
plt.xlabel('Nurses',fontweight='bold')
plt.show()
