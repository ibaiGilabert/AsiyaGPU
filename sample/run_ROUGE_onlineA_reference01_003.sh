#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=4G

echo ./Asiya Asiya_ROUGE_onlineA_reference01_003.config -serialize 19 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_onlineA_reference01_003.report
./Asiya Asiya_ROUGE_onlineA_reference01_003.config -serialize 19 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_onlineA_reference01_003.report
