rm /test_seek.bin

# create a new file
t_open wc /test_seek.bin

! abort ---- create file failed ----
set 9 $1  # opened fd => $9

# test seek and write
t_write $9 hello-world
! abort ---- write file failed ----
t_seek $9 5 s
! abort --- seek file to 5 failed ---
test $1 == 5
! abort --- file pointer is not 5 ---
t_write $9 &
! abort --- write '&' at position 5 failed ---
t_seek $9 0 s
! abort --- seek file to 0 failed
test $1 == 0
! abort -- file pointer not 0 ---
t_read $9 hello&world
! abort --- check file failed ---

# test seek in different options
t_seek $9 0 s
test $1 == 0
! abort -- file pointer seek to 0 s failed --
t_seek $9 100 s
test $1 == 100
! abort -- file pointer seek to 100 s failed --
t_seek $9 10 c
test $1 == 110
! abort -- file pointer seek to +10 c failed --
t_seek $9 -10 c
test $1 == 100
! abort -- file pointer seek to -10 c failed --
t_seek $9 0 e
test $1 == 11
! abort -- file pointer seek to 0 e failed --
t_seek $9 -1 e
test $1 == 10
! abort -- file pointer seek to -1 e failed --
t_seek $9 10 e
test $1 == 21
! abort -- file pointer seek to +10 e failed --

# now the file pointer is passed over the end of file,
# write to it will increase file size and filling 0 in the gap

t_write $9 a
test $? == 0
! abort -- file write to position passed over file length failed --
t_seek $9 0 e
test $1 == 22
! abort -- file new length not filling the gap --

t_close $9
! abort --- close file failed ---
echo === test seek success ===
