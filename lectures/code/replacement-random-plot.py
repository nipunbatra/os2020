import random
import sys
import pandas as pd
import matplotlib.pyplot as plt

workload = [1,2,3,4,1,2,3,4,3,2,1]
cache_size = 3


def r_replacement(seed):
    random.seed(seed)
    cache_content = []
    hit_count = 0
    miss_count = 0
    #print("Iteration", "page", "cache_content (after)")
    for iteration, page in enumerate(workload):
        if page in cache_content:
            # Hit!
            #print("Cache hit!")
            hit_count +=1
        else:
            miss_count +=1
            #print("Cache miss!")
            if len(cache_content) < cache_size:
                cache_content.append(page)
            else:
                # Need to evict
                page_evict = random.choice(cache_content)
                #print("Removing {}".format(page_evict))
                cache_content.remove(page_evict)
                cache_content.append(page)
                assert(len(cache_content)==cache_size)
        #print(iteration, page, cache_content)

    #print("Hit count for seed {} is {}".format(seed, hit_count))
    assert(hit_count+miss_count==len(workload))
    return hit_count

hit_seed = {}
for seed in range(1000):
    hit_seed[seed] = r_replacement(seed)

pd.Series(hit_seed).plot(kind='hist')
plt.xlabel("Number of hits")
plt.show()