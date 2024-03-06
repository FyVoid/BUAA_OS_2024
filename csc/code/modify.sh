awk '{gsub(/'$2'/, "'$3'"); print}' $1 > tmp
cat tmp > $1
rm tmp

