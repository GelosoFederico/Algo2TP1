echo Test de estres para tp1 -3 heuristicas- y tp0
for i in 1 10 100 1000 10000 100000 1000000 1000000
do
echo $i entries
echo 2 dimensions
./DataGenerator -n $i -d 2 -o TestPoints -I
./DataGenerator -n $i -d 2 -o TestQuery
START=$(date +%s%3N)
./tp1 -p TestPoints -i TestQuery -o TestOut -u -s mediana
FINISH=$(date +%s%3N)
((duration=FINISH-START))
printf 'TP1 con mediana tardó %.1f milisegundos\n' "$duration"
START=$(date +%s%3N)
./tp1 -p TestPoints -i TestQuery -o TestOut -u -s mitad
FINISH=$(date +%s%3N)
((duration=FINISH-START))
printf 'TP1 con mitad tardó %.1f milisegundos\n' "$duration"
START=$(date +%s%3N)
./tp1 -p TestPoints -i TestQuery -o TestOut -u -s promedio
FINISH=$(date +%s%3N)
((duration=FINISH-START))
printf 'TP1 con promedio tardó %.1f milisegundos\n' "$duration"
START=$(date +%s%3N)
./tp0 -p TestPoints -i TestQuery -o TestOut
FINISH=$(date +%s%3N)
((duration=FINISH-START))
printf 'TP0 tardó %.1f milisegundos\n' "$duration"
done
exit 0
