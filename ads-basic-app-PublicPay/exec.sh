compile_option=debug
proj_path=./app/ads-basic-app-PublicPay
proj_name=810basic

if [ "$1" = "release" ]; then
	compile_option=release
fi
if [ "$1" = "clean" ]; then
	cd $proj_path
	make clean
	exit
fi
	./MakeCore $proj_path $proj_name  $compile_option exe
