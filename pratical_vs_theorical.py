import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
from decimal import Decimal

epsilon = Decimal('0.0000000000000000000000000000000000000001')
# digits,time,value
path = "/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/results/data.csv"
fig = "/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/plots/timetest.png"
pvt = "/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/plots/pratical_vs_theorical.png"
s = 50


df = pd.DataFrame()
df = pd.read_csv(path)
df = df.groupby(['digits']).mean().reset_index()


df['comp'] = df['digits'].apply(lambda d : (d-1)**3)
df['comp'] = df['time']/ df['comp']


filtered_df = df.loc[~(df['comp'] == float('inf'))]
print('filered')
print(filtered_df)
means = filtered_df['comp'].mean()
stds = filtered_df['comp'].std()
threshold = 0.5

print(means)
print( means + threshold * stds)

filtered_df = filtered_df.loc[filtered_df['comp'] < means + threshold * stds]


print(filtered_df)
plt.clf()
ax = sns.lmplot(
    x='digits', 
    y='comp', 
    data=filtered_df,
    order=5, 
    ci=None, 
    scatter_kws={"s": 10, "color": "green"}, 
    line_kws={'lw':2, "color": "purple"})
plt.title("Pratical vs Theorical")
plt.xlabel('#digits')
plt.ylabel('experienced time (ms) / expected time (ms)')
# xticks = []
# ax.set_xticks(range(len(xticks)))
# ax.set_xticklabels(xticks)
plt.savefig(pvt)