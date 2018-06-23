import matplotlib.pyplot as plt
import numpy as np

if __name__ =='__main__':
    count=0
    while (1):
        k = int(input("聚类为几簇:"))
        # x, y, z = np.loadtxt("C:/Users/92582/Desktop/k_means/k_means/out.txt", delimiter='  ', unpack=True)
        x, y, z = np.loadtxt("C:/Users/92582/Desktop/k_means_2.0/k_means_2.0/out.txt", delimiter='  ', unpack=True)
        marker = ['+', '*', 'x', 'o','^']
        colors = ['r', 'g', 'b', 'c', 'y']
        for i in range(k):
            for j in range(len(z)):
                if (z[j] == i):
                    plt.scatter(x[j], y[j], marker=marker[i], color=colors[i], s=30)
        plt.title("k-means", fontsize=24)
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.savefig('2d_out_'+str(count)+'.jpg')
        plt.show()
        count+=1


