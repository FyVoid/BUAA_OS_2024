mkdir test
cp -r code test
cat ./code/14.c
i=0
while [ $i -le 15 ]
do
	gcc -c ./test/code/$i.c -o ./test/code/$i.o
	let i++
done

gcc ./test/code/*.o -o test/hello
./test/hello 2>> ./test/err.txt
mv test/err.txt ./err.txt
chmod 655 err.txt
if [ $# -eq 0 ]
then
	n=2
fi
if [ $# -eq 1 ]
then
	n=$[$1+1]
fi
if [ $# -ge 2 ]
then
	n=$[$1+$2]
fi
# sed -n "'$(n)p'" err.txt >&2
