echo $1
f()
{
echo $1
x = $(ps -p $1 -o ppid)
echo "s"
echo $x
echo "h"

}
f $1


