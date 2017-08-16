#!/bin/sh

cur_dir=`pwd`

while [ "1" = "1" ]
do
	cd $cur_dir
	git checkout master
	sleep 2
	git pull
	sleep 10
	master_commit=`git rev-parse HEAD`
	master_commit_short=`git rev-parse --short HEAD`
	sleep 2
	if [ ! -f .last_commit.log ]; then
		echo "No last_commit.log,we init a log file"
		touch .last_commit.log
	fi

	last_commit=`cat .last_commit.log` 

	if [ "$master_commit"x != "$last_commit"x ]; then
		echo "There is a new commit on https://github.com/YUNEEC/camera_repeater/tree/master/yuneec_udp"
		echo "$master_commit" > .last_commit.log

		#git cgo3plus options
		git checkout master
		sleep 2
		make clean
		sleep 1
		git submodule update --init --recursive
		sleep 1
		git pull origin master
		sleep 10
		make CAMERA=cgo3

		if [ -f ../../camera_fimware_build/builds/cgo3plus/firmware.bin ]; then
			echo "delete the cgo3plus  firmware.bin existed in camera_firmware_build"
			rm ../../camera_firmware_build/builds/cgo3plus/firmware.bin
		fi

		if [ -f ./build/yuneec_udp ]; then
			echo "built yuneec_udp for cgo3plus binary successfully"
			cp ./build/yuneec_udp ../../fakeroot_pkg/fakeroot/usr/local/bin/
			cd ../../fakeroot_pkg
			./auto_firmware.sh
			sleep 8
			cp ./out/firmware.bin ../camera_firmware_build/builds/cgo3plus
			cd ../camera_firmware_build/builds/cgo3plus
			git pull origin master
			if [ -f firmware.bin ]; then
				echo "automatically built cgo3plus camera firmware.bin successfully,push to the github repo"
				git add ./firmware.bin
				built_time=`date`
				echo "BuildTime:"$built_time
				git commit -m "$built_time, $master_commit_short"
				git push origin master
			else
				echo "automatically built cgo3plus camera firmware.bin failed"
			fi
		else
			echo "built cgo3plus yuneec_udp binary failed"
		fi


		#git e50 options
		cd $cur_dir
		git checkout master
			sleep 2
		make clean
			sleep 1
			git submodule update --init --recursive
			sleep 1
			git pull origin master
			sleep 10
		make CAMERA=e50
		
		if [ -f ../../camera_fimware_build/builds/e50/firmware.bin ]; then
                        echo "delete the e50 firmware.bin existed in camera_firmware_build"
                        rm ../../camera_firmware_build/builds/e50/firmware.bin
        fi

		if [ -f ./build/yuneec_udp ]; then
			echo "built yuneec_udp for e90 binary successfully"
			cp ./build/yuneec_udp ../../e50_rootfs_pkg/fakeroot/usr/local/bin/
			cd ../../e50_rootfs_pkg
			./auto_firmware.sh
			sleep 8
			cp ./out/firmware.bin ../camera_firmware_build/builds/e50/
			cd ../camera_firmware_build/builds/e50
			git pull origin master
			if [ -f firmware.bin ]; then
				echo "automatically built cgo_ci camera firmware.bin successfully,push to the github repo"
				git add ./firmware.bin
				built_time=`date`
				echo "BuildTime:"$built_time
				git commit -m "$built_time, $master_commit_short"
				git push origin master
			else
				echo "automatically built cgo_ci camera firmware.bin failed"
			fi
		else
            echo "built e90 yuneec_udp binary failed"
		fi

        #git e90 options
		cd $cur_dir
                sleep 2
		make clean
                sleep 1
                git submodule update --init --recursive
                sleep 1
                git pull origin master
                sleep 10
                make CAMERA=e90

                if [ -f ../../camera_fimware_build/builds/e90/firmware.bin ]; then
                        echo "delete the e90 firmware.bin existed in camera_firmware_build"
                        rm ../../camera_firmware_build/builds/e90/firmware.bin
                fi

                if [ -f ./build/yuneec_udp ]; then
                        echo "built yuneec_udp for e90 binary successfully"
                        cp ./build/yuneec_udp ../../e90_rootfs_pkg/genfirmware/fakeroot_pkg/fakeroot/usr/local/bin
			cd ../../e90_rootfs_pkg/genfirmware/
                        ./auto_rootfs.sh
			sleep 8
                        cp ./out/*firmware.bin ../../camera_firmware_build/builds/e90/firmware.bin
                        cd ../../camera_firmware_build/builds/e90/
			git pull origin master
                        if [ -f firmware.bin ]; then
                                echo "automatically built e90 camera firmware.bin successfully,push to the github repo"
                                git add ./firmware.bin
                                built_time=`date`
                                echo "BuildTime:"$built_time
                                git commit -m "$built_time, $master_commit_short"
                                git push origin master
                        else
                                echo "automatically built e90 camera firmware.bin failed"
                        fi
                else
                        echo "built e90 yuneec_udp binary failed"
                fi


	fi

	
	sleep 600
done
