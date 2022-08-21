import numpy as np

count = 0
for i in range(100):
    rand_matrix = np.random.rand(50, 50)
    np.savetxt('./testData/' + str(count) + '.txt', rand_matrix, delimiter = ',')
    np.savetxt('./testData/' + str(count) + 'mul.txt', np.matmul(rand_matrix, rand_matrix), delimiter = ',')
    count += 1

