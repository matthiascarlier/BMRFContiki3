#!/bin/bash

POSITION="XorYcoords"
MOTE_IDENT="moteIdentifier"
SIMSPERSCENARIO=10

declare -a RESULTFILES=('raw' 'delay' 'summary' 'duplicates' 'duplicates_raw');
declare -a PERCENTTOPOLOGIES=('100');
declare -a ENGINECONF=('BMRF' 'BMRF');
declare -a MODECONF=('UNICAST' 'BROADCAST');
declare -a THRESHOLDCONF=('1' '1');

declare -a RANDOMTOPOLOGIES=('topology_1_childZ1_nodata')

SEEDS=(100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900 5000 5100 5200 5300 5400 5500 5600 5700 5800 5900 6000 6100 6200 6300 6400 6500 6600 6700 6800 6900 7000 7100 7200 7300 7400 7500 7600 7700 7800 7900 8000 8100 8200 8300 8400 8500 8600 8700 8800 8900 9000 9100 9200 9300 9400 9500 9600 9700 9800 9900 10000)

declare -a remaining_motes=()
declare -a remaining_motes_aux=()
declare -a motes_names=()
declare -a motes_names_aux=()

for topology in "${RANDOMTOPOLOGIES[@]}"
do
    mkdir $topology
    for ((j=1; j <= $SIMSPERSCENARIO; j++))
    do
        echo "Generating random topologies"
        for percenttop in "${PERCENTTOPOLOGIES[@]}"
        do
            #randomseed= ${SEEDS[$j]}
            subscribed_number=$((50*$percenttop/100))
            remaining_motes=(1 $((50-$subscribed_number)) $subscribed_number)
            motes_names=('z11' 'z12' 'z13')
            cp $topology".csc" "multicast-sim-"$percenttop"-percent_tosim.csc"
            sed -i s/\#randomseed\#/${SEEDS[$j]}/ "multicast-sim-"$percenttop"-percent_tosim.csc"
            
            if [ $topology == 'topology_1_childZ1' ]
            then
            IDs=( $(echo "2 3 4 5 6" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi
			
			if [ $topology == 'topology_1_childZ1_nodata' ]
            then
            IDs=( $(echo "2 3 4 5 6" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi
			
			if [ $topology == 'topology_2_childZ1' ]
            then
            IDs=( $(echo "2 3 4 5 6 7 8 9 10 11 12 13 14 15" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi
			
			if [ $topology == 'topology_3_childZ1-close' ]
            then
            IDs=( $(echo "2 3 4 5 6 7 8 9 10 11 12 13" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi
			
			if [ $topology == 'topology_3_childZ1-close-deep' ]
            then
            IDs=( $(echo "2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi
			
			if [ $topology == 'topology_4_childZ1-close' ]
            then
            IDs=( $(echo "2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21" | sed -r 's/(.[^;]*;)/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )
			fi

			for id in "${!IDs[@]}"
			do
				sed -i s/\#ID"$id"\#/${IDs[$id]}/ "multicast-sim-"$percenttop"-percent_tosim.csc"
			done

#check if this needs to be done
            rand_mote="moteIdentifier"
            while sed -i "/$MOTE_IDENT/,\${s//$rand_mote/;:a;n;ba};\$q1" "multicast-sim-"$percenttop"-percent_tosim.csc"
            do
                motes_names_aux=()
                remaining_motes_aux=()
                for ((h=0; h <${#remaining_motes[@]}; h++))
                do
                    if [ "${remaining_motes[$h]}" != "0" ]; then
                        motes_names_aux+=(${motes_names[$h]})
                        remaining_motes_aux+=(${remaining_motes[$h]})
                    fi
                done
                if [[ "${#motes_names[@]}" == "1" ]]; then
                    random_number=0
                else
                    random_number=$[RANDOM % ((${#motes_names[@]}-1))]
                fi
                remaining_motes_aux[$random_number]=$((${remaining_motes_aux[$random_number]}-1))
                remaining_motes=("${remaining_motes_aux[@]}")
                motes_names=("${motes_names_aux[@]}")
                rand_mote=${motes_names[$random_number]}
            done
        done

        for ((i=0; i<${#ENGINECONF[@]}; ++i)); do
            echo "Loading project-conf"
            cp project-conf-sample.h project-conf.h
            sed -i s/\#engine\#/UIP_MCAST6_ENGINE_${ENGINECONF[i]}/ project-conf.h
            sed -i s/\#mode\#/BMRF_${MODECONF[i]}_MODE/ project-conf.h
            sed -i s/\#threshold\#/${THRESHOLDCONF[i]}/ project-conf.h

            for percenttop in "${PERCENTTOPOLOGIES[@]}"
            do
                simfile="multicast-sim-"$percenttop"-percent_tosim.csc"

                echo "Starting simulation of "$percenttop"% topologie with "${ENGINECONF[i]}" engine, "${MODECONF[i]}" mode and threshold "${THRESHOLDCONF[i]}"."
                echo "Iteration number "$j
                make TARGET=cooja nogui=Simulation $simfile

                for filename in "${RESULTFILES[@]}"
                do
                    mv $filename"_results.csv" $topology"/"$filename"_results_"$percenttop"-percent_"${ENGINECONF[i]}"_"${MODECONF[i]}"_"${THRESHOLDCONF[i]}"_iteration-"$j".csv"
                done
            done

            rm project-conf.h
        done

        for topologie in "${SIMTOPOLOGIES[@]}"
        do
            rm "multicast-sim-"$topologie"-percent_tosim.csc"
        done
    done
done
