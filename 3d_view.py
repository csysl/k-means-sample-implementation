import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

if __name__ =='__main__':
    count=0
    while (1):
        k = int(input("聚类为几簇:"))
        # x, y, z = np.loadtxt("C:/Users/92582/Desktop/k_means/k_means/out.txt", delimiter='  ', unpack=True)
        x, y, z ,t= np.loadtxt("C:/Users/92582/Desktop/k_means_2.0/k_means_2.0/out.txt", delimiter='  ', unpack=True)
        marker = ['+', '*', 'x', 'o','^']
        colors = ['r', 'g', 'b', 'c', 'y']
        ax=plt.subplot(111, projection='3d') #创建三维绘图
        for i in range(k):
            for j in range(len(t)):
                if (t[j] == i):
                    ax.scatter(x[j],y[j],z[j], marker=marker[i], color=colors[i])
        plt.title("k-means", fontsize=24)
        ax.set_zlabel('Z')  # 坐标轴
        ax.set_ylabel('Y')
        ax.set_xlabel('X')
        plt.savefig('3d_out_'+str(count)+'.jpg')
        plt.show()
        count+=1
