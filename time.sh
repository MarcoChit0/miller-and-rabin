g++ -o mr miller_rabin.cpp -lgmpxx -lgmp
cd primes
echo digits,time,value > ../results/data.csv
for f in *.txt
do 
    for i in {1..30}
    do
        cd ..
        digits=$(echo "$f" | cut -f 1 -d '.')
        ./mr --time < primes/$f >> results/data.csv
        cd primes
    done 
done