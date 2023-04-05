g++ -o mr miller_rabin.cpp -lgmpxx -lgmp

for n in {2..2000}
do
    echo $n > probtest/num/$n.txt
    ./mr --prob < probtest/num/$n.txt
done 
