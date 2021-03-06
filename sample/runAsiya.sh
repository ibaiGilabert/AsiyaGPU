#$ -S /bin/bash
#$ -V
#$ -cwd
#$ -m eas
#$ -M gilabert@cs.upc.edu
#$ -l h_vmem=25G
##$ -q short@node115,short@node116,short@node117,short@node315,short@node316

. /home/soft/asiya/ASIYA12.04.PATH

EXPECTED_ARGS=3
E_BADARGS=65

if [ $# -ne $EXPECTED_ARGS ]
then
  echo "Usage: `basename $0` {running folder} {Asiya.config} {metric_set}"
  exit $E_BADARGS
fi

cwd=$(pwd)
FOLDER=$1
CONFIG=$2
METRICSET=$3

cd $FOLDER
#echo "Asiya.pl -time -v -g all -eval single -metric_set $METRICSET -data_path $FOLDER $CONFIG > $CONFIG.$METRICSET.report 2> $CONFIG.$METRICSET.err"
#Asiya.pl -time -v -g all -eval single -metric_set $METRICSET -data_path $FOLDER $CONFIG > $CONFIG.$METRICSET.report 2> $CONFIG.$METRICSET.err
echo "./Asiya $CONFIG -time -v -eval single,ulc -g sys -metric_set $METRICSET -data_path $FOLDER > $CONFIG.$METRICSET.report 2> $CONFIG.$METRICSET.err"
./Asiya $CONFIG -time -v -eval single,ulc -g sys -metric_set $METRICSET -data_path $FOLDER > $CONFIG.$METRICSET.report 2> $CONFIG.$METRICSET.err

rm -rf $FOLDER/scores
rm -rf $FOLDER/tmp
cd $cwd
