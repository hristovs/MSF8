import psycopg2
import numpy as np
from matplotlib import pyplot as plot

# set up connection to server
conn = psycopg2.connect("host=nurses.cmufhw6anp86.eu-west-1.rds.amazonaws.com port=5432 dbname=nurses user=nursesadmin password=password")
print('Connected to the database')

# create a cursor
cur = conn.cursor()

# execute a statement
cur.execute("SELECT SUM(patient_severity_score_3) FROM tacuity WHERE patient_severity_score_3 != 'nan'")
severity3 = cur.fetchall()
severity3 = severity3[0]

cur.execute("SELECT SUM(patient_severity_score_2) FROM tacuity WHERE patient_severity_score_3 != 'nan'")
severity2 = cur.fetchall()
severity2 = severity2[0]

cur.execute("SELECT SUM(patient_severity_score_1) FROM tacuity WHERE patient_severity_score_3 != 'nan'")
severity1 = cur.fetchall()
severity1 = severity1[0]

cur.execute("SELECT SUM(patient_severity_score_0) FROM tacuity WHERE patient_severity_score_3 != 'nan'")
severity0 = cur.fetchall()
severity0 = severity0[0]

data = [severity3[0], severity2[0], severity1[0], severity0[0]]

for i in range(0,4):
 print(data[i])
# close the communication with the PostgreSQL
conn.commit()
cur.close()
conn.close()

x = ('Severity 3', 'Severity 2', 'Severity 1', 'Severity 0')
y_pos = np.arange(len(x))
a,b,c,d = plot.bar(y_pos, data, align='center', alpha=1)
a.set_facecolor('r')
b.set_facecolor('g')
c.set_facecolor('b')
d.set_facecolor('r')
plot.xticks(y_pos, x)
plot.title('Number of Patients with each Severity Level')
plot.xlabel('Patient Severity')
plot.ylabel('Number of Patients')
plot.show()
