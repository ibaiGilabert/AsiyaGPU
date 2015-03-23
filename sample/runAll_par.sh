#!/bin/bash

##allfolders=( "ws_corpus100" "ws_corpus200" "ws_corpus500" "ws_corpus1000" "ws_corpus2000" )
allfolders=( "ws_corpus100" "ws_corpus200" )

##allsystems=( "Asiya-1.config" "Asiya-2.config" "Asiya-5.config" "Asiya-10.config" "Asiya-all.config" )
allsystems=( "Asiya-1.config" "Asiya-2.config" )

##allmetric_sets=( "metrics_SP" "metrics_SR" "metrics_CE" "metrics_ESA" "metrics_GTM" "metrics_LEM" "metrics_METEOR" "metrics_NE" "metrics_NGRAM" "metrics_O" "metrics_PER" "metrics_ROUGE" "metrics_TER" "metrics_WER" )
allmetric_sets=( "metrics_ESA" "metrics_GTM" "metrics_LEM" "metrics_ROUGE" )

##allsplits=( "1" "2" "4" "8" "16" "32" )
allsplits=( "1" "2" "4" )


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
                #cp $cwd/$S $folder/$S
                if [ "$jid" = "0" ]; then   
                    jid="$(qsub -q medium runAsiya_par.sh $folder $S $M $R)"
                else
                    jid="$(qsub -q medium -hold_jid $jid runAsiya_par.sh $folder $S $M $R)"
                fi
                IFS=' ' read -a array <<< "$jid" 
                jid="${array[2]}"
                echo $jid
            done
        done
    done
done