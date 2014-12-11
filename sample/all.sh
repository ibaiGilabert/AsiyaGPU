#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=1G


DATAPATH=/home/usuaris/gilabert/PROVA_ESA/AsiyaGPU/sample

metrics=( "ROUGE" "METEOR" "GTM" "O" )

for i in "${metrics[@]}"
do
	echo "Asiya.pl Asiya.config -v -eval single -metric_set metric_$i -data_path $DATAPATH > $i.report"
	Asiya.pl Asiya.config -v -eval single -metric_set metrics_$i > $i.report

	for ((j=2; j<=32; j=j*2))
	do
    	echo "Asiya.pl Asiya.config -p $j -v -eval single -metric_set metric_$i -data_path $DATAPATH > $i_$j.report"
    	Asiya.pl Asiya.config -p $j -v -eval single -metric_set metrics_$i > $i_$j.report
	done
done
