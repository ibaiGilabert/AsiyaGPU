#!/usr/bin/perl
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
