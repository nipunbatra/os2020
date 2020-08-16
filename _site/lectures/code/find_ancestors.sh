echo "Gello"
findFather(){
    
    ppid=$(ps ho ppid $1)
    echo $ppid
    [ $ppid -gt 1 ] &&  findFather $ppid
}
findFather
