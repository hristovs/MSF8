import psycopg2
import numpy as np
from matplotlib import pyplot as plt
import time
from time import mktime
from datetime import datetime
import numpy as np


week0 = "date(started_time) between '2018-10-05' and '2018-10-11' "
week1 = "date(started_time) between '2018-10-12' and '2018-10-18' "
week2 = "date(started_time) between '2018-10-19' and '2018-10-25' "
week3 = "date(started_time) between '2018-10-26' and '2018-11-02' "

under_5 = "ward_you_are_working_on_today='IPD1_under_5' "
over_5 = "ward_you_are_working_on_today='IDP4_over_5' "
admission = "event_type='admission'"
discharge = "event_type='discharge'"
drug_round = "event_type='drug_round'"
vital_sign_round = "event_type='vital_sign_round'"
patient_documentation = "event_type='patient_documentation'"
meeting_patients_basic_needs = "event_type='meeting_patients_basic_needs'"
handover = "event_type='handover'"
surveillance = "event_type='surveillance'"
taking_a_break = "event_type ='taking_a_break'"
indirect_patient_care = "event_type='indirect_patient_care'"
pharmacy_tasks = "event_type='pharmacy_tasks'"

day_shift = "(date_part('hour', started_time) < 19 and date_part('hour', started_time) >= 8)"
night_shift = "(date_part('hour', started_time) >= 19 or date_part('hour', started_time) < 8)"

def get_date(week, day):
    if week == 3:
        if day<=5:
            date = 12 + day
            return "started_time between '2018-10-" + str(date) +  " 00:00:00' and '2018-10-" + str(date) + " 23:59:59' "
        elif day>5:
            date = day - 5
            return "started_time between '2018-11-0" + str(date) +  " 00:00:00' and '2018-11-0" + str(date) + " 23:59:59' "

    elif week == 0:
        date = 5 + day
        if date<10:
            return "started_time between '2018-10-0" + str(date) +  " 00:00:00' and '2018-10-0" + str(date) + " 23:59:59' "
        else:
            return "started_time between '2018-10-" + str(date) +  " 00:00:00' and '2018-10-" + str(date) + " 23:59:59' "
    elif week == 1:
        date = 12 + day
        if date<10:
            return "started_time between '2018-10-0" + str(date) +  " 00:00:00' and '2018-10-0" + str(date) + " 23:59:59' "
        else:
            return "started_time between '2018-10-" + str(date) +  " 00:00:00' and '2018-10-" + str(date) + " 23:59:59' "
    elif week == 2:
        date = 19 + day
        if date<10:
            return "started_time between '2018-10-0" + str(date) +  " 00:00:00' and '2018-10-0" + str(date) + " 23:59:59' "
        else:
            return "started_time between '2018-10-" + str(date) +  " 00:00:00' and '2018-10-" + str(date) + " 23:59:59' "

    else:
        print("error")

# set up connection to server
conn = psycopg2.connect("host=nurses.c1sjehtxbob6.eu-west-1.rds.amazonaws.com port=5432 dbname=nurses user=nursesadmin password=password")
print('Connected to the database')

# create a cursor
cur = conn.cursor()


def baselineFunc(day_and_date, shift, ward):
    cur.execute("SELECT sum(duration) FROM tevent WHERE " + day_and_date + " AND " + shift + " AND " + ward)
    sum = cur.fetchone()
    sum = sum[0]
    cur.execute("SELECT duration, event_type FROM tevent WHERE " + day_and_date + " AND " + shift + " AND " + ward)
    l = cur.fetchall()
    baseline_sum = 0
    for i in range(0, len(l)):
        if l[i][1] == 'admission'\
            or l[i][1] == 'discharge'\
            or l[i][1] == 'drug_round'\
            or l[i][1] == 'vital_sign_round'\
            or l[i][1] == 'patient_documentation'\
            or l[i][1] == 'meeting_patients_basic_needs'\
            or l[i][1] == 'handover'\
            or l[i][1] == 'surveillance'\
            or l[i][1] == 'taking_a_break'\
            or l[i][1] == 'indirect_patient_care'\
            or l[i][1] == 'pharmacy_tasks':
                baseline_sum += l[i][0]
    baseline = (baseline_sum/sum) * 100
    return baseline

weeks = 4
days = 7
baselinePart = []
reactivePart = []
for i in range(0,weeks):
    for j in range(0,days):
        baselinePart.append(baselineFunc(get_date(i,j), day_shift, over_5))
        baselinePart.append(baselineFunc(get_date(i,j), night_shift, over_5))
        reactivePart.append(100-(baselineFunc(get_date(i,j), day_shift, over_5)))
        reactivePart.append(100-(baselineFunc(get_date(i,j), night_shift, over_5)))


# close the communication with the PostgreSQL
conn.commit()
cur.close()
conn.close()


ind = np.arange(len(baselinePart))
width = 0.4
p1 = plt.bar(ind, baselinePart, color='#75bbfd')
p2 = plt.bar(ind, reactivePart, bottom=baselinePart, color='red')
plt.ylabel('Percentage of Time', fontweight='bold')
plt.xlabel('Shift', fontweight='bold')
plt.title('Time Spent on Baseline vs Reactive Care (Over 5 Ward)')
plt.xticks(ind, ('Day', 'Night', 'Day', 'Night', 'Day','Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night','Day', 'Night'), rotation='vertical')
plt.yticks(np.arange(0, 101, 10))
plt.legend((p1[0], p2[0]), ('Baseline', 'Reactive'))

plt.show()








