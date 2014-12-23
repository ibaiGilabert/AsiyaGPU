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

[ "$#" -eq 1 ] || die "1 argument required: name of the metric family (i.e., BLEU, NIST, TER, PER, ..), $# provided."

i=$1

./Asiya Asiya.config -v -time -eval single,ulc -g sys -metric_set metrics_$i -data_path $DATAPATH > $i.report
