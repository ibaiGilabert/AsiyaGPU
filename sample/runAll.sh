#!/bin/bash

allfolders=( "ws_corpus100" "ws_corpus200" )

allsystems=( "Asiya-1.config" "Asiya-2.config" "Asiya-5.config" "Asiya-10.config" "Asiya-all.config" )

allmetric_sets=( "metrics_ROUGE" "metrics_METEOR" "metrics_GTM" "metrics_O" "metrics_WER" "metrics_PER" "metrics_TER" "metrics_LEM" )

cwd=$(pwd)

for F in "${allfolders[@]}"
do
    jid="0"
    for S in "${allsystems[@]}"
    do
        for M in "${allmetric_sets[@]}"
        do
            folder=$cwd/$F
            cp $cwd/$S $folder/$S
            if [ "$jid" = "0" ]; then   
                jid="$(qsub  runAsiya.sh $folder $S $M)"
            else
                jid="$(qsub  -hold_jid $jid runAsiya.sh $folder $S $M)"
            fi
            IFS=' ' read -a array <<< "$jid" 
            jid="${array[2]}"
            echo $jid
        done
    done
done
