t_open cw /a
! abort --- create file /a failed.
set 9 $1

t_write_seq $9 1000
! abort
t_write_seq $9 100
! abort
t_write_seq $9 10
! abort
t_write_seq $9 1
! abort
t_seek $9 100
! abort
t_write_seq $9 1000
! abort
t_write_seq $9 100
! abort
t_write_seq $9 10
! abort
t_write_seq $9 1
! abort
t_seek $9 500
! abort
t_write_seq $9 1000
! abort
t_write_seq $9 100
! abort
t_write_seq $9 10
! abort
t_write_seq $9 1
! abort
t_seek $9 1500
! abort
t_write_seq $9 1000
! abort
t_write_seq $9 100
! abort
t_write_seq $9 10
! abort
t_write_seq $9 1
! abort

# check ...
t_seek $9 0
! abort
t_check_seq $9 1000
! abort
t_seek $9 1
! abort
t_check_seq $9 1000
! abort
t_seek $9 1000
! abort
t_check_seq $9 10
! abort
t_seek $9 100
! abort
t_check_seq $9 500
! abort
t_seek $9 2000
! abort
t_check_seq $9 100
! abort

t_close $9
echo -- test succ --