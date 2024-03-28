import numpy as np
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

# 创建一个空的DataFrame来存储聚类结果
cluster_results = pd.DataFrame()

# 循环进行K-means聚类，并记录结果
for n_clusters in range(2, 10):
    kmeans = KMeans(n_clusters=n_clusters, random_state=0, n_init=10).fit(reduced_vectors)
    labels = kmeans.labels_
    cluster_results[f'Cluster{n_clusters}'] = labels

# 将聚类结果写入Excel文件，行表示基因名，列表示聚类结果
cluster_results = cluster_results.T
cluster_results.index = [f'Cluster{n}' for n in range(2, 10)]
cluster_results.columns = df.columns[1:]
cluster_results.to_excel('kMeans_cluster_results1.xlsx')
