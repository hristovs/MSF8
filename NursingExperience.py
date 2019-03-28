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
#print(usernames)

cur.execute("select distinct(duration_of_qualification) FROM texp;")
list1 = cur.fetchall()
exp = ["" for x in range(len(list1))]
for i in range(0,len(list1)):
    experience = list1[i]
    experience = experience[0]
    exp[i] = experience
#print(exp)


data = ["" for y in range(len(list))]
x_pos = ["" for z in range(len(list))]
for x in range(1,len(list) + 1):
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


#for item in x_pos:
#    if item == "7_to_11_months": x_pos[x_pos.index(item)] = 1
#    elif item == "1_to_2_years": x_pos[x_pos.index(item)] = 2
#    elif item == "3_to_4_years": x_pos[x_pos.index(item)] = 3
#    else: x_pos[x_pos.index(item)] = 4


print(data)
print(x_pos)

# close the communication with the PostgreSQL
conn.commit()
cur.close()
conn.close()

x = x_pos
y_pos = np.arange(len(x))
plot.plot(y_pos, data, 'ro')
plot.xticks(y_pos, x)
plot.title('Nursing Experience Effect on Task Effeciency')
plot.xlabel('How Long Nurse has Been Qualified')
plot.ylabel('Average Task Duration')
plot.show()
