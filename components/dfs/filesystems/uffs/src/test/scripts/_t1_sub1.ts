# $9 --- fd
# $8 --- counter, file content

evl $8 % 60
set 6 $1
evl $1 * 508
set 7 $1

echo --- testing n = $8 / $6, offset = $7 ---

t_seek $9 $7 s
! abort --- seek file failed ---
t_write $9 $8
! abort --- write file (n=$8) failed ---
t_seek $9 $7 s
! abort --- seek file failed ---
t_read $9 $8
! abort --- read file compare failed n=$8 ---

evl $8 + 1
set 8 $1

