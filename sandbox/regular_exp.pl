#!/usr/bin/perl

use File::Basename;


my $path = "/home/usuaris/\\gilabert/asiya/gpu/sample/   ";
print "path.a: $path|\n";

$path =~ s/\/\s*$//;
print "path.b: $path|\n";

my $TOOLS = "/ho//me/soft//asiya/tools//";
print "tools.a: $TOOLS|\n";
$TOOLS =~ s/\/+/\//g;
print "tools.b: $TOOLS|\n";

$TOOLS = "/home/ibai/Escriptori/AsiyaGPU/";
if (!(-d $TOOLS)) { die "[$Common::appNAME] directory <$TOOLS> does not exist!\n"; }

$command = "[$Common::appNAME\n] directory <$TOOLS> does not exist!\n";
print "command before: $command";
$command =~ s/\R/ /g;
print "command after: $command";

$s_character = "Ei; que jo* tinc un cullo de 'caracters' (especials)";
$s_character =~ s/\*/\\\*/g;
print "\n\ns_character -{*}: $s_character\n";
$s_character =~ s/;/\\;/g;
print "\ns_character -{*;}: $s_character\n";

$output = $s_character;
$output =~ s/\*/\\\*/g;
$output =~ s/\'/\\\'/g;
$output =~ s/\`/\\\`/g;
$output =~ s/\(/\\\(/g;
$output =~ s/\)/\\\)/g;
$output =~ s/;/\\;/g;
$output =~ s/\?/\\\?/g;

print "\n\nfinal output: $output\n";

$base_name = "/home/usuaris/gilabert/asiya/gpu/sample/tmp/9179.63435714231.out.BLEU.sgml";
print "name: $base_name\n";
print "base_name: ".basename("$base_name.23")."\n";

$auxOUT = ".";
if ( ($auxOUT eq "") or ($auxOUT =~ /^[\?\!\.]$/) ) {
	print "\nOUT!\n";
}

my $pwd = readpipe("pwd");
chomp($pwd);

$pwd = $pwd.".out";
print "pwd: |$pwd|\n";
$pwd =~ m/\.\//;
print "1: |$1|\n";
print "2: |$2|\n";

print "pwd: |$pwd|\n";

my $outRND = $pwd."./puta";
print "outRND: |$outRND|\n";
$outRND =~ s/\.\///;
print "outRND: |$outRND|\n";

if ( $outRND =~ m/\.\// ) {
  $outRND =~ s/\.\///;
  $outRND = "$pwd/$outRND";
}