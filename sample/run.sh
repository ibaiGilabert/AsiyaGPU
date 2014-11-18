#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=4G


DATAPATH=/home/usuaris/gilabert/PROVA/AsiyaGPU/sample

die () {
    echo >&2 "$@"
    exit 1
}

[ "$#" -eq 1 ] || die "1 argument required: name of the metric family (i.e., BLEU, NIST, TER, PER, ..), $# provided."

i=$1

./Asiya Asiya.config.old -p 3 -eval single,ulc -g seg -metric_set metrics_$i -data_path $DATAPATH > $i.report