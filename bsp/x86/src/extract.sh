#! /bin/sh


imap=$1
iout=$2

echo "!!! extract symbol from $imap to $iout !!!"

symlist="rt_kprintf \
rt_kputs \
rt_vsprintf \
rt_sprintf \
rt_snprintf \
rt_thread_create \
"

echo "#ifndef RT_THREAD_SYM_H_H" > $iout
echo "#define RT_THREAD_SYM_H_H" >> $iout

for sym in $symlist
do
dlim=`echo $sym | cut -b 1`
addr=`cat $imap | grep $sym | head -n 1 | cut -d $dlim -f 1`

echo "#define __abs_$sym $addr" >> $iout
done

echo "#endif /* RT_THREAD_SYM_H_H */" >> $iout
