#!/usr/bin/perl

my @arr = (2, 4, 8, 10);

print "First result:\n";
print scalar @arr;

print "\nSecond result:\n";
print $#arr + 1; # Shift numeration with +1 as it shows last index that starts with 0.

my $arrSize = @arr;
print "\nThird result: $arrSize\n";