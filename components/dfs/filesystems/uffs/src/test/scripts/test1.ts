#rm /a
# * 10 t3 /a
t_open w /a
set 9 $1

echo --- test batch 1 ---
set 8 0
* 10 script _t1_sub1.ts

echo --- test batch 2 ---
set 8 32
* 10 script _t1_sub1.ts

echo --- test batch 3 ---
set 8 70
* 10 script _t1_sub1.ts

t_close $9



