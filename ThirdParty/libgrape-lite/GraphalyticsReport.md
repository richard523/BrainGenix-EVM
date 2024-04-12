# Graphalytics Report

The previous commit refactored the memory management in the message manager, resulting in a slight performance improvement. This document compares the performance of commit 4944d80 and commit 40f08a4 on LDBC Graphalytics. Commit 4944d80 is the version participating in the LDBC Graphalytics Competition 2023.

## Configurations

- cluster: 8 instances of ecs.r7.16xlarge
- system configurations for hugepages: allocate 130174 2MB persistent hugetlb pages in the kernel's huge page pool
- compiling flags: cmake -DUSE_HUGEPAGES=ON -DUSE_SIMD=ON ..
- runtime flags: --opt

## Results on 2XL+ Datasets

| Algorithm | Dataset          | Run-0  | Run-1  | Run-2  | Avg(4944d80) | Run-0    | Run-1    | Run-2    | Avg(40f08a4) |
|-----------|------------------|--------|--------|--------|--------------|----------|----------|----------|--------------|
| BFS       | datagen-sf10k-fb | 0.161  | 0.156  | 0.16   | 0.159        | 0.147969 | 0.153708 | 0.151054 | 0.15091033   |
|           | graph500-28      | 0.389  | 0.388  | 0.436  | 0.40433333   | 0.332436 | 0.330191 | 0.321635 | 0.32808733   |
|           | graph500-29      | 0.782  | 0.76   | 0.768  | 0.77         | 0.640984 | 0.651217 | 0.64728  | 0.64649367   |
|           | graph500-30      | 1.437  | 1.436  | 1.431  | 1.43466667   | 1.2105   | 1.20078  | 1.23213  | 1.21447      |
| WCC       | datagen-sf10k-fb | 0.915  | 0.912  | 0.92   | 0.91566667   | 0.829834 | 0.82791  | 0.833734 | 0.83049267   |
|           | graph500-28      | 1.414  | 1.39   | 1.407  | 1.40366667   | 1.17079  | 1.19715  | 1.1547   | 1.17421333   |
|           | graph500-29      | 2.982  | 3.053  | 3.018  | 3.01766667   | 2.48582  | 2.63086  | 2.58466  | 2.56711333   |
|           | graph500-30      | 6.458  | 6.416  | 6.386  | 6.42         | 5.78149  | 5.63968  | 5.43152  | 5.61756333   |
| CDLP      | datagen-sf10k-fb | 6.676  | 6.657  | 6.677  | 6.67         | 6.69863  | 6.71152  | 6.72455  | 6.71156667   |
|           | graph500-28      | 3.536  | 3.541  | 3.569  | 3.54866667   | 3.25324  | 3.28292  | 3.24624  | 3.2608       |
|           | graph500-29      | 7.024  | 7.087  | 7.148  | 7.08633333   | 6.60817  | 6.58306  | 6.55058  | 6.58060333   |
|           | graph500-30      | 15.387 | 15.353 | 15.352 | 15.364       | 14.3468  | 14.2793  | 14.2591  | 14.2950667   |
| LCC       | datagen-sf10k-fb | 20.301 | 20.855 | 20.814 | 20.6566667   | 18.3038  | 18.1838  | 18.1707  | 18.2194333   |
|           | graph500-28      | 63.526 | 64.422 | 64.09  | 64.0126667   | 60.429   | 60.0627  | 60.086   | 60.1925667   |
|           | graph500-29      | 144.99 | 145.6  | 145.43 | 145.34       | 136.646  | 137.447  | 136.783  | 136.958667   |
|           | graph500-30      | 333.82 | 334.74 | 334.89 | 334.486      | 317.691  | 319.1    | 317.949  | 318.246667   |
| PR        | datagen-sf10k-fb | 3.819  | 3.777  | 3.823  | 3.80633333   | 3.59498  | 3.55539  | 3.53666  | 3.56234333   |
|           | graph500-28      | 4.591  | 4.616  | 4.596  | 4.601        | 4.37156  | 4.43652  | 4.43313  | 4.41373667   |
|           | graph500-29      | 9.378  | 9.484  | 9.449  | 9.437        | 9.13917  | 9.06991  | 9.17298  | 9.12735333   |
|           | graph500-30      | 19.695 | 19.743 | 19.648 | 19.6953333   | 19.1781  | 19.114   | 19.2361  | 19.1760667   |
| SSSP      | datagen-sf10k-fb | 0.945  | 0.947  | 0.945  | 0.94566667   | 0.927446 | 0.935689 | 0.943155 | 0.93543      |

## Results on XL Datasets

