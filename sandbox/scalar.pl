#!/usr/bin/perl
my @refs = (2, 3, 4, 5);

print join("_", sort @refs), "\n";
if (scalar(@refs)) {
	print "PUTA\n";
}