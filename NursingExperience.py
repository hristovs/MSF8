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
print(exp)


data = ["" for y in range(len(usernames))]
x_pos = ["" for z in range(len(usernames))]
for x in range(1,len(usernames) + 1):
    cur.execute("select t2.user_id, t3.duration_of_qualification, t1.duration FROM t_events t1 INNER JOIN t_users t2 ON t1.user_id = t2.user_id INNER JOIN texp t3 ON t2.username = t3.username WHERE t2.user_id=%s;",[x])
    l = cur.fetchall()
    sum = 0
    for i in range(len(l)):
        sum = sum + l[i][2]

    avrg = sum/len(l)
    int_avrg = int(avrg)
    qualification = l[0][1]
    data[x-1] = int_avrg
    x_pos[x-1] = qualification

experience0 = []
experience1 = []
experience2 = []
experience3 = []
for x in range(0,len(x_pos)):
    if x_pos[x] == '7_to_11_months': experience0.append(data[x])
    elif x_pos[x] == '1_to_2_years': experience1.append(data[x])
    elif x_pos[x] == '3_to_4_years': experience2.append(data[x])
    else: experience3.append(data[x])

y=[experience0, experience1, experience2, experience3]
x=[1,2,3,4]

# close the communication with the PostgreSQL
conn.commit()
cur.close()
conn.close()

colors = ['r','b','m','k']
labels = ['7 to 11 Months', '1 to 2 Years', '3 to 4 Years', '11 to 15 Years']
for xe, ye in zip(x, y):
    plot.scatter([xe] * len(ye), ye, color=colors[xe-1])
plot.xticks(x, labels)
plot.ylim(top=3000)
plot.title('Nursing Experience Affect on Task Effeciency', fontweight='bold')
plot.xlabel('How Long Nurse has Been Qualified',fontweight='bold')
plot.ylabel('Average Task Duration',fontweight='bold')
plot.show()
