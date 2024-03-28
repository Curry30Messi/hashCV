import numpy as np
from matplotlib import pyplot as plt
from sklearn.cluster import KMeans
import pandas as pd
from sklearn.decomposition import PCA

# 从Excel读取数据
df = pd.read_excel('data.xlsx')

# 提取碱基数据，每列数据为一组碱基
n_columns_data = df.iloc[:, 1:].values.T.tolist()

# 定义碱基及其向量表示，同时包含多碱基组合
base_vector_mapping = {
    '0': np.array([0, 0, 0, 0]),
    'A': np.array([1, 0, 0, 0]),
    'T': np.array([0, 1, 0, 0]),
    'G': np.array([0, 0, 1, 0]),
    'C': np.array([0, 0, 0, 1]),
    'AT': np.array([1, 1, 0, 0]),
    'AG': np.array([1, 0, 1, 0]),
    'AC': np.array([1, 0, 0, 1]),
    'TG': np.array([0, 1, 1, 0]),
    'TC': np.array([0, 1, 0, 1]),
    'GC': np.array([0, 0, 1, 1]),
    'TGC': np.array([0, 1, 1, 1]),
    'AGC': np.array([1, 0, 1, 1]),
    'ATG': np.array([1, 1, 1, 0]),
    'ATC': np.array([1, 1, 0, 1]),
    'ATGC': np.array([1, 1, 1, 1])
}


def binary_encoding(sequence):
    # 直接查找整个序列的向量表示并返回
    try:
        return base_vector_mapping[sequence]
    except KeyError:
        # 对于不在字典中的序列，这里可以根据实际情况决定如何处理，
        # 例如，拆分序列并对单个碱基编码后再求和，或者抛出异常
        # 为了简化，假设未定义的序列将返回全零向量
        return np.array([0, 0, 0, 0])


# 对每列数据进行编码
vectors = np.array([[binary_encoding(base) for base in column] for column in n_columns_data])
vectors = vectors.reshape(201, -1)
# 对编码后的数据进行主成分分析降维
pca = PCA(n_components=2)
reduced_vectors = pca.fit_transform(vectors)

fig, axs = plt.subplots(2, 4, figsize=(16, 8))
# 打开txt文件，准备写入结果
cluster_results = pd.DataFrame()
with open('kMeans_cluster_results1.txt', 'w') as file:
    # 循环聚类
    for i in range(2, 10):
        # 使用K-means算法进行聚类
        kmeans = KMeans(n_clusters=i, random_state=0, n_init=10).fit(reduced_vectors)

        # 获取聚类标签
        labels = kmeans.labels_

        # 输出结果到txt文件
        file.write(f'Clusters: {i}\n')
        for j, label in enumerate(labels):
            file.write(f'{df.columns[j + 1]}: {label}\n')
        file.write('====================\n')
        centers = kmeans.cluster_centers_

        row = (i - 2) // 4
        col = (i - 2) % 4
        scatter = axs[row, col].scatter(reduced_vectors[:, 0], reduced_vectors[:, 1], c=labels, cmap='viridis')
        axs[row, col].scatter(centers[:, 0], centers[:, 1], c='red', marker='x')
        axs[row, col].set_title(f'{i} Clusters')
        axs[row, col].set_xlabel('Principal Component 1')
        axs[row, col].set_ylabel('Principal Component 2')

        # 添加图例
        if (i <= 5):
            legend1 = axs[row, col].legend(*scatter.legend_elements(), fontsize=8,
                                           title="Classes", loc='upper left', bbox_to_anchor=(0, 1.08),
                                           bbox_transform=axs[row, col].transAxes)
        else:
            legend1 = axs[row, col].legend(*scatter.legend_elements(), fontsize=8,
                                           title="Classes", loc='upper left', bbox_to_anchor=(0, 1.3),
                                           bbox_transform=axs[row, col].transAxes)

        axs[row, col].add_artist(legend1)

        # 显示每个颜色对应的聚类编号
        for label_num in range(i):
            x_mean = reduced_vectors[labels == label_num, 0].mean()
            y_mean = reduced_vectors[labels == label_num, 1].mean()
            axs[row, col].text(x_mean, y_mean, str(label_num), color='black', fontsize=8, ha='center', va='center')

plt.tight_layout()
fig.suptitle('kMeans_cluster_results1', fontsize=16, y=0.9999)
# 保存图片
plt.savefig('kMeans_cluster_results1.png')

# plt.show()
