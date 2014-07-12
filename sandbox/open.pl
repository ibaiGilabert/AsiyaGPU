#!/usr/bin/perl

my $IQ_config = "Asiya.config";
my $i = 1;

open(QF, "<$IQ_config") or die "couldn't open file: $IQ_config\n";
while (my $line = <QF>) { # READING INPUT MODE
   print "line: $i $line\n";
   if ($line =~ /^[^#].*=.*/) {

      print "\tthat was a kind of line\n";

      #chomp($line);
      my @entry = split(/ *= */, $line);

      print "\tentry: @entry\n";
      #if (lc($entry[0]) eq "input") {}
   }
   $i = $i + 1;
}