if [ "$1" = "" ]
then
	echo ERROR: Must provide prefix for recording files to delete.
else
	rm -vf $1[0-9]*.h264
fi
