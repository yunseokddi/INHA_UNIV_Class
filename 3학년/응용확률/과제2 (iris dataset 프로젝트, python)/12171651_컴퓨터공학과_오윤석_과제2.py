import seaborn as sns
import numpy as np
from matplotlib import pyplot as plt
import math

def least_square_fit(avg_x,avg_y, x, y):
    x1 = 0
    y1 = 0
    count = 0
    result = 0
    pow_x = 0
    alpha = 0
    beta = 0
    for _ in range(0,50):
        x1 = abs(avg_x - x[count])
        y1 = abs(avg_y-y[count])
        pow_x = pow_x + math.pow(x1,2)
        result = result + (x1 * y1)
        count = count + 1
    alpha = result / pow_x
    beta = avg_y - (avg_x*alpha)

    return alpha, beta






def Make_K_Function(u): #Gussian Kernel Function
    return ((1/(math.sqrt(2)*math.pi))*math.exp((-1/2)*math.pow(u,2)))

def Make_h(a, n):
    return (1.06)*a*math.pow(n,-1/5)

def Make_KED_Function(k, a): # k: 데이터 집합, a: 표준편차

    result = np.zeros(100)
    k_sum = 0
    h = Make_h(a, 50)
    x = 0.0
    count1 = 0
    count2 = 0

    for _ in range(0,100):
        for _ in range(0,50):
            k_sum = k_sum+Make_K_Function((x-k[count1])/h)
            count1 = count1 + 1
        result[count2] = (1/(50*h))*(k_sum)
        k_sum = 0
        count1 =0
        count2 = count2 + 1
        x = x + 0.1

    return result

f = open("C:/Users/YunSeok/Desktop/INHA/학교/3학년/2학기/응용확률/과제2/iris.data",'r') #본인의 data로 경로 변경해주세요.

#첫번째 배열은 종류 (1.sepal length in cm 2. sepal width in cm 3. petal length in cm 4. petal width in cm)
#두번쨰는 각 data 개수
Iris_setosa_list =[]
Iris_versicolor_list = []
Iris_virginica_list = []
a = []



for _ in range(50):

        line = f.readline()

        if not line:
             break

        a = line.split(',')
        del a[4]
        Iris_setosa_list += [a]


for _ in range(50):

        line = f.readline()

        if not line:
             break

        a = line.split(',')
        del a[4]
        Iris_versicolor_list += [a]

for _ in range(50):

        line = f.readline()

        if not line:
             break

        a = line.split(',')
        del a[4]
        Iris_virginica_list += [a]

f.close()

#Iris Setosa 데이터 분리 변수
setosa_sepal_length = []
setosa_sepal_width = []
setosa_pepal_length = []
setosa_pepal_width = []

#Iris Versicolour 데이터 분리 변수
Versicolour_sepal_length = []
Versicolour_sepal_width = []
Versicolour_pepal_length = []
Versicolour_pepal_width = []

#Iris Virginica 데이터 분리 변수
Virginica_sepal_length = []
Virginica_sepal_width = []
Virginica_pepal_length = []
Virginica_pepal_width = []

#데이터에 대한 각 avg
setosa_sepal_length_avg = 0
setosa_sepal_width_avg = 0
setosa_pepal_length_avg = 0
setosa_pepal_width_avg = 0
Versicolour_sepal_length_avg = 0
Versicolour_sepal_width_avg = 0
Versicolour_pepal_length_avg =0
Versicolour_pepal_width_avg = 0
Virginica_sepal_length_avg = 0
Virginica_sepal_width_avg = 0
Virginica_pepal_length_avg = 0
Virginica_pepal_width_avg = 0

#데이터에 대한 각 var
setosa_sepal_length_var = 0
setosa_sepal_width_var = 0
setosa_pepal_length_var = 0
setosa_pepal_width_var = 0
Versicolour_sepal_length_var = 0
Versicolour_sepal_width_var = 0
Versicolour_pepal_length_var =0
Versicolour_pepal_width_var = 0
Virginica_sepal_length_var = 0
Virginica_sepal_width_var= 0
Virginica_pepal_length_var = 0
Virginica_pepal_width_var = 0


i = 0
for _ in range(50):
    setosa_sepal_length.append(Iris_setosa_list[i][0])
    i =  i+1

i = 0
for _ in range(50):
    setosa_sepal_width.append(Iris_setosa_list[i][1])
    i =  i+1

