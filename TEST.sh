echo Stress test tp1
for i in 1 10 100 1000 10000 100000 1000000
do
echo $i entries
echo 2 dimensions
./DataGenerator -n $i -d 2 -o TestPoints -I
./DataGenerator -n $i -d 2 -o TestQuery
START=$(date +%s%3N)
./tp1 -p TestPoints -i TestQuery -o TestOut
FINISH=$(date +%s%3N)
(( DURATION = FINISH - START ))
printf 'Tardó %f milisegundos\n' "$DURATION"
done
exit 0