| Algorithm | Dataset         | Run-0  | Run-1  | Run-2  | Avg(4944d80) | Run-0     | Run-1     | Run-2     | Avg(40f08a4) |
|-----------|-----------------|--------|--------|--------|--------------|-----------|-----------|-----------|------------|
| BFS       | com-friendster  | 0.293  | 0.287  | 0.307  | 0.29566667   | 0.273735  | 0.278371  | 0.275095  | 0.27573367 |
|           | datagen-9_0-fb  | 0.071  | 0.064  | 0.066  | 0.067        | 0.0673618 | 0.065789  | 0.0596471 | 0.06426597 |
|           | datagen-9_1-fb  | 0.061  | 0.066  | 0.063  | 0.06333333   | 0.05896   | 0.0564909 | 0.0674961 | 0.06098233 |
|           | datagen-9_2-zf  | 0.396  | 0.418  | 0.405  | 0.40633333   | 0.403863  | 0.390583  | 0.405155  | 0.399867   |
|           | datagen-9_3-zf  | 0.493  | 0.497  | 0.483  | 0.491        | 0.466007  | 0.468733  | 0.473893  | 0.46954433 |
|           | datagen-9_4-fb  | 0.081  | 0.081  | 0.092  | 0.08466667   | 0.0881181 | 0.0778179 | 0.0782251 | 0.08138703 |
|           | datagen-sf3k-fb | 0.084  | 0.089  | 0.095  | 0.08933333   | 0.0870421 | 0.0790961 | 0.0775571 | 0.08123177 |
|           | graph500-26     | 0.146  | 0.136  | 0.145  | 0.14233333   | 0.122877  | 0.127464  | 0.130438  | 0.12692633 |
|           | graph500-27     | 0.217  | 0.208  | 0.217  | 0.214        | 0.190422  | 0.190183  | 0.185231  | 0.188612   |
|           | twitter_mpi     | 0.223  | 0.223  | 0.222  | 0.22266667   | 0.206047  | 0.211668  | 0.205439  | 0.207718   |
| WCC       | com-friendster  | 0.836  | 0.856  | 0.847  | 0.84633333   | 0.734736  | 0.688219  | 0.75898   | 0.72731167 |
|           | datagen-9_0-fb  | 0.148  | 0.157  | 0.148  | 0.151        | 0.131593  | 0.126634  | 0.137955  | 0.13206067 |
|           | datagen-9_1-fb  | 0.194  | 0.193  | 0.195  | 0.194        | 0.17229   | 0.168127  | 0.178071  | 0.17282933 |
|           | datagen-9_2-zf  | 0.328  | 0.329  | 0.331  | 0.32933333   | 0.297944  | 0.280041  | 0.295364  | 0.29111633 |
|           | datagen-9_3-zf  | 0.423  | 0.438  | 0.431  | 0.43066667   | 0.39478   | 0.379965  | 0.38261   | 0.385785   |
|           | datagen-9_4-fb  | 0.315  | 0.316  | 0.324  | 0.31833333   | 0.294946  | 0.271082  | 0.278796  | 0.281608   |
|           | datagen-sf3k-fb | 0.379  | 0.368  | 0.373  | 0.37333333   | 0.325671  | 0.326065  | 0.311924  | 0.32122    |
|           | graph500-26     | 0.36   | 0.379  | 0.374  | 0.371        | 0.303936  | 0.295484  | 0.301651  | 0.300357   |
|           | graph500-27     | 0.739  | 0.738  | 0.731  | 0.736        | 0.603281  | 0.595716  | 0.586651  | 0.595216   |
|           | twitter_mpi     | 0.768  | 0.73   | 0.763  | 0.75366667   | 0.634787  | 0.638041  | 0.640087  | 0.63763833 |
| CDLP      | com-friendster  | 2.778  | 2.766  | 2.762  | 2.76866667   | 2.62144   | 2.63405   | 2.63326   | 2.62958333 |
|           | datagen-9_0-fb  | 0.839  | 0.845  | 0.84   | 0.84133333   | 0.81241   | 0.812189  | 0.809143  | 0.81124733 |
|           | datagen-9_1-fb  | 1.046  | 1.04   | 1.044  | 1.04333333   | 1.0051    | 1.01428   | 1.00973   | 1.00970333 |
|           | datagen-9_2-zf  | 1.384  | 1.373  | 1.367  | 1.37466667   | 1.26711   | 1.27104   | 1.25995   | 1.26603333 |
|           | datagen-9_3-zf  | 1.744  | 1.721  | 1.73   | 1.73166667   | 1.58631   | 1.55863   | 1.57769   | 1.57421    |
|           | datagen-9_4-fb  | 1.911  | 1.914  | 1.912  | 1.91233333   | 1.85903   | 1.84524   | 1.85356   | 1.85261    |
|           | datagen-sf3k-fb | 2.163  | 2.163  | 2.16   | 2.162        | 2.09031   | 2.09749   | 2.09178   | 2.09319333 |
|           | graph500-26     | 0.892  | 0.878  | 0.901  | 0.89033333   | 0.783956  | 0.787728  | 0.796549  | 0.789411   |
|           | graph500-27     | 1.754  | 1.739  | 1.736  | 1.743        | 1.56406   | 1.57269   | 1.57987   | 1.57220667 |
|           | twitter_mpi     | 11.18  | 11.058 | 11.055 | 11.0976667   | 11.1798   | 11.0223   | 11.0865   | 11.0962    |
| LCC       | com-friendster  | 9.613  | 9.943  | 9.318  | 9.62466667   | 8.14113   | 8.26958   | 8.30719   | 8.2393     |
|           | datagen-9_0-fb  | 2.948  | 2.975  | 3.031  | 2.98466667   | 2.61915   | 2.56456   | 2.66568   | 2.61646333 |
|           | datagen-9_1-fb  | 3.647  | 3.665  | 3.631  | 3.64766667   | 3.21238   | 3.24971   | 3.29004   | 3.25071    |
|           | datagen-9_2-zf  | 0.854  | 0.854  | 0.868  | 0.85866667   | 0.670904  | 0.644172  | 0.643516  | 0.652864   |
|           | datagen-9_3-zf  | 1.06   | 1.062  | 1.049  | 1.057        | 0.848262  | 0.770813  | 0.77038   | 0.796485   |
|           | datagen-9_4-fb  | 6.593  | 6.572  | 6.502  | 6.55566667   | 5.62747   | 5.6587    | 5.63488   | 5.64035    |
|           | datagen-sf3k-fb | 7.31   | 7.219  | 7.419  | 7.316        | 6.27178   | 6.32444   | 6.34943   | 6.31521667 |
|           | graph500-26     | 12.486 | 12.48  | 12.606 | 12.524       | 11.5906   | 11.6009   | 11.7669   | 11.6528    |
|           | graph500-27     | 28.342 | 28.315 | 28.163 | 28.2733333   | 26.1338   | 26.0895   | 26.1976   | 26.1403    |
|           | twitter_mpi     | 21.044 | 20.891 | 20.778 | 20.9043333   | 18.0782   | 17.9579   | 18.0275   | 18.0212    |
| PR        | com-friendster  | 2.812  | 2.769  | 2.765  | 2.782        | 2.68977   | 2.65567   | 2.71283   | 2.68609    |
|           | datagen-9_0-fb  | 0.611  | 0.601  | 0.607  | 0.60633333   | 0.611097  | 0.602088  | 0.608674  | 0.60728633 |
|           | datagen-9_1-fb  | 0.722  | 0.733  | 0.717  | 0.724        | 0.709839  | 0.701382  | 0.704358  | 0.705193   |
|           | datagen-9_2-zf  | 0.972  | 0.99   | 0.977  | 0.97966667   | 0.864043  | 0.856392  | 0.874125  | 0.86485333 |
|           | datagen-9_3-zf  | 1.164  | 1.159  | 1.184  | 1.169        | 1.03553   | 1.07419   | 1.09088   | 1.06686667 |
|           | datagen-9_4-fb  | 1.285  | 1.283  | 1.274  | 1.28066667   | 1.16082   | 1.15079   | 1.17189   | 1.16116667 |
|           | datagen-sf3k-fb | 1.423  | 1.461  | 1.436  | 1.44         | 1.31089   | 1.3089    | 1.29841   | 1.30606667 |
|           | graph500-26     | 1.444  | 1.476  | 1.437  | 1.45233333   | 1.49242   | 1.47717   | 1.43308   | 1.46755667 |
|           | graph500-27     | 2.354  | 2.35   | 2.401  | 2.36833333   | 2.32072   | 2.3087    | 2.32472   | 2.31804667 |
|           | twitter_mpi     | 2.93   | 2.87   | 2.856  | 2.88533333   | 2.95619   | 3.00794   | 2.93378   | 2.96597    |
| SSSP      | datagen-9_0-fb  | 0.145  | 0.144  | 0.143  | 0.144        | 0.133025  | 0.135114  | 0.136265  | 0.13480133 |
|           | datagen-9_1-fb  | 0.177  | 0.177  | 0.185  | 0.17966667   | 0.160117  | 0.167383  | 0.169869  | 0.16578967 |
|           | datagen-9_2-zf  | 0.555  | 0.555  | 0.542  | 0.55066667   | 0.543128  | 0.520067  | 0.54567   | 0.53628833 |
|           | datagen-9_3-zf  | 0.72   | 0.695  | 0.715  | 0.71         | 0.686377  | 0.642784  | 0.683938  | 0.671033   |
|           | datagen-9_4-fb  | 0.304  | 0.312  | 0.332  | 0.316        | 0.304866  | 0.293934  | 0.300606  | 0.299802   |
|           | datagen-sf3k-fb | 0.348  | 0.335  | 0.339  | 0.34066667   | 0.330866  | 0.316258  | 0.322607  | 0.32324367 |