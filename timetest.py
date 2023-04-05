import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
from decimal import Decimal

epsilon = Decimal('0.0000000000000000000000000000000000000001')
# digits,time,value
path = "/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/results/data.csv"
fig = "/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/plots/timetest.png"

df = pd.DataFrame()
df = pd.read_csv(path)
df = df.groupby(['digits']).mean().reset_index()

print(df)
fig1, ax1 = plt.subplots()
sns.barplot(x='digits', y='time', data=df)
xticks = []
ax1.set_xticks(range(len(xticks)))
ax1.set_xticklabels(xticks)

ax1.set_title("Time test")
ax1.set_xlabel('#digits')
ax1.set_ylabel('time (ms)')
fig1.savefig(fig)