i = 0
for _ in range(50):
    setosa_pepal_length.append(Iris_setosa_list[i][2])
    i =  i+1

i = 0
for _ in range(50):
    setosa_pepal_width.append(Iris_setosa_list[i][3])
    i =  i+1

#Iris Versicolour 데이터 분리
i = 0
for _ in range(50):
    Versicolour_sepal_length.append(Iris_versicolor_list[i][0])
    i =  i+1

i = 0
for _ in range(50):
    Versicolour_sepal_width.append(Iris_versicolor_list[i][1])
    i =  i+1

i = 0
for _ in range(50):
    Versicolour_pepal_length.append(Iris_versicolor_list[i][2])
    i =  i+1

i = 0
for _ in range(50):
    Versicolour_pepal_width.append(Iris_versicolor_list[i][3])
    i =  i+1

#Iris Virginica 데이터 분리
i = 0
for _ in range(50):
    Virginica_sepal_length.append(Iris_virginica_list[i][0])
    i =  i+1

i = 0
for _ in range(50):
    Virginica_sepal_width.append(Iris_virginica_list[i][1])
    i =  i+1

i = 0
for _ in range(50):
    Virginica_pepal_length.append(Iris_virginica_list[i][2])
    i =  i+1

i = 0
for _ in range(50):
    Virginica_pepal_width.append(Iris_virginica_list[i][3])
    i =  i+1


#---------------------------------------------------변수 대입----------------------------------------------------------
#Each data transformate for float
setosa_sepal_length = np.array(setosa_sepal_length, dtype='float')
Versicolour_sepal_length = np.array(Versicolour_sepal_length, dtype='float')
Virginica_sepal_length = np.array(Virginica_sepal_length, dtype='float')
setosa_sepal_width = np.array(setosa_sepal_width, dtype='float')
Versicolour_sepal_width = np.array(Versicolour_sepal_width, dtype='float')
Virginica_sepal_width = np.array(Virginica_sepal_width, dtype='float')
setosa_pepal_length = np.array(setosa_pepal_length, dtype='float')
Versicolour_pepal_length = np.array(Versicolour_pepal_length, dtype='float')
Virginica_pepal_length = np.array(Virginica_pepal_length, dtype='float')
setosa_pepal_width = np.array(setosa_pepal_width, dtype='float')
Versicolour_pepal_width = np.array(Versicolour_pepal_width, dtype='float')
Virginica_pepal_width = np.array(Virginica_pepal_width, dtype='float')


#Avarage 구하기
setosa_sepal_length_avg = setosa_sepal_length.sum()/50
Versicolour_sepal_length_avg = Versicolour_sepal_length.sum()/50
Virginica_sepal_length_avg = Virginica_sepal_length.sum()/50
setosa_sepal_width_avg = setosa_sepal_width.sum()/50
Versicolour_sepal_width_avg = Versicolour_sepal_width.sum()/50
Virginica_sepal_width_avg = Virginica_sepal_width.sum()/50
setosa_pepal_length_avg = setosa_pepal_length.sum()/50
Versicolour_pepal_length_avg = Versicolour_pepal_length.sum()/50
Virginica_pepal_length_avg = Virginica_pepal_length.sum()/50
setosa_pepal_width_avg = setosa_pepal_width.sum()/50
Versicolour_pepal_width_avg = Versicolour_pepal_width.sum()/50
Virginica_pepal_width_avg = Virginica_pepal_width.sum()/50


