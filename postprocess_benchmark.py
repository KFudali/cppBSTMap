import pandas as pd
import matplotlib.pyplot as plt

# Load the data
df_rand = pd.read_csv('results_rand.txt', sep='\t')
df_linear = pd.read_csv('results_linear.txt', sep='\t')
df_linearRev = pd.read_csv('results_linearRev.txt', sep='\t')

# Create a dictionary with setType as keys and DataFrames as values
dfs = {
    'rand': df_rand,
    'linear': df_linear,
    'linearRev': df_linearRev
}

#specific maps
map_types = ['vecMap', 'BSTMap', 'RBTMap', 'stdMap']
for map_type in map_types:
    fig, axs = plt.subplots(1,2,figsize=(12,5))
    for set_type, df in dfs.items():
        df_insert = df[df['quant'] == 'insert-mean']
        df_insert_err = 3 * df[df['quant'] == 'insert-sDev']
        axs[0].errorbar(df_insert['setSize'],df_insert[map_type],df_insert_err[map_type], marker='o', label=set_type)
        axs[0].set_xlabel('set size')
        axs[0].set_ylabel('Insert Time [μs]')
        axs[0].set_title(map_type + " insert operation benchmark")
        axs[0].grid()
        axs[0].legend(loc='upper left')
        df_search = df[df['quant'] == 'search-mean']
        df_search_err = 3 * df[df['quant'] == 'search-sDev']
        axs[1].errorbar(df_search['setSize'],df_search[map_type],df_search_err[map_type], marker='o', label=set_type)
        axs[1].set_xlabel('set size')
        axs[1].set_ylabel('Search Time [μs]')
        axs[1].set_title(map_type + " search operation benchmark")
        axs[1].grid()
        axs[1].legend(loc='upper left')
        y_min, y_max = axs[0].get_ylim()
        axs[1].set_ylim(y_min, y_max)

for set_type, df in dfs.items():
    df_insert = df[df['quant'] == 'insert-mean']
    df_insert_err = 3 * df[df['quant'] == 'insert-sDev']
    
    df_search = df[df['quant'] == 'search-mean']
    df_search_err = 3 * df[df['quant'] == 'search-sDev']

    fig, axs = plt.subplots(2, 1, figsize=(12, 10), sharex=True)


    for map_type in map_types:
        axs[0].errorbar(df_insert['setSize'], df_insert[map_type], df_insert_err[map_type], marker='o', label=map_type)
    axs[0].set_ylabel('Insert Time [μs]')
    axs[0].set_title('Insert and Search Operation Benchmark - ' + set_type + ' set')
    axs[0].set_yscale('log')
    axs[0].grid(True, which="both", ls="--")
    axs[0].legend(loc='upper left')

    for map_type in map_types:
        axs[1].errorbar(df_search['setSize'], df_search[map_type], df_search_err[map_type], marker='o', label=map_type)
    axs[1].set_xlabel('set size')
    axs[1].set_ylabel('Search Time [μs]')
    axs[1].set_yscale('log')
    axs[1].grid(True, which="both", ls="--")
    axs[1].legend(loc='upper left')

plt.show()