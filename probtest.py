from copy import deepcopy
import os
import pandas as pd
import seaborn as sns 
import matplotlib.pyplot as plt

dfs = pd.DataFrame(columns = ['number','p'])
fig = '/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/plots/probtest.png'
path = '/home/macsilva/Desktop/ufrgs/cadeiras/2022/02/alg_avancados/prime_numbers/miller-and-rabin/probtest'
for csv in os.listdir(path):
    if not csv == 'num':
        number = int(csv.split('.')[0])
        if (not number % 2 == 0):
            df = pd.DataFrame()
            df = pd.read_csv(path + '/' + csv)
            gt = deepcopy(df.iloc[-1]['result'])

            df = df.groupby(['result']).count().reset_index()

            if gt == '0':
                p = df.loc[df['result'] == 's']['base'].iloc[0]/ (number-1)
                newrow = {
                    'number':number,
                    'p':p,
                }
                dfs.loc[len(dfs)] = newrow

dfs = dfs.sort_values(by='number').reset_index()
print(dfs)

ax = sns.barplot(x='number', y='p', data=dfs)
xticks = []

# count = 0
# for x in dfs['number']:
    # if count >= 50:
    #     xticks.append(x)
    #     count = 0
    # count += 1

plt.xlabel('input size')
plt.ylabel('prob')

ax.set_xticks(range(len(xticks)))
ax.set_xticklabels(xticks)

plt.savefig(fig)