#Variance 구하기
setosa_sepal_length_var = ((setosa_sepal_length_avg*setosa_sepal_length_avg) - (np.square(setosa_sepal_length_avg).sum()/50))/ 50
Versicolour_sepal_length_var = ((Versicolour_sepal_length_avg*Versicolour_sepal_length_avg) - (np.square(Versicolour_sepal_length_avg).sum()/50))/ 50
Virginica_sepal_length_var = ((Virginica_sepal_length_avg*Virginica_sepal_length_avg) - (np.square(Virginica_sepal_length_avg).sum()/50))/ 50
setosa_sepal_width_var = ((setosa_sepal_width_avg*setosa_sepal_width_avg) - (np.square(setosa_sepal_width_avg).sum()/50))/ 50
Versicolour_sepal_width_var = ((Versicolour_sepal_width_avg*Versicolour_sepal_width_avg) - (np.square(Versicolour_sepal_width_avg).sum()/50))/ 50
Virginica_sepal_width_var = ((Virginica_sepal_width_avg*Virginica_sepal_width_avg) - (np.square(Virginica_sepal_width_avg).sum()/50))/ 50
setosa_pepal_length_var = ((setosa_pepal_length_avg*setosa_pepal_length_avg) - (np.square(setosa_pepal_length_avg).sum()/50))/ 50
Versicolour_pepal_length_var = ((Versicolour_pepal_length_avg*Versicolour_pepal_length_avg) - (np.square(Versicolour_pepal_length_avg).sum()/50))/ 50
Virginica_pepal_length_var = ((Virginica_pepal_length_avg*Virginica_pepal_length_avg) - (np.square(Virginica_pepal_length_avg).sum()/50))/ 50
setosa_pepal_width_var = ((setosa_pepal_width_avg*setosa_pepal_width_avg) - (np.square(setosa_pepal_width_avg).sum()/50))/ 50
Versicolour_pepal_width_var = ((Versicolour_pepal_width_avg*Versicolour_pepal_width_avg) - (np.square(Versicolour_pepal_width_avg).sum()/50))/ 50
Virginica_pepal_width_var = ((Virginica_pepal_width_avg*Virginica_pepal_width_avg) - (np.square(Virginica_pepal_width_avg).sum()/50))/ 50

x_range = np.zeros(100)
i = 0
count = 0

for _ in range(0,100):
        x_range[count] = i
        i = i + 0.1
        count = count + 1


#kde 구현
#sepal_length
setosa_sepal_length_kde = np.zeros(100)
setosa_sepal_length_kde = Make_KED_Function(setosa_sepal_length, math.sqrt(setosa_sepal_length_var ))

Versicolour_sepal_length_kde = np.zeros(100)
Versicolour_sepal_length_kde = Make_KED_Function(Versicolour_sepal_length, math.sqrt(Versicolour_sepal_length_var))

Virginica_sepal_length_kde = np.zeros(100)
Virginica_sepal_length_kde = Make_KED_Function(Virginica_sepal_length, math.sqrt(Virginica_sepal_length_var))

#sepal width
setosa_sepal_width_kde = np.zeros(100)
setosa_sepal_width_kde = Make_KED_Function(setosa_sepal_width, math.sqrt(setosa_sepal_width_var ))

Versicolour_sepal_width_kde = np.zeros(100)
Versicolour_sepal_width_kde = Make_KED_Function(Versicolour_sepal_width, math.sqrt(Versicolour_sepal_width_var ))

Virginica_sepal_width_kde = np.zeros(100)
Virginica_sepal_width_kde = Make_KED_Function(Virginica_sepal_width, math.sqrt(Virginica_sepal_width_var ))

#pepal length
setosa_pepal_length_kde = np.zeros(100)
setosa_pepal_length_kde = Make_KED_Function(setosa_pepal_length, math.sqrt(setosa_pepal_length_var ))

Versicolour_pepal_length_kde = np.zeros(100)
Versicolour_pepal_length_kde = Make_KED_Function(Versicolour_pepal_length, math.sqrt(Versicolour_pepal_length_var))

Virginica_pepal_length_kde = np.zeros(100)
Virginica_pepal_length_kde = Make_KED_Function(Virginica_pepal_length, math.sqrt(Virginica_pepal_length_var))

#pepal width
setosa_pepal_width_kde = np.zeros(100)
setosa_pepal_width_kde = Make_KED_Function(setosa_pepal_width, math.sqrt(setosa_pepal_width_var ))

Versicolour_pepal_width_kde = np.zeros(100)
Versicolour_pepal_width_kde = Make_KED_Function(Versicolour_pepal_width, math.sqrt(Versicolour_pepal_width_var ))

Virginica_pepal_width_kde = np.zeros(100)
Virginica_pepal_width_kde = Make_KED_Function(Virginica_pepal_width, math.sqrt(Virginica_pepal_width_var ))

#-----------------------------------------------problem3. pmf----------------------------------------------------------
pb3_setosa_sepal_length_proper = np.zeros(100)
pb3_Versicolour_sepal_length_proper = np.zeros(100)
pb3_Virginica_sepal_length_proper = np.zeros(100)
pb3_setosa_sepal_width_proper = np.zeros(100)
pb3_Versicolour_sepal_width_proper = np.zeros(100)
pb3_Virginica_sepal_width_proper = np.zeros(100)
pb3_setosa_pepal_length_proper = np.zeros(100)
pb3_Versicolour_pepal_length_proper = np.zeros(100)
pb3_Virginica_pepal_length_proper = np.zeros(100)
pb3_setosa_pepal_width_proper = np.zeros(100)
pb3_Versicolour_pepal_width_proper = np.zeros(100)
pb3_Virginica_pepal_width_proper = np.zeros(100)

