# @Author: sun000
# @Date:   2018-06-02 11:39:24
# @Last Modified by:   sun000
# @Last Modified time: 2018-06-03 15:39:30
echo "Please Input the number of iteration: "
read epoch
while ((epoch > 0)) ; do  
    let "epoch--"
    ./dataMaker > tmp.in #出数据  
    time ./main < tmp.in > my.out #被测程序   
    time ./ddq < tmp.in > std.out #正确（暴力）程序  
    if diff my.out std.out; then #比较两个输出文件  
        printf "$epoch AC\n" #结果相同显示AC  
    elif diff -B -b my.out std.out; then  
        printf "PE\n"  
    else  
        printf "WA\n" #结果不同显示WA，并退出  
        printf "Inpunt:\n"
        cat tmp.in
        exit 0  
    fi  
done