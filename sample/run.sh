#!/bin/bash

DATAPATH=/home/usuaris/gilabert/AsiyaGPU

die () {
    echo >&2 "$@"
    exit 1
}

[ "$#" -eq 1 ] || die "1 argument required: name of the metric family (i.e., BLEU, NIST, TER, PER, ..), $# provided."

i=$1

./Asiya Asiya.config -v -eval single -metric_set metrics_$i -data_path $DATAPATH