#-------------------------------sepal_length-------------------
#setosa_sepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)

for _ in range(0,100):
        sum1 = round(setosa_sepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0

print("setosa_sepal_length  property")

for _ in range(0,100):
    result = round(setosa_sepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_setosa_sepal_length_proper[count1] = result1[count1]
    print(str(round(count2,2)) + ": " + str(pb3_setosa_sepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1

print("-------------------------------")

#versicolor_sepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)

for _ in range(0,100):
        sum1 = round(Versicolour_sepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0
print("versicolor_sepal_length  property")
for _ in range(0,100):
    result = round(Versicolour_sepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Versicolour_sepal_length_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Versicolour_sepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#Virginica_sepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Virginica_sepal_length  property")
for _ in range(0,100):
        sum1 = round(Virginica_sepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0

for _ in range(0,100):
    result = round(Virginica_sepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Virginica_sepal_length_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Virginica_sepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#-------------------------------sepal_width-------------------
#setosa_sepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("setosa_sepal_width  property")
for _ in range(0,100):
        sum1 = round(setosa_sepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0

for _ in range(0,100):
    result = round(setosa_sepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_setosa_sepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_setosa_sepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")

#Versicolour_sepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Versicolour_sepal_width  property")
for _ in range(0,100):
        sum1 = round(Versicolour_sepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0

for _ in range(0,100):
    result = round(Versicolour_sepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Versicolour_sepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Versicolour_sepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#Virginica_sepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Virginica_sepal_width  property")
for _ in range(0,100):
        sum1 = round(Virginica_sepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0


for _ in range(0,100):
    result = round(Virginica_sepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Virginica_sepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Virginica_sepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#pepal length
#setosa_pepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("setosa_pepal_length  property")
for _ in range(0,100):
        sum1 = round(setosa_pepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0


for _ in range(0,100):
    result = round(setosa_pepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_setosa_pepal_length_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_setosa_pepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#versicolor_pepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)

for _ in range(0,100):
        sum1 = round(Versicolour_pepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0
print("versicolor_pepal_length  property")

for _ in range(0,100):
    result = round(Versicolour_pepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Versicolour_pepal_length_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Versicolour_pepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")

#Virginica_pepal_length pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Virginica_pepal_length  property")
for _ in range(0,100):
        sum1 = round(Virginica_pepal_length_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0


for _ in range(0,100):
    result = round(Virginica_pepal_length_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Virginica_pepal_length_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Virginica_pepal_length_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#pepal width
#setosa_pepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("setosa_pepal_width  property")
for _ in range(0,100):
        sum1 = round(setosa_pepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0


for _ in range(0,100):
    result = round(setosa_pepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_setosa_pepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_setosa_pepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#Versicolour_pepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Versicolour_pepal_width  property")
for _ in range(0,100):
        sum1 = round(Versicolour_pepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0


for _ in range(0,100):
    result = round(Versicolour_pepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Versicolour_pepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Versicolour_pepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")
#Virginica_pepal_width pmf
count1 = 0
count2 = 0.1
sum1 = 0
result = 0
result1 = np.zeros(100)
print("Virginica_pepal_width  property")
for _ in range(0,100):
        sum1 = round(Virginica_pepal_width_kde[count1],2) + sum1
        count1 = count1 + 1

count1 = 0

for _ in range(0,100):
    result = round(Virginica_pepal_width_kde[count1],2) / round(sum1 ,2)
    result1[count1] = round(result, 2)
    pb3_Virginica_pepal_width_proper[count1] = result1[count1]
    print(str(round(count2, 2)) + ": " + str(pb3_Virginica_pepal_width_proper[count1]))
    count1 = count1 + 1
    count2 = count2+0.1
print("-------------------------------")

#--------------------------------------------------Draw the kde graph----------------------------------------------------------------
#sepal_length, likelihood(5.48, 6.25)
plt.plot(x_range, setosa_sepal_length_kde,label="setosa")
plt.plot(x_range, Versicolour_sepal_length_kde,label="versicolor")
plt.plot(x_range, Virginica_sepal_length_kde,label="virginica")

plt.title("Sepal Lengths")
plt.xlabel("Sepal Length (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()

#sepal_width, likelihood(2.90, 3.19)
plt.plot(x_range, setosa_sepal_width_kde,label="setosa")
plt.plot(x_range, Versicolour_sepal_width_kde,label="versicolor")
plt.plot(x_range, Virginica_sepal_width_kde,label="virginica")

plt.title("Sepal widths")
plt.xlabel("Sepal width (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()

#pepal_length, likelihood(2.23,4.90)
plt.plot(x_range, setosa_pepal_length_kde,label="setosa")
plt.plot(x_range, Versicolour_pepal_length_kde,label="versicolor")
plt.plot(x_range, Virginica_pepal_length_kde,label="virginica")

plt.title("Pepal Lengths")
plt.xlabel("Pepal Length (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()

#pepal_width, likelihood(0.70,1.65)
plt.plot(x_range, setosa_pepal_width_kde,label="setosa")
plt.plot(x_range, Versicolour_pepal_width_kde,label="versicolor")
plt.plot(x_range, Virginica_pepal_width_kde,label="virginica")

plt.title("Pepal_widths")
plt.xlabel("pepal_width (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()




#-------------------------------------------Draw the histogram---------------------------------------------------------
#sepal_length
sns.distplot(setosa_sepal_length, kde=False, color="blue", label="setosa",bins=10,)
sns.distplot(Versicolour_sepal_length, kde=False,  color="red", label="versicolor",bins=10)
sns.distplot(Virginica_sepal_length, kde=False,  color="green", label="virginica",bins=10)

plt.title("Sepal Lengths")
plt.xlabel("Sepal Length (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()


#sepal width
sns.distplot(setosa_sepal_width, kde=False, color="blue", label="setosa",bins=10)
sns.distplot(Versicolour_sepal_width, kde=False,  color="red", label="versicolor",bins=10)
sns.distplot(Virginica_sepal_width, kde=False,  color="green", label="virginica",bins=10)

plt.title("Sepal widths")
plt.xlabel("Sepal width (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()

#pepal lenght
sns.distplot(setosa_pepal_length, kde=False, color="blue", label="setosa",bins=10)
sns.distplot(Versicolour_pepal_length, kde=False,  color="red", label="versicolor",bins=10)
sns.distplot(Virginica_pepal_length, kde=False, color="green", label="virginica",bins=10)

plt.title("pepal Lengths")
plt.xlabel("pepal Length (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()

#pepal width
sns.distplot(setosa_pepal_width, kde=False,  color="blue", label="setosa",bins=10)
sns.distplot(Versicolour_pepal_width, kde=False,  color="red", label="versicolor",bins=10)
sns.distplot(Virginica_pepal_width, kde=False, color="green", label="virginica",bins=10)

plt.title("Pepal widths")
plt.xlabel("Pepal width (cm)")
plt.ylabel("Density")
plt.legend(title="Species")

plt.show()
'''

'''
#draw the scatter plot(sepal length, sepal width, pepal length, pepal width)
#sepal length, sepal width

#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_sepal_length_avg, setosa_sepal_width_avg, setosa_sepal_length, setosa_sepal_width)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_sepal_length_avg, Versicolour_sepal_width_avg, Versicolour_sepal_length, Versicolour_sepal_width)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_sepal_length_avg, Virginica_sepal_width_avg, Virginica_sepal_length, Virginica_sepal_width)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]


print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")



#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(setosa_sepal_length, setosa_sepal_width, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_sepal_length, Versicolour_sepal_width, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_sepal_length, Virginica_sepal_width, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Sepal length | Sepal width')
plt.xlabel('Sepal length')
plt.ylabel('Sepal width')
plt.legend(title="Species")

plt.show()

#sepal length, pepal length
#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_sepal_length_avg, setosa_pepal_length_avg, setosa_sepal_length, setosa_pepal_length)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_sepal_length_avg, Versicolour_pepal_length_avg, Versicolour_sepal_length, Versicolour_pepal_length)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_sepal_length_avg, Virginica_pepal_length_avg, Virginica_sepal_length, Virginica_pepal_length)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]

print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")



#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(setosa_sepal_length, setosa_pepal_length, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_sepal_length, Versicolour_pepal_length, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_sepal_length, Virginica_pepal_length, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Sepal length | Pepal_length')
plt.xlabel('Sepal length')
plt.ylabel('Pepal length')
plt.legend(title="Species")

plt.show()

#sepal length, pepal width
#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_sepal_length_avg, setosa_pepal_width_avg, setosa_sepal_length, setosa_pepal_width)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_sepal_length_avg, Versicolour_pepal_width_avg, Versicolour_sepal_length, Versicolour_pepal_width)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_sepal_length_avg, Virginica_pepal_width_avg, Virginica_sepal_length, Virginica_pepal_width)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]

print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")



#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(setosa_sepal_length, setosa_pepal_width, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_sepal_length, Versicolour_pepal_width, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_sepal_length, Virginica_pepal_width, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Sepal length | Pepal width')
plt.xlabel('Sepal length')
plt.ylabel('Pepal width')
plt.legend(title="Species")

plt.show()



#sepal width, pepal length
#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_sepal_width_avg, setosa_pepal_length_avg, setosa_sepal_width, setosa_pepal_length)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_sepal_width_avg, Versicolour_pepal_length_avg, Versicolour_sepal_width, Versicolour_pepal_length)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_sepal_width_avg, Virginica_pepal_length_avg, Virginica_sepal_width, Virginica_pepal_length)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]


print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")

#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)

plt.plot(setosa_sepal_width, setosa_pepal_length, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_sepal_width, Versicolour_pepal_length, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_sepal_width, Virginica_pepal_length, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Sepal width | Pepal length')
plt.xlabel('Sepal width')
plt.ylabel('Pepal length')
plt.legend(title="Species")

plt.show()

#sepal width, pepal width
#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_sepal_width_avg, setosa_pepal_width_avg, setosa_sepal_width, setosa_pepal_width)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_sepal_width_avg, Versicolour_pepal_width_avg, Versicolour_sepal_width, Versicolour_pepal_width)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_sepal_width_avg, Virginica_pepal_width_avg, Virginica_sepal_width, Virginica_pepal_width)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]

print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")


#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(setosa_sepal_width, setosa_pepal_width, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_sepal_width, Versicolour_pepal_width, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_sepal_width, Virginica_pepal_width, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Sepal width | Pepal width')
plt.xlabel('Sepal width')
plt.ylabel('Pepal width')
plt.legend(title="Species")

plt.show()


#pepal length, pepal width
#model 1
model1 = 0
a1 = 0
b1 = 0
model1= least_square_fit(setosa_pepal_length_avg, setosa_pepal_width_avg, setosa_pepal_length, setosa_pepal_width)

x1 = [a1 for a1 in range(10)]
y1 = [model1[0]*b1+model1[1] for b1 in range(10) ]

#model 2
model2 = 0
a2 = 0
b2 = 0
model2= least_square_fit(Versicolour_pepal_length_avg, Versicolour_pepal_width_avg, Versicolour_pepal_length, Versicolour_pepal_width)

x2 = [a2 for a2 in range(10)]
y2 = [model2[0]*b2+model2[1] for b2 in range(10) ]

#model 3
model3 = 0
a3 = 0
b3 = 0
model3= least_square_fit(Virginica_pepal_length_avg, Virginica_pepal_width_avg, Virginica_pepal_length, Virginica_pepal_width)

x3 = [a3 for a3 in range(10)]
y3 = [model3[0]*b3+model3[1] for b3 in range(10) ]

#model 4
x4 = [a4 for a4 in range(10)]
y4 = [((model1[0]+model2[0])/2)*b4+(model1[1]+model2[1])/2 for b4 in range(10)]

#model 5
x5 = [a5 for a5 in range(10)]
y5 = [((model2[0]+model3[0])/2)*b5+(model2[1]+model3[1])/2 for b5 in range(10)]

print(((model1[0]+model2[0])/2))
print((model1[1]+model2[1])/2)
print(((model2[0]+model3[0])/2))
print((model2[1]+model3[1])/2)
print("----------------------------------")



#-------------------------------draw----------------------------------------------------
#plt.plot(x1,y1,color='blue')
#plt.plot(x2,y2 ,color='red')
#plt.plot(x3,y3,color = 'green')
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(setosa_pepal_length, setosa_pepal_width, linestyle='none', marker='o', markersize=8, color='blue', label="setosa")
plt.plot(Versicolour_pepal_length, Versicolour_pepal_width, linestyle='none', marker='o', markersize=8, color='red', label="versicolour")
plt.plot(Virginica_pepal_length, Virginica_pepal_width, linestyle='none', marker='o', markersize=8, color='green', label="virginica")

plt.title('Pepal length | Pepal width')
plt.xlabel('Pepal length')
plt.ylabel('Pepal width')
plt.legend(title="Species")

plt.show()
