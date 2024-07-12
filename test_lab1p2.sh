#!/bin/bash

echo  'int main() { return 0; }' > a.c
echo  ' int main() { return 0; }' > b.c
echo  'int main() {  return 0; }' > c.c

gcc -o lab1p2 lab1p2.c

# Test without placeholders
echo "Testing without placeholders:"
./lab1p2 ls -l

# Test with single placeholder
echo "Testing with single placeholder:"
{
echo "a.c"
echo "b.c"
echo "c.c"
} | ./lab1p2 gcc -c %

# Test with multiple placeholders
echo "Testing with multiple placeholders:"
{
echo "a.c -o a.o"
echo "b.c -o b.o"
echo "c.c -o c.o"
} | ./lab1p2 gcc % % % %


rm a.c b.c c.c a.o b.o c.o lab1p2
