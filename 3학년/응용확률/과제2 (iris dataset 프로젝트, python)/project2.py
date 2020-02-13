from matplotlib import pyplot as plt

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

setosa_sepal_length = []

i = 0

for _ in range(50):
    setosa_sepal_length = Iris_setosa_list[i][0]
    i =  i+1

plt.hist(setosa_sepal_length)
plt.show()

