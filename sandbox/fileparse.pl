#!/usr/bin/perl
use File::Basename;

srand();
my $r = rand(10000);

my $fullname = "/home/ibai/Escriptori/AsiyaGPU/sandbox/boost_ip.cc";
print "fullname: $fullname\n";

my $basename_isolated = basename("$fullname.$r");
my $basename_isolated_tok = basename("$fullname.$r.tok");

print "basename_isolate: $basename_isolated\n";
print "basename_isolate_tok: $basename_isolated_tok\n";

my @suffixlist = (); #(".txt", ".sgm", ".sgml");

my ($basename,$path,$suffix) = fileparse($fullname, @suffixlist);

print "basename: $basename\n";
print "path: $path\n";
print "suffix: $suffix\n";
