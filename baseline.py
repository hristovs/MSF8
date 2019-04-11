import psycopg2
import numpy as np
from matplotlib import pyplot as plot

# set up connection to server
#conn = psycopg2.connect("dbname=nurses user=SusieMoynihan")
conn = psycopg2.connect("host=nurses.c1sjehtxbob6.eu-west-1.rds.amazonaws.com port=5432 dbname=nurses user=nursesadmin password=password")

print('Connected to the database')
# create a cursor
cur = conn.cursor()

# execute a statement
cur.execute("select distinct(username) FROM texp WHERE username != '';")
list = cur.fetchall()
usernames = ["" for x in range(len(list))]
for i in range(0,len(list)):
    user = list[i]
    user = user[0]
    usernames[i] = user

cur.execute("select distinct(duration_of_qualification) FROM texp;")
list1 = cur.fetchall()
exp = ["" for x in range(len(list1))]
for i in range(0,len(list1)):
    experience = list1[i] 
    experience = experience[0]
    exp[i] = experience


data = ["" for y in range(len(list))]
x_pos = ["" for z in range(len(list))]
for x in range(1,len(list) + 1):
    cur.execute("select t2.user_id, t3.duration_of_qualification, t1.duration, t1.type FROM t_events t1 INNER JOIN t_users t2 ON t1.user_id = t2.user_id INNER JOIN texp t3 ON t2.username = t3.username WHERE t2.user_id=%s;",[x])
    l = cur.fetchall()
    sum = 0
    count = 0
    for i in range(len(l)):
        if l[i][3] == 'admission'\
            or l[i][3] == 'vital_sign_round'\
            or l[i][3] == 'iv_fluids'\
            or l[i][3] == 'meeting_patients_basic_needs'\
            or l[i][3] == 'handover'\
            or l[i][3] == 'communication'\
            or l[i][3] == 'drugs_individual_pt'\
            or l[i][3] == 'invasive_procedures'\
            or l[i][3] == 'drug_round'\
            or l[i][3] == 'diagnostic_test'\
            or l[i][3] == 'blood_transfusion'\
            or l[i][3] == 'vital_sign_individual'\
            or l[i][3] == 'discharge':
            sum = sum + l[i][2]
            count +=1
    if sum != 0 : avrg = sum/count
    int_avrg = int(avrg) /60
    qualification = l[0][1]
    data[x-1] = int_avrg
    x_pos[x-1] = qualification
    

experience0 = []
experience1 = []
experience2 = []
for x in range(0,len(x_pos)):
    if x_pos[x] == '7_to_11_months': experience0.append(data[x])
    elif x_pos[x] == '1_to_2_years': experience1.append(data[x])
    elif x_pos[x] == '3_to_4_years': experience2.append(data[x])

y=[experience0, experience1, experience2]
x=[1,2,3]

# close the communication with the PostgreSQL
conn.commit()
cur.close()
conn.close()

colors = ['r','b','m']
labels = ['7 to 11 Months', '1 to 2 Years', '3 to 4 Years']
for xe, ye in zip(x, y):
    plot.scatter([xe] * len(ye), ye, color=colors[xe-1])
plot.xticks(x, labels)
plot.ylim(bottom=0.0)
plot.title('Nursing Experience Affect on Task Effeciency', fontweight='bold')
plot.xlabel('How Long Nurse has Been Qualified',fontweight='bold')
plot.ylabel('Average Task Duration',fontweight='bold')
plot.show()
