#!/usr/bin/env perl

use strict;
use warnings;

my @letters = ('x', '-', '=', '+');

my $n = 100;
my $m = 400;
print "$n $m\n";

my @values = ();
for my $i (1 ... $n) {
  push @values, (int rand 4);
}
{
  my @printable = map {$letters[$_]} @values;
  local $" = '';
  print STDERR "@printable\n";
}

for my $i (1 ... $m) {
  my ($a, $b) = (0, 0);
  while ($a == $b) {
    $a = 1 + int rand $n;
    $b = 1 + int rand $n;
  }
  my $c = $values[$a-1] * $values[$b-1];
  $c = $letters[$c == 0 ? 0 : $c < 3 ? 1: $c <= 4 ? 2: 3];
  print "$a $b $c\n";
}
