#!/bin/bash

uml_dir=ClassDiagram
mkdir -p $uml_dir

touch $uml_dir/import_classes.puml
echo "@startuml import_classes" > $uml_dir/import_classes.puml
for folder in */
do
    echo $folder
    mkdir -p $uml_dir/$folder
    for file in $(find $folder -name *.hpp)
    do
        echo $file
        targetfile=${file//"hpp"/puml}

        name=$(echo $file | rev | cut -d"/" -f 1 | rev)
        name=${name//".hpp"/}
        firstline='@startuml '$name'(id='$name')'
        secondline='skinparam classAttributeIconSize 0'

        hpp2plantuml -i $file -o $uml_dir/$targetfile
        
        tail -n +2 $uml_dir/$targetfile > temp && mv temp $uml_dir/$targetfile
        echo $secondline | cat - $uml_dir/$targetfile > temp && mv temp $uml_dir/$targetfile
        echo $firstline | cat - $uml_dir/$targetfile > temp && mv temp $uml_dir/$targetfile
        plantuml -tpng  $uml_dir/$targetfile /$uml_dir
    
        echo "!include $targetfile!$name" >> $uml_dir/import_classes.puml
    done
done

echo "@enduml" >> $uml_dir/import_classes.puml