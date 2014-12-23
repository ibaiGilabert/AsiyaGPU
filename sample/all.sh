#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=5G


DATAPATH=/home/usuaris/gilabert/PROVA_sTIME/AsiyaGPU/sample

metrics=( "LeM" "ROUGE" "METEOR" "GTM" "O" "NGRAM" "WER" "PER" "TER")

for i in "${metrics[@]}"
do
	echo "Asiya.pl Asiya.config -v -time -eval single,ulc -metric_set metric_$i -data_path $DATAPATH > $i.report"
	Asiya.pl Asiya.config -v -time -eval single,ulc -metric_set metrics_$i > $i.report

	for ((j=2; j<=32; j=j*2))
	do
    	echo "Asiya.pl Asiya.config -p $j -v -time -eval single -metric_set metric_$i -data_path $DATAPATH > $i_$j.report"
    	Asiya.pl Asiya.config -p $j -v -time -eval single -metric_set metrics_$i > $i_$j.report
	done
done
