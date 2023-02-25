#! bash

py_list=`find *.py`
name_list=${py_list//.py/ }

for i in ${name_list}
do
    py ${i}.py > ../gml/_${i}.inc
done
