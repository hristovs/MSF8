import matplotlib.pyplot as plt
import numpy as np

with open('/Users/SusieMoynihan/GroupProject/MSF8/test.text') as f:
    lines = f.readlines()
    taskAvg = [line.split()[0] for line in lines]

x = ["" for y in range(len(taskAvg))]
for i in range(0,len(x)):
    x[i] = i+1
    taskAvg[i] = int(taskAvg[i])/60
taskAvg.sort()

y_pos = np.arange(len(x))
plt.bar(y_pos, taskAvg, align='center', width=0.9)
plt.xticks(y_pos, x)
plt.xlabel('Nurses',fontweight='bold')
plt.ylabel('Average Task Duration (minutes)',fontweight='bold')
plt.title('Average Task Duration for Each Nurse')

plt.show()
