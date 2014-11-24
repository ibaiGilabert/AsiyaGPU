#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=4G

echo ./Asiya Asiya_ROUGE_upv-combo_reference01_001.config -serialize 1 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_upv-combo_reference01_001.report
./Asiya Asiya_ROUGE_upv-combo_reference01_001.config -serialize 1 -g seg -eval single -metric_set metrics_ROUGE > run_ROUGE_upv-combo_reference01_001.report
