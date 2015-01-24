#!/bin/bash

allfolders=( "ws_corpus100" "ws_corpus200" )

allsystems=( "Asiya-1.config" "Asiya-2.config" "Asiya-5.config" "Asiya-10.config" "Asiya-all.config" )

allmetric_sets=( "metrics_ROUGE" "metrics_METEOR" "metrics_GTM" "metrics_O" "metrics_WER" "metrics_PER" "metrics_TER" "metrics_LEM" )

allsplits=( "1" "2" "4" "8" "16" "32" )


cwd=$(pwd)

for F in "${allfolders[@]}"
do
    jid="0"
    for S in "${allsystems[@]}"
    do
        for M in "${allmetric_sets[@]}"
        do
            for R in "${allsplits[@]}"
            do
                folder=$cwd/$F/$R
                cp $cwd/$S $folder/$S
                if [ "$jid" = "0" ]; then   
                    jid="$(qsub  runAsiya_par.sh $folder $S $M $R)"
                else
                    jid="$(qsub  -hold_jid $jid runAsiya_par.sh $folder $S $M $R)"
                fi
                IFS=' ' read -a array <<< "$jid" 
                jid="${array[2]}"
                echo $jid
            done
        done
    done
done