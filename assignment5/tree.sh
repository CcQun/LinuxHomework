#!/bin/bash
vline="│   "
bnull="    "
middle="├── "
last="└── "

path=$1 #获取要展开的路径
option=$2 #获取选项

if [[ ${option} = "-a" ]] #判断是否使用a选项
then
	a=1
else
	a=0
fi

if [[ ${option} = "-d" ]] #判断是否使用d选项
then
	d=1
else
	d=0
fi

prefix=""


echo ${path}
#该函数用于展开单个文件夹，接受两个参数，第一个为要展开的文件夹路径，第二个为树状图中的前缀
tree(){
	local ph=$1
	local pf=$2
	if [ -d ${ph} ]
	then
		cd ${ph}
	
		if [ ${a} -eq 1 ]
		then
			local ls=`ls -a`
		else
			local ls=`ls`
		fi

		local j=0
		for filename in ${ls}
		do
			if [[ ${filename} != "." ]] && [[ ${filename} != ".." ]]
			then
				if [ ${d} -eq 1 ] && [ -d ${filename} ]
				then
					local flist[${j}]=${filename}
					((j++))
				elif [ ${d} -eq 0 ]
				then
					local flist[${j}]=${filename}
					((j++))
				fi
			fi
		done
		local total=${#flist[@]}  #该文件夹下的所有文件数量
		local i=0
		for ((i=0;i<${total};i++))
		do
			if [ -f ${flist[i]} ]
			then
				if [ $i -eq $((${total}-1)) ]
				then
					if [ -x ${flist[i]} ] #判断如果是可执行文件则显示成绿色
					then
						echo -e "${pf}${last}\033[1;32m${flist[i]}\033[0m"
					else
						echo "${pf}${last}${flist[i]}"
					fi
				else
					if [ -x ${flist[i]} ]
					then
						echo -e "${pf}${middle}\033[1;32m${flist[i]}\033[0m"
					else
						echo "${pf}${middle}${flist[i]}"
					fi
				fi
			elif [ -d ${flist[i]} ]
			then
				if [ $i -eq $((${total}-1)) ]
				then
					echo -e "${pf}${last}\033[34m${flist[i]}\033[0m" #文件夹全部显示为蓝色
					pre=${pf}${bnull}
			       		tree ${flist[i]} "$pre"
					cd ..
				else
					echo -e "${pf}${middle}\033[34m${flist[i]}\033[0m"
					pre=${pf}${vline}
					tree ${flist[i]} "$pre"
					cd ..
				fi
			fi	
		done
	fi	
}

tree ${path} ${prefix}
