#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=4G

echo ./Asiya Asiya_ROUGE_onlineB_reference01_004.config -serialize 28 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_onlineB_reference01_004.report
./Asiya Asiya_ROUGE_onlineB_reference01_004.config -serialize 28 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_onlineB_reference01_004.report
