#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=5G


DATAPATH=/home/usuaris/gilabert/PROVA_TESTBED/AsiyaGPU/sample

die () {
    echo >&2 "$@"
    exit 1
}

[ "$#" -eq 2 ] || die "2 argument required: name of the metric family (i.e., BLEU, NIST, TER, PER, ..) and #folds, $# provided."

i=$1
j=$2

./Asiya Asiya.config -p $j -v -time -eval single,ulc -g sys -metric_set metrics_$i -data_path $DATAPATH > $i.report
