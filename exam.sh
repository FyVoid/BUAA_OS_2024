mkdir test
cp -r code test
cat ./code/14.c
i=0
while [ $i -le 15 ]
do
	gcc -c ./test/code/$i.c -o ./test/code/$i.o
	let i++
done

gcc ./test/code *.o -o test/hello
test/hello 2> ./err.txt
chmod rw-r-xr-x err.txt
if [ $# -eq 0 ]
then
	n=2
fi
if [ $# -eq 1 ]
then
	n=$[$1+1]
fi
if [ $# -le 2 ]
then
	n=$[$1+$2]
fi
sed -n "$np" >&2
