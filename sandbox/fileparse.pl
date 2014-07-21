#!/usr/bin/perl
use File::Basename;

my $fullname = "/home/ibai/Escriptori/AsiyaGPU/sandbox/boost_ip.cc";


my @suffixlist = (); #(".txt", ".sgm", ".sgml");

my ($basename,$path,$suffix) = fileparse($fullname, @suffixlist);

print "basename: $basename\n";
print "path: $path\n";
print "suffix: $suffix\n";