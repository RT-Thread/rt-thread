#
# test delete file/dir
#
rm /a

#####################################
echo == test normal delete ==
#####################################

t_open cw /a
! abort --- Can't create file /a ---
set 9 $1
t_write_seq $9 100
! abort --- write file failed ---
t_close $9
! abort --- close file failed ---
rm /a
! abort --- can't delete /a ---


###############################################
echo == test not delete if a file is opened ==
###############################################

t_open cw /a
! abort --- Can't create file /a ---
set 9 $1
t_write_seq $9 100
! abort --- write file failed ---
rm /a
# this should failed, save $?(-1) to $8.
set 8 $?
t_close $9
! abort --- fail to close file ---
test $8 == -1
! abort --- can delete a file in use ? ---

######################################
echo == test delete empty dir ==
######################################

rm /xx
mkdir /xx
! abort -- can't create /xx --
mkdir /xx/yy
! abort -- can't create /xx/yy --
rm /xx/yy
! abort -- can't delete /xx/yy ---
rm /xx
! abort -- can't delet /xx

#########################################
echo == test not delete non-empty dir ==
#########################################

mkdir /xx
t1 /xx/a.txt
rm /xx
test $? == -1
! abort --- delete a non-empty dir success ?? ---
rm /xx/a.txt
! abort --- can't delete /xx/a.txt ---
rm /xx
! abort --- can't delet /xx ---


echo ##################################
echo -------- ALL TEST SUCCESS --------
echo ##################################

