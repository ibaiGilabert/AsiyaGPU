#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=4G

echo ./Asiya Asiya_ROUGE_upc_reference01_002.config -serialize 10 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_upc_reference01_002.report
./Asiya Asiya_ROUGE_upc_reference01_002.config -serialize 10 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_upc_reference01_002.report
