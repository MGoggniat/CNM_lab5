Normal sieve 100'000

============= Time measures ===============
Init time :     0.001169
Sieve time :    2.207875
Extract time :  0.000544
Display time :  0.003027
Total time :    2.212615


OMP sieve 100'000
============= Time measures ===============
For 8 threads
Init time :     0.001117
Sieve time :    2.238839
Extract time :  0.001138
Display time :  0.003127
Total time :    2.244221

============= Time measures ===============
For 1 threads
Init time :     0.001184
Sieve time :    2.195234
Extract time :  0.000541
Display time :  0.003480
Total time :    2.200439

CUDA sieve 100'000

============= Time measures ===============
Init time :     0.001174
Sieve time :    0.056964
Extract time :  0.001118
Display time :  0.006168
Total time :    0.065424

CUDA en commentant la ligne //kernel<<<numBlocks, blockSize>>>(sieveArraySize, d_sieveArray);
on voit que presque tout le temps de sieve est pour l'allocation mémoire gpu / copie mémoire
on ne constate aucune modification en augmentant le nombre de bloc car le calcul est trop rapide
Il est important de mettre assez de bloc car pour un grand nombre (100'000 par ex) un seul bloc n'a
pas assez de mémoire partagée

============= Time measures ===============
Init time :     0.001173
Sieve time :    0.057847
Extract time :  0.000397
Display time :  0.000128
Total time :    0.059